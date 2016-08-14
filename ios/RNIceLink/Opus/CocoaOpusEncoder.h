#import <Foundation/Foundation.h>

#import "CocoaOpusBuffer.h"

@interface CocoaOpusEncoder : NSObject

@property bool debugMode;
@property int bitrate;
@property double quality;

- (id)initWithClockRate:(int)clockRate channels:(int)channels packetTime:(int)packetTime;
- (void)activateFECWithPacketLossPercent:(int)packetLossPercent;
- (void)deactivateFEC;
- (NSMutableData *)encodeBuffer:(CocoaOpusBuffer *)buffer;
- (void)destroy;

@end
