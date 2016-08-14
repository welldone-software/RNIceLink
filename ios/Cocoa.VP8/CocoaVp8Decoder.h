#import <Foundation/Foundation.h>

#import "CocoaVp8Buffer.h"

#include "vpx_decoder.h"
#include "vp8dx.h"

@interface CocoaVp8Decoder : NSObject
{
    vpx_codec_ctx_t *_codec;
    bool _debugMode;
    bool _needsKeyFrame;
}

@property bool debugMode;
@property bool needsKeyFrame;

- (bool)decodeFrame:(NSData *)frame toBuffer:(CocoaVp8Buffer *)buffer;
- (void)destroy;

@end
