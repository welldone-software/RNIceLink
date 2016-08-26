#import <Foundation/Foundation.h>

#import "CocoaOpusBuffer.h"

#include "opus.h"

@interface CocoaOpusEncoder : NSObject
{
    OpusEncoder *_encoder;
    int _frameSizePerChannel;
    int _maxEncodedDataLength;
    NSMutableData *_encodedData;
    int _bitrate;
    double _quality;
    int _complexity;
    
    bool _debugMode;
}

@property bool debugMode;
@property int bitrate;
@property double quality;

- (id)initWithClockRate:(int)clockRate channels:(int)channels packetTime:(int)packetTime;
- (void)activateFECWithPacketLossPercent:(int)packetLossPercent;
- (void)deactivateFEC;
- (NSMutableData *)encodeBuffer:(CocoaOpusBuffer *)buffer;
- (void)destroy;

@end
