#import "OpusCodec.h"

@implementation OpusCodec

@synthesize percentLossToTriggerFEC=_percentLossToTriggerFEC;
@synthesize disableFEC=_disableFEC;

- (bool)fecActive
{
    return _fecActive;
}

- (id)init
{
    self = [super initWithPacketTime:20];
    if (self)
    {
        _disableFEC = NO;
        _percentLossToTriggerFEC = 5;
        _minimumReportsBeforeFEC = 2;
        
        _currentRTPSequenceNumber = -1;
        _lastRTPSequenceNumber = -1;
        
        _padep = [[FMIceLinkWebRTCBasicAudioPadep alloc] init];
    }
    return self;
}

- (NSMutableData *)encodeWithFrame:(FMIceLinkWebRTCAudioBuffer *)frame
{
    if (!_encoder)
    {
        _encoder = [[CocoaOpusEncoder alloc] initWithClockRate:self.clockRate channels:self.channels packetTime:self.packetTime];
        _encoder.quality = 0.5;
        _encoder.bitrate = 125;
    }
    
    CocoaOpusBuffer *buffer = [[CocoaOpusBuffer alloc] init];
    buffer.data = frame.data;
    buffer.index = frame.index;
    buffer.length = frame.length;
    return [_encoder encodeBuffer:buffer];
}

- (FMIceLinkWebRTCAudioBuffer *)decodeWithEncodedFrame:(NSMutableData *)encodedFrame
{
    if (!_decoder)
    {
        _decoder = [[CocoaOpusDecoder alloc] initWithClockRate:self.clockRate channels:self.channels packetTime:self.packetTime];
        [self.link getRemoteStream].disablePLC = YES;
    }
    
    if (_lastRTPSequenceNumber == -1)
    {
        _lastRTPSequenceNumber = _currentRTPSequenceNumber;
        return [self decodeNormalWithEncodedFrame:encodedFrame];
    }
    else
    {
        int sequenceNumberDelta = [FMIceLinkRTPPacket getSequenceNumberDeltaWithSequenceNumber:_currentRTPSequenceNumber lastSequenceNumber:_lastRTPSequenceNumber];
        if (sequenceNumberDelta <= 0)
        {
            return nil;
        }
        
        _lastRTPSequenceNumber = _currentRTPSequenceNumber;
        
        int missingPacketCount = sequenceNumberDelta - 1;
        NSMutableArray *previousFrames = [NSMutableArray arrayWithCapacity:missingPacketCount];
        
        int plcFrameCount = (missingPacketCount > 1) ? missingPacketCount - 1 : 0;
        if (plcFrameCount > 0)
        {
            [FMLog infoWithMessage:[NSString stringWithFormat:@"Adding %d frames of loss concealment to incoming audio stream. Packet sequence violated.", plcFrameCount]];
            for (int i = 0; i < plcFrameCount; i++)
            {
                [previousFrames addObject:[self decodePLC]];
            }
        }
        
        int fecFrameCount = (missingPacketCount > 0) ? 1 : 0;
        if (fecFrameCount > 0)
        {
            FMIceLinkWebRTCAudioBuffer *fecFrame = [self decodeFECWithEncodedFrame:encodedFrame];
            if (fecFrame == nil)
            {
                [previousFrames addObject:[self decodePLC]];
            }
            else
            {
                [previousFrames addObject:fecFrame];
            }
        }
        
        FMIceLinkWebRTCAudioBuffer *frame = [self decodeNormalWithEncodedFrame:encodedFrame];
        frame.previousBuffers = previousFrames;
        return frame;
    }
}

- (FMIceLinkWebRTCAudioBuffer *)decodePLC
{
    return [self decodeWithEncodedFrame:nil fec:NO];
}

- (FMIceLinkWebRTCAudioBuffer *)decodeFECWithEncodedFrame:(NSData *)encodedFrame
{
    return [self decodeWithEncodedFrame:encodedFrame fec:YES];
}

- (FMIceLinkWebRTCAudioBuffer *)decodeNormalWithEncodedFrame:(NSData *)encodedFrame
{
    return [self decodeWithEncodedFrame:encodedFrame fec:NO];
}

- (FMIceLinkWebRTCAudioBuffer *)decodeWithEncodedFrame:(NSData *)encodedFrame fec:(bool)fec
{
    CocoaOpusBuffer *buffer = [_decoder decodeFrame:encodedFrame fec:fec];
    if (buffer == nil)
    {
        return nil;
    }
    
    return [FMIceLinkWebRTCAudioBuffer audioBufferWithData:[NSMutableData dataWithBytesNoCopy:(void *)buffer.data.bytes length:buffer.data.length freeWhenDone:NO]
                                                     index:buffer.index
                                                    length:buffer.length];
}

- (NSMutableArray *)packetizeWithEncodedFrame:(NSMutableData *)encodedFrame
{
    return [_padep packetizeWithEncodedFrame:encodedFrame clockRate:self.clockRate packetTime:self.packetTime resetTimestamp:self.resetTimestamp];
}

- (NSMutableData *)depacketizeWithPacket:(FMIceLinkRTPPacket *)packet
{
    _currentRTPSequenceNumber = packet.sequenceNumber;
    
    return [_padep depacketizeWithPacket:packet];
}

- (void)processRTCPWithPackets:(NSMutableArray *)packets
{
    if (_encoder)
    {
        for (FMIceLinkRTCPPacket *packet in packets)
        {
            if ([packet isKindOfClass:[FMIceLinkRTCPReportPacket class]])
            {
                _reportsReceived++;
                
                FMIceLinkRTCPReportPacket *report = (FMIceLinkRTCPReportPacket *)packet;
                for (FMIceLinkRTCPReportBlock *block in report.reportBlocks)
                {
                    [FMLog debugWithMessage:[NSString stringWithFormat:@"Opus report: %0.2f %% packet loss (%d cumulative packets lost)", block.percentLost * 100, block.cumulativeNumberOfPacketsLost]];
                    if (block.percentLost > 0)
                    {
                        _losslessCount = 0;
                        _lossyCount++;
                        if (_lossyCount > 5 && _encoder.quality > 0.0)
                        {
                            _lossyCount = 0;
                            _encoder.quality = MAX(0.0, _encoder.quality - 0.1);
                            [FMLog infoWithMessage:[NSString stringWithFormat:@"Decreasing Opus encoder quality to %0.2f %%.", _encoder.quality * 100]];
                        }
                    }
                    else
                    {
                        _lossyCount = 0;
                        _losslessCount++;
                        if (_losslessCount > 5 && _encoder.quality < 1.0)
                        {
                            _losslessCount = 0;
                            _encoder.quality = MIN(1.0, _encoder.quality + 0.1);
                            [FMLog infoWithMessage:[NSString stringWithFormat:@"Increasing Opus encoder quality to %0.2f %%.", _encoder.quality * 100]];
                        }
                    }
                    
                    if (!_disableFEC && !_fecActive && _reportsReceived > _minimumReportsBeforeFEC)
                    {
                        if ((block.percentLost * 100) > _percentLossToTriggerFEC)
                        {
                            [FMLog infoWithMessage:@"Activating FEC for Opus audio stream."];
                            [_encoder activateFECWithPacketLossPercent:_percentLossToTriggerFEC];
                            _fecActive = true;
                        }
                    }
                }
            }
        }
    }
}

- (void)destroy
{
    if (_encoder)
    {
        [_encoder destroy];
        _encoder = nil;
    }
    
    if (_decoder)
    {
        [_decoder destroy];
        _decoder = nil;
    }
}

@end