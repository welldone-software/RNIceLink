#import "CocoaVp8Decoder.h"

#define VPX_CODEC_DISABLE_COMPAT 1
#define vp8dx (vpx_codec_vp8_dx())

@implementation CocoaVp8Decoder

@synthesize debugMode=_debugMode;
@synthesize needsKeyFrame=_needsKeyFrame;

- (id)init
{
    self = [super init];
    if (self)
    { }
    return self;
}

- (bool)decodeFrame:(NSData *)frame toBuffer:(CocoaVp8Buffer *)buffer
{
    // check args
    if (!frame || !buffer)
    {
        if (_debugMode)
        {
            NSLog(@"Argument 'frame' or 'buffer' missing.");
        }
        return NO;
    }
    
    // create decoder
    if (!_codec)
    {
        if (_debugMode)
        {
            NSLog(@"Configuring decoder.");
        }
        // initialize decoder
        _codec = malloc(sizeof(vpx_codec_ctx_t));
        vpx_codec_err_t res = vpx_codec_dec_init(_codec, vp8dx, NULL, 0);
        if (res)
        {
            free(_codec);
            _codec = nil;
            
            NSLog(@"Could not initialize decoder. %s", vpx_codec_err_to_string(res));
            [NSException raise:@"InitializeException" format:@"Could not initialize decoder."];
        }
    }
    
    if (_debugMode)
    {
        NSLog(@"Ready for decoding. (%d bytes)", (int)frame.length);
    }
    
    // decode
    vpx_codec_err_t res = vpx_codec_decode(_codec, frame.bytes, (unsigned int)frame.length, NULL, 1);
    if (res)
    {
        if (res == 5) // need a keyframe
        {
            _needsKeyFrame = YES;
        }
        if (_debugMode)
        {
            NSLog(@"Could not decode frame. %s", vpx_codec_err_to_string(res));
        }
        return NO;
    }
    
    _needsKeyFrame = NO;
    
    // get frame
    vpx_image_t *img;
    vpx_codec_iter_t iter = NULL;
    while ((img = vpx_codec_get_frame(_codec, &iter)))
    {
        // get image details
        size_t width = img->d_w;
        size_t height = img->d_h;
        size_t height_2 = height / 2;
        size_t strideY = img->stride[VPX_PLANE_Y];
        size_t strideU = img->stride[VPX_PLANE_U];
        size_t strideV = img->stride[VPX_PLANE_V];
        size_t dataYLength = strideY * height;
        size_t dataULength = strideU * height_2;
        size_t dataVLength = strideV * height_2;
        
        // copy planes
        buffer.planeY = [[[NSData alloc] initWithBytesNoCopy:img->planes[VPX_PLANE_Y] length:dataYLength freeWhenDone:NO] autorelease];
        buffer.planeU = [[[NSData alloc] initWithBytesNoCopy:img->planes[VPX_PLANE_U] length:dataULength freeWhenDone:NO] autorelease];
        buffer.planeV = [[[NSData alloc] initWithBytesNoCopy:img->planes[VPX_PLANE_V] length:dataVLength freeWhenDone:NO] autorelease];
        
        // copy strides
        buffer.strideY = (int)strideY;
        buffer.strideU = (int)strideU;
        buffer.strideV = (int)strideV;
        
        if (_debugMode)
        {
            NSLog(@"Decoded frame. (%d x %d, YS %d, US %d, VS %d)", buffer.width, buffer.height, buffer.strideY, buffer.strideU, buffer.strideV);
        }
        
        // copy dimensions
        buffer.width = (int)width;
        buffer.height = (int)height;
        
        return YES;
    }
    
    if (_debugMode)
    {
        NSLog(@"Could not decode frame.");
    }
    return NO;
}

- (void)destroy
{
    if (_codec)
    {
        vpx_codec_destroy(_codec);
        free(_codec);
        _codec = nil;
    }
}

@end
