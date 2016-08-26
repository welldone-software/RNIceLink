#import "CocoaOpusBuffer.h"

@implementation CocoaOpusBuffer

@synthesize data=_data;
@synthesize index=_index;
@synthesize length=_length;

-(void) dealloc
{
   [_data release];
   [super dealloc];
}

@end
