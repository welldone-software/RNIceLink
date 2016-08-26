#import "CocoaVp8Encoder.h"

#define VPX_CODEC_DISABLE_COMPAT 1
#define vp8cx (vpx_codec_vp8_cx())

FILE *fopen$UNIX2003(const char *filename, const char *mode) {
    return fopen(filename, mode);
}

size_t fwrite$UNIX2003(const void *ptr, size_t size, size_t nitems, FILE *stream) {
    return fwrite(ptr, size, nitems, stream);
}

@implementation CocoaVp8Encoder

@synthesize debugMode=_debugMode;
@synthesize bitrate=_bitrate;

- (double)quality
{
    return _quality;
}

- (void)setQuality:(double)quality
{
    _quality = (quality < 0.0 ? 0.0 : (quality > 1.0 ? 1.0 : quality));
    
    int lowerBound = 31;
    int upperBound = 63;
    _maxQuantizer = lowerBound + (int)((1.0 - _quality) * (upperBound - lowerBound));
}

- (id)init
{
    self = [super init];
    if (self)
    {
        _frame_cnt = 0;
        _maxFramerate = 30;
        
        self.quality = 0.5;
        self.bitrate = 320;
        //self.scale = 1.0;
    }
    return self;
}

- (bool)encodeBuffer:(CocoaVp8Buffer *)buffer toFrame:(NSMutableData*)frame;
{
    // check args
    if (!buffer || !frame)
    {
        if (_debugMode)
        {
            NSLog(@"Argument 'buffer' or 'frame' missing.");
        }
        return NO;
    }
    
    // if the dimensions change, trash reusable data structures
    if (_codec && (buffer.width != _config->g_w || buffer.height != _config->g_h))
    {
        vpx_codec_destroy(_codec);
        free(_codec);
        free(_config);
        _codec = nil;
        _config = nil;
    }
    
    // create encoder
    if (!_codec)
    {
        if (_debugMode)
        {
            NSLog(@"Configuring encoder to use new dimensions. (%d %d)", buffer.width, buffer.height);
        }
        
        // allocate config
        _config = malloc(sizeof(vpx_codec_enc_cfg_t));
        
        // set config defaults
        vpx_codec_err_t res = vpx_codec_enc_config_default(vp8cx, _config, 0);
        if (res)
        {
            free(_config);
            _config = nil;
            
            NSLog(@"Could not set encoder config defaults. %s", vpx_codec_err_to_string(res));
            [NSException raise:@"InitializeException" format:@"Could not set encoder config defaults."];
        }
        
        _config->g_timebase.num = 1;
        _config->g_timebase.den = 30;
        _config->rc_target_bitrate = _bitrate;
        _config->rc_end_usage = VPX_CBR;
        _config->g_w = buffer.width;
        _config->g_h = buffer.height;
        _config->kf_mode = VPX_KF_AUTO;
        _config->kf_min_dist = _config->kf_max_dist = _config->g_timebase.den * 60; // 1 per min @ 30fps;
        _config->g_error_resilient = 1;
        _config->g_lag_in_frames = 0;
        _config->g_pass = VPX_RC_ONE_PASS;
        _config->rc_min_quantizer = 0;
        _config->rc_max_quantizer = _maxQuantizer;
        _config->g_profile = 0;
        
        // allocate encoder
        _codec = malloc(sizeof(vpx_codec_ctx_t));
        
        // initialize encoder
        res = vpx_codec_enc_init(_codec, vp8cx, _config, 0);
        if (res)
        {
            free(_codec);
            _codec = nil;
            
            NSLog(@"Could not initialize encoder. %s", vpx_codec_err_to_string(res));
            [NSException raise:@"InitializeException" format:@"Could not initialize encoder."];
        }
        
#if TARGET_OS_IPHONE
        // additional tuning
        vpx_codec_control(_codec, VP8E_SET_STATIC_THRESHOLD, 1);
        vpx_codec_control(_codec, VP8E_SET_CPUUSED, -12); // only on mobile
        vpx_codec_control(_codec, VP8E_SET_TOKEN_PARTITIONS, VP8_ONE_TOKENPARTITION);
        vpx_codec_control(_codec, VP8E_SET_NOISE_SENSITIVITY, 0);
        vpx_codec_control(_codec, VP8E_SET_MAX_INTRA_BITRATE_PCT, MIN(300, (_config->rc_buf_optimal_sz * 0.5f * _maxFramerate / 10)));
#endif
        
        // create new image
        vpx_img_wrap(&_img, VPX_IMG_FMT_I420, buffer.width, buffer.height, 1, (unsigned char *)1);
    }
    
    // handle bitrate change
    if (_bitrate != _config->rc_target_bitrate || _maxQuantizer != _config->rc_max_quantizer)
    {        
        _config->rc_target_bitrate = _bitrate;
        _config->rc_max_quantizer = _maxQuantizer;
        
        vpx_codec_err_t res = vpx_codec_enc_config_set(_codec, _config);
        if (res)
        {
            NSLog(@"Could not reconfigure encoder. %s", vpx_codec_err_to_string(res));
            return NO;
        }
    }
    
    // set flags
    vpx_enc_frame_flags_t flag = 0;
    if (_sendKeyframe)
    {
        if (_debugMode)
        {
            NSLog(@"Forcing keyframe.");
        }
        
        flag |= VPX_EFLAG_FORCE_KF;
        _sendKeyframe = NO;
    }
    
    vpx_image_t *img = &_img;
    img->planes[VPX_PLANE_Y] = (unsigned char *)buffer.planeY.bytes;
    img->planes[VPX_PLANE_U] = (unsigned char *)buffer.planeU.bytes;
    img->planes[VPX_PLANE_V] = (unsigned char *)buffer.planeV.bytes;
    img->stride[VPX_PLANE_Y] = buffer.strideY;
    img->stride[VPX_PLANE_U] = buffer.strideU;
    img->stride[VPX_PLANE_V] = buffer.strideV;
    
    if (_debugMode)
    {
        NSLog(@"Ready for encoding. (%d x %d, YS %d, US %d, VS %d)", buffer.width, buffer.height, buffer.strideY, buffer.strideU, buffer.strideV);
    }
    
    // encode
    uint32_t duration = 90000 / _maxFramerate;
    vpx_codec_err_t res = vpx_codec_encode(_codec, img, _frame_cnt, duration, flag, VPX_DL_REALTIME);
    if (res)
    {
        if (_debugMode)
        {
            NSLog(@"Could not encode frame. %s", vpx_codec_err_to_string(res));
        }
        return NO;
    }
    
    // update counter
    _frame_cnt++;
    
    // get frame
    vpx_codec_iter_t iter = NULL;
    const vpx_codec_cx_pkt_t *pkt;
    while ((pkt = vpx_codec_get_cx_data(_codec, &iter)))
    {
        if (pkt->kind == VPX_CODEC_CX_FRAME_PKT)
        {
            if (_debugMode)
            {
                NSLog(@"Encoded frame. (%zd bytes)", pkt->data.frame.sz);
            }
            [frame appendBytes:pkt->data.frame.buf length:pkt->data.frame.sz];
            return YES;
        }
    }
    
    if (_debugMode)
    {
        NSLog(@"Could not encode frame.");
    }
    return NO;
}

- (void)sendKeyframe
{
    _sendKeyframe = YES;
}

- (void)destroy
{
    if (_codec)
    {
        vpx_codec_destroy(_codec);
        free(_codec);
        _codec = nil;
    }
    if (_config)
    {
        free(_config);
        _config = nil;
    }
}

@end
