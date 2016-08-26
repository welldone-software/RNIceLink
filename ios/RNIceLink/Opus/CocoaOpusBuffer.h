#import <Foundation/Foundation.h>

@interface CocoaOpusBuffer : NSObject

@property (nonatomic, retain) NSData *data;
@property int index;
@property int length;

@end
