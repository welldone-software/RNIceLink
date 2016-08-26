#import <Foundation/Foundation.h>

#import "CocoaOpusBuffer.h"

#include "opus.h"

@interface CocoaOpusDecoder : NSObject
{
    OpusDecoder *_decoder;
    int _frameSizePerChannel;
    int _maxDataLength;
    NSMutableData *_data;
    NSMutableData *_fecData;
    int _channels;
    
    bool _debugMode;
}

@property bool debugMode;

- (id)initWithClockRate:(int)clockRate channels:(int)channels packetTime:(int)packetTime;
- (CocoaOpusBuffer *)decodeFrame:(NSData *)frame;
- (CocoaOpusBuffer *)decodeFrame:(NSData *)frame fec:(bool)fec;
- (void)destroy;

@end
