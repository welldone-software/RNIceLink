#import "Vp8Codec.h"

@implementation Vp8Codec

- (id)init
{
    self = [super init];
    if (self)
    {
        _padep = [[FMIceLinkWebRTCVp8Padep alloc] init];
    }
    return self;
}

- (NSMutableData *)encodeWithFrame:(FMIceLinkWebRTCVideoBuffer *)frame
{
    if (!_encoder)
    {
        _encoder = [[CocoaVp8Encoder alloc] init];
        _encoder.quality = 0.5;
        _encoder.bitrate = 320;
        //_encoder.scale = 1.0;
    }
    
    if (frame.resetKeyFrame)
    {
        [_encoder sendKeyframe];
    }
    
    // encode from YUV buffer
    NSMutableData *encodedFrame = [NSMutableData data];
    CocoaVp8Buffer *buffer = [[CocoaVp8Buffer alloc] init];
    FMIceLinkWebRTCVideoPlane *planeY = [frame.planes objectAtIndex:0];
    FMIceLinkWebRTCVideoPlane *planeU = [frame.planes objectAtIndex:1];
    FMIceLinkWebRTCVideoPlane *planeV = [frame.planes objectAtIndex:2];
    buffer.planeY = planeY.data;
    buffer.planeU = planeU.data;
    buffer.planeV = planeV.data;
    buffer.strideY = planeY.stride;
    buffer.strideU = planeU.stride;
    buffer.strideV = planeV.stride;
    buffer.width = frame.width;
    buffer.height = frame.height;
    if ([_encoder encodeBuffer:buffer toFrame:encodedFrame])
    {
        return encodedFrame;
    }
    return nil;
}

- (FMIceLinkWebRTCVideoBuffer *)decodeWithEncodedFrame:(NSMutableData *)encodedFrame
{
    if (!_decoder)
    {
        _decoder = [[CocoaVp8Decoder alloc] init];
    }
    
    if (_padep.sequenceNumberingViolated)
    {
        _decoder.needsKeyFrame = YES;
        return nil;
    }
    
    // decode to YUV buffer
    CocoaVp8Buffer *buffer = [[CocoaVp8Buffer alloc] init];
    if ([_decoder decodeFrame:encodedFrame toBuffer:buffer])
    {
        FMIceLinkWebRTCVideoPlane *planeY = [FMIceLinkWebRTCVideoPlane videoPlaneWithData:[NSMutableData dataWithData:buffer.planeY] stride:buffer.strideY];
        FMIceLinkWebRTCVideoPlane *planeU = [FMIceLinkWebRTCVideoPlane videoPlaneWithData:[NSMutableData dataWithData:buffer.planeU] stride:buffer.strideU];
        FMIceLinkWebRTCVideoPlane *planeV = [FMIceLinkWebRTCVideoPlane videoPlaneWithData:[NSMutableData dataWithData:buffer.planeV] stride:buffer.strideV];
        NSMutableArray *planes = [[NSMutableArray alloc] initWithObjects:planeY, planeU, planeV, nil];
        FMIceLinkWebRTCVideoBuffer *frame = [FMIceLinkWebRTCVideoBuffer videoBufferWithWidth:buffer.width height:buffer.height planes:planes format:FMIceLinkWebRTCVideoFormatI420];
        return frame;
    }
    return nil;
}

- (bool)decoderNeedsKeyFrame
{
    if (!_decoder)
    {
        return NO;
    }
    return _decoder.needsKeyFrame;
}

- (NSMutableArray *)packetizeWithEncodedFrame:(NSMutableData *)encodedFrame
{
    return [_padep packetizeWithEncodedFrame:encodedFrame clockRate:self.clockRate];
}

- (NSMutableData *)depacketizeWithPacket:(FMIceLinkRTPPacket *)packet
{
    return [_padep depacketizeWithPacket:packet];
}

- (void)processRTCPWithPackets:(NSMutableArray *)packets
{
    if (_encoder)
    {
        for (FMIceLinkRTCPPacket *packet in packets)
        {
            if ([packet isKindOfClass:[FMIceLinkRTCPPliPacket class]])
            {
                [FMLog infoWithMessage:@"Received PLI for video stream."];
                [_encoder sendKeyframe];
            }
            else if ([packet isKindOfClass:[FMIceLinkRTCPReportPacket class]])
            {
                FMIceLinkRTCPReportPacket *report = (FMIceLinkRTCPReportPacket *)packet;
                for (FMIceLinkRTCPReportBlock *block in report.reportBlocks)
                {
                    [FMLog debugWithMessage:[NSString stringWithFormat:@"VP8 report: %0.2f %% packet loss (%d cumulative packets lost)", block.percentLost * 100, block.cumulativeNumberOfPacketsLost]];
                    if (block.percentLost > 0)
                    {
                        _losslessCount = 0;
                        _lossyCount++;
                        if (_lossyCount > 5 && (_encoder.quality > 0.0 || _encoder.bitrate > 64 /* || _encoder.scale > 0.2 */))
                        {
                            _lossyCount = 0;
                            if (_encoder.quality > 0.0)
                            {
                                _encoder.quality = MAX(0.0, _encoder.quality - 0.1);
                                [FMLog infoWithMessage:[NSString stringWithFormat:@"Decreasing VP8 encoder quality to %0.2f%%.", _encoder.quality * 100]];
                            }
                            if (_encoder.bitrate > 64)
                            {
                                _encoder.bitrate = MAX(64, _encoder.bitrate - 64);
                                [FMLog infoWithMessage:[NSString stringWithFormat:@"Decreasing VP8 encoder bitrate to %d.", _encoder.bitrate]];
                            }
                            /*if (_encoder.scale > 0.2)
                            {
                                _encoder.scale = MAX(0.2, _encoder.scale - 0.2);
                                [FMLog infoWithMessage:[NSString stringWithFormat:@"Decreasing VP8 encoder scale to %0.2f%%.", _encoder.scale * 100]];
                            }*/
                        }
                    }
                    else
                    {
                        _lossyCount = 0;
                        _losslessCount++;
                        if (_losslessCount > 5 && (_encoder.quality < 1.0 || _encoder.bitrate < 640))
                        {
                            _losslessCount = 0;
                            if (_encoder.quality < 1.0)
                            {
                                _encoder.quality = MIN(1.0, _encoder.quality + 0.1);
                                [FMLog infoWithMessage:[NSString stringWithFormat:@"Increasing VP8 encoder quality to %0.2f%%.", _encoder.quality * 100]];
                            }
                            if (_encoder.bitrate < 640)
                            {
                                _encoder.bitrate = MIN(640, _encoder.bitrate + 64);
                                [FMLog infoWithMessage:[NSString stringWithFormat:@"Increasing VP8 encoder bitrate to %d.", _encoder.bitrate]];
                            }
                            /*if (_encoder.scale < 1.0)
                            {
                                _encoder.scale = MIN(1.0, _encoder.scale + 0.2);
                                [FMLog infoWithMessage:[NSString stringWithFormat:@"Increasing VP8 encoder scale to %0.2f%%.", _encoder.scale * 100]];
                            }*/
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