#import <Foundation/Foundation.h>

#import "FM.h"
#import "FMIceLink.h"
#import "FMIceLinkWebRTC.h"

#import "CocoaOpusEncoder.h"
#import "CocoaOpusDecoder.h"

@interface OpusCodec : FMIceLinkWebRTCAudioCodec
{
    CocoaOpusEncoder *_encoder;
    CocoaOpusDecoder *_decoder;
    FMIceLinkWebRTCBasicAudioPadep *_padep;
    
    int _percentLossToTriggerFEC;
    bool _disableFEC;
    bool _fecActive;
    
    int _currentRTPSequenceNumber;
    int _lastRTPSequenceNumber;
    
    int _lossyCount;
    int _losslessCount;
    
    int _minimumReportsBeforeFEC;
    long long _reportsReceived;
}

@property int percentLossToTriggerFEC;
@property bool disableFEC;

- (id)init;
- (bool)fecActive;

@end