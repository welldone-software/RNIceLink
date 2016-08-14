#import <Foundation/Foundation.h>

#import "CocoaVp8Buffer.h"

@interface CocoaVp8Decoder : NSObject

@property bool debugMode;
@property bool needsKeyFrame;

- (bool)decodeFrame:(NSData *)frame toBuffer:(CocoaVp8Buffer *)buffer;
- (void)destroy;

@end
