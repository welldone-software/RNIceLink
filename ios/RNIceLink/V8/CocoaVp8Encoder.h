#import <Foundation/Foundation.h>

#import "CocoaVp8Buffer.h"

@interface CocoaVp8Encoder : NSObject

@property bool debugMode;
@property double quality;
@property int bitrate;

- (bool)encodeBuffer:(CocoaVp8Buffer *)buffer toFrame:(NSMutableData*)frame;
- (void)sendKeyframe;
- (void)destroy;

@end
