#import <Foundation/Foundation.h>

#import "CocoaVp8Buffer.h"

#include "vpx_encoder.h"
#include "vp8cx.h"

@interface CocoaVp8Encoder : NSObject
{
    vpx_codec_ctx_t *_codec;
    vpx_codec_enc_cfg_t *_config;
    vpx_image_t _img;
    vpx_codec_pts_t _frame_cnt;
    bool _sendKeyframe;
    
    int _bitrate;
    double _quality;
    int _maxQuantizer;
    
    int _maxFramerate;
    bool _debugMode;
}

@property bool debugMode;
@property double quality;
@property int bitrate;

- (bool)encodeBuffer:(CocoaVp8Buffer *)buffer toFrame:(NSMutableData *)frame;
- (void)sendKeyframe;
- (void)destroy;

@end
