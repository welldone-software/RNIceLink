#import "CocoaOpusEncoder.h"

@implementation CocoaOpusEncoder

@synthesize debugMode=_debugMode;

- (int)bitrate
{
    return _bitrate;
}

- (void)setBitrate:(int)bitrate
{
    int lowerBound = 1;
    int upperBound = 500;
    _bitrate = (bitrate < lowerBound ? lowerBound : (bitrate > upperBound ? upperBound : bitrate));
    opus_encoder_ctl(_encoder, OPUS_SET_BITRATE(_bitrate * 1024));
}

- (double)quality
{
    return _quality;
}

- (void)setQuality:(double)quality
{
    _quality = (quality < 0.0 ? 0.0 : (quality > 1.0 ? 1.0 : quality));
    
    int lowerBound = 0;
    int upperBound = 10;
    _complexity = lowerBound + (int)(_quality * (upperBound - lowerBound));
    opus_encoder_ctl(_encoder, OPUS_SET_COMPLEXITY(_complexity));
}

- (id)initWithClockRate:(int)clockRate channels:(int)channels packetTime:(int)packetTime
{
    self = [super init];
    if (self)
    {
        _frameSizePerChannel = (clockRate * packetTime) / 1000;
        _maxEncodedDataLength = 4000;
        _encodedData = [[NSMutableData alloc] initWithLength:_maxEncodedDataLength];
        
        // initialize encoder
        int error;
        _encoder = opus_encoder_create(clockRate, channels, OPUS_APPLICATION_VOIP, &error);
        if (error != OPUS_OK)
        {
            NSLog(@"Could not initialize encoder. %s", opus_strerror(error));
            [NSException raise:@"InitializeException" format:@"Could not initialize encoder."];
        }
        
        opus_encoder_ctl(_encoder, OPUS_SET_SIGNAL(OPUS_SIGNAL_VOICE));
        
        self.quality = 1.0;
        self.bitrate = 125;
    }
    return self;
}

- (void)activateFECWithPacketLossPercent:(int)packetLossPercent
{
    opus_encoder_ctl(_encoder, OPUS_SET_INBAND_FEC(1));
    opus_encoder_ctl(_encoder, OPUS_SET_PACKET_LOSS_PERC(packetLossPercent));
}

- (void)deactivateFEC
{
    opus_encoder_ctl(_encoder, OPUS_SET_INBAND_FEC(0));
    opus_encoder_ctl(_encoder, OPUS_SET_PACKET_LOSS_PERC(0));
}

- (void)destroy
{
    if (_encoder)
    {
        opus_encoder_destroy(_encoder);
        _encoder = nil;
    }
    
    if (_encodedData)
    {
        [_encodedData autorelease];
        _encodedData = nil;
    }
}

- (NSMutableData *)encodeBuffer:(CocoaOpusBuffer *)buffer
{
    uint8_t *data = (uint8_t *)buffer.data.bytes + buffer.index;
    int encodedLength = opus_encode(_encoder, (opus_int16 *)data, _frameSizePerChannel, _encodedData.mutableBytes, _maxEncodedDataLength);
    if (encodedLength > 0)
    {
        return [NSMutableData dataWithBytes:_encodedData.bytes length:encodedLength];
    }
    
    if (_debugMode)
    {
        NSLog(@"Could not encode frame.");
    }
    return nil;
}

@end
