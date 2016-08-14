#import "CocoaVp8Buffer.h"

@implementation CocoaVp8Buffer

@synthesize planeY=_planeY;
@synthesize planeU=_planeU;
@synthesize planeV=_planeV;
@synthesize strideY=_strideY;
@synthesize strideU=_strideU;
@synthesize strideV=_strideV;
@synthesize width=_width;
@synthesize height=_height;

-(void) dealloc
{
   [_planeY release];
   [_planeU release];
   [_planeV release];
   [super dealloc];
}

@end
