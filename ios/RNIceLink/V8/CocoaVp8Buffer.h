#import <Foundation/Foundation.h>

@interface CocoaVp8Buffer : NSObject

@property (nonatomic, retain) NSData *planeY;
@property (nonatomic, retain) NSData *planeU;
@property (nonatomic, retain) NSData *planeV;
@property int strideY;
@property int strideU;
@property int strideV;
@property int width;
@property int height;

@end
