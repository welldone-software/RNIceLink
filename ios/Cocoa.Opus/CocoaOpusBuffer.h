#import <Foundation/Foundation.h>

@interface CocoaOpusBuffer : NSObject
{
    NSData *_data;
    int _index;
    int _length;
}

@property (nonatomic, retain) NSData *data;
@property int index;
@property int length;

@end
