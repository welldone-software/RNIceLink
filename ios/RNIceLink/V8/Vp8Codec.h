#import <Foundation/Foundation.h>

#import "FM.h"
#import "FMIceLink.h"
#import "FMIceLinkWebRTC.h"

#import "CocoaVp8Encoder.h"
#import "CocoaVp8Decoder.h"

@interface Vp8Codec : FMIceLinkWebRTCVideoCodec
{
    CocoaVp8Encoder *_encoder;
    CocoaVp8Decoder *_decoder;
    FMIceLinkWebRTCVp8Padep *_padep;
    
    int _lossyCount;
    int _losslessCount;
}

- (id)init;

@end