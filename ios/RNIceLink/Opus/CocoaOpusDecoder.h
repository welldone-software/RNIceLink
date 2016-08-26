#import <Foundation/Foundation.h>

#import "CocoaOpusBuffer.h"

@interface CocoaOpusDecoder : NSObject

@property bool debugMode;

- (id)initWithClockRate:(int)clockRate channels:(int)channels packetTime:(int)packetTime;
- (CocoaOpusBuffer *)decodeFrame:(NSData *)frame;
- (CocoaOpusBuffer *)decodeFrame:(NSData *)frame fec:(bool)fec;
- (void)destroy;

@end
