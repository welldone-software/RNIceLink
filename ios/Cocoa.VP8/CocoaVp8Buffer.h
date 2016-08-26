#import <Foundation/Foundation.h>

@interface CocoaVp8Buffer : NSObject
{
    NSData *_planeY;
    NSData *_planeU;
    NSData *_planeV;
    int _strideY;
    int _strideU;
    int _strideV;
    int _width;
    int _height;
}

@property (nonatomic, retain) NSData *planeY;
@property (nonatomic, retain) NSData *planeU;
@property (nonatomic, retain) NSData *planeV;
@property int strideY;
@property int strideU;
@property int strideV;
@property int width;
@property int height;

@end
