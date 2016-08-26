#import "CocoaOpusDecoder.h"

@implementation CocoaOpusDecoder

@synthesize debugMode=_debugMode;

- (id)initWithClockRate:(int)clockRate channels:(int)channels packetTime:(int)packetTime
{
    self = [super init];
    if (self)
    {
        _frameSizePerChannel = (clockRate * packetTime) / 1000;
        _maxDataLength = clockRate * channels * sizeof(short) * packetTime / 1000;
        _data = [[NSMutableData alloc] initWithLength:_maxDataLength];
        _fecData = [[NSMutableData alloc] initWithLength:_maxDataLength];
        
        _channels = channels;
        
        // initialize decoder
        int error;
        _decoder = opus_decoder_create(clockRate, channels, &error);
        if (error != OPUS_OK)
        {
            NSLog(@"Could not initialize decoder. %s", opus_strerror(error));
            [NSException raise:@"InitializeException" format:@"Could not initialize decoder."];
        }
    }
    return self;
}

- (void)destroy
{
    if (_decoder)
    {
        opus_decoder_destroy(_decoder);
        _decoder = nil;
    }
    
    if (_data)
    {
        [_data autorelease];
        _data = nil;
    }
    
    if (_fecData)
    {
        [_fecData autorelease];
        _fecData = nil;
    }
}

- (CocoaOpusBuffer *)decodeFrame:(NSData *)frame
{
    return [self decodeFrame:frame fec:NO];
}

- (CocoaOpusBuffer *)decodeFrame:(NSData *)frame fec:(bool)fec
{
    if (!frame)
    {
        NSMutableData *plcData = [NSMutableData dataWithLength:_maxDataLength];
        
        int numSamplesDecoded = opus_decode(_decoder, 0, 0, (opus_int16 *)plcData.mutableBytes, _frameSizePerChannel, fec ? 1 : 0);
        if (numSamplesDecoded > 0)
        {
            CocoaOpusBuffer *buffer = [[[CocoaOpusBuffer alloc] init] autorelease];
            buffer.data = plcData;
            buffer.index = 0;
            buffer.length = numSamplesDecoded * _channels * sizeof(short);
            return buffer;
        }
    }
    else
    {
        int numSamplesDecoded = opus_decode(_decoder, frame.bytes, (opus_int32)frame.length, (opus_int16 *)(fec ? _fecData.mutableBytes : _data.mutableBytes), _frameSizePerChannel, fec ? 1 : 0);
        if (numSamplesDecoded > 0)
        {
            CocoaOpusBuffer *buffer = [[[CocoaOpusBuffer alloc] init] autorelease];
            buffer.data = (fec ? _fecData : _data);
            buffer.index = 0;
            buffer.length = numSamplesDecoded * _channels * sizeof(short);
            return buffer;
        }
    }
    
    if (_debugMode)
    {
        NSLog(@"Could not decode frame.");
    }
    
    return nil;
}

@end
