#import "IceLinkConference.h"

#import "OpusCodec.h"
#import "Vp8Codec.h"

@implementation IceLinkConference

@synthesize sessionId = _sessionId;
@synthesize icelinkServerAddress = _icelinkServerAddress;
@synthesize conference = _conference;

+ (IceLinkConference *)instance
{
  static IceLinkConference *instance = nil;
  static dispatch_once_t onceToken;
  dispatch_once(&onceToken, ^{
    instance = [[self alloc] init];
  });
  return instance;
}

- (id)init
{
  if (self = [super init])
  {
    // Log to the console.
    [FMLog setProvider:[FMNSLogProvider nsLogProviderWithLogLevel:FMLogLevelInfo]];

    // WebRTC has chosen VP8 as its mandatory video codec.
    // Since video encoding is best done using native code,
    // reference the video codec at the application-level.
    // This is required when using a WebRTC video stream.
    [FMIceLinkWebRTCVideoStream registerCodecWithEncodingName:@"VP8" createCodecBlock:^()
     {
       return [[Vp8Codec alloc] init];
     } preferred:YES];

    // For improved audio quality, we can use Opus. By
    // setting it as the preferred audio codec, it will
    // override the default PCMU/PCMA codecs.
    [FMIceLinkWebRTCAudioStream registerCodecWithEncodingName:@"opus" clockRate:48000 channels:2 createCodecBlock:^
     {
       return [[OpusCodec alloc] init];
     } preferred:YES];

    // To save time, generate a DTLS certificate when the
    // app starts and reuse it for multiple conferences.
    _certificate = [FMIceLinkCertificate generateCertificate];

    _addRemoteVideoControlEvent = [FMCallback callback:@selector(addRemoteVideoControl:) target:self];
    _removeRemoteVideoControlEvent = [FMCallback callback:@selector(removeRemoteVideoControl:) target:self];
    _logLinkInitEvent = [FMCallback callback:@selector(logLinkInit:) target:self];
    _logLinkUpEvent = [FMCallback callback:@selector(logLinkUp:) target:self];
    _logLinkDownEvent = [FMCallback callback:@selector(logLinkDown:) target:self];
  }
  return self;
}

- (void)startLocalMedia:(UIView *)videoContainer callback:(void (^)(NSString *))callback
{
  _localMedia = [[LocalMedia alloc] init];
  [_localMedia start:videoContainer callback:callback];
}

- (void)stopLocalMedia:(void (^)(NSString *)) callback
{
  if (_localMedia)
  {
    [_localMedia stop:callback];
    _localMedia = nil;
  }
  else
  {
    callback(nil);
  }
}

- (void)startConference
{
  // Create a WebRTC audio stream description (requires a
  // reference to the local audio feed).
  _audioStream = [[FMIceLinkWebRTCAudioStream alloc] initWithLocalStream:_localMedia.localMediaStream];

  // Create a WebRTC video stream description (requires a
  // reference to the local video feed). Whenever a P2P link
  // initializes using this description, position and display
  // the remote video control on-screen by passing it to the
  // layout manager created above. Whenever a P2P link goes
  // down, remove it.
  _videoStream = [[FMIceLinkWebRTCVideoStream alloc] initWithLocalStream:_localMedia.localMediaStream];
  [_videoStream addOnLinkInit:_addRemoteVideoControlEvent];
  [_videoStream addOnLinkDown:_removeRemoteVideoControlEvent];

  // Create a conference using our stream descriptions.
  _conference = [[FMIceLinkConference alloc]
                 initWithServerAddress:_icelinkServerAddress
                 streams:[NSMutableArray arrayWithObjects:_audioStream, _videoStream, nil]];

  // Use our pre-generated DTLS certificate.
  [_conference setDtlsCertificate:_certificate];

  // Supply TURN relay credentials in case we are behind a
  // highly restrictive firewall. These credentials will be
  // verified by the TURN server.
  [_conference setRelayUsername:@"roboteam"];
  [_conference setRelayPassword:@"roboteam"];

  // Add a few event handlers to the conference so we can see
  // when a new P2P link is created or changes state.
  [_conference addOnLinkInit:_logLinkInitEvent];
  [_conference addOnLinkUp:_logLinkUpEvent];
  [_conference addOnLinkDown:_logLinkDownEvent];
}

- (void)addRemoteVideoControl:(FMIceLinkStreamLinkInitArgs *)e
{
  UIView *remoteVideoControl = (UIView *)[e.link getRemoteVideoControl];
  [_localMedia.layoutManager addRemoteVideoControlWithPeerId:e.peerId remoteVideoControl:remoteVideoControl];
}

- (void)removeRemoteVideoControl:(FMIceLinkStreamLinkDownArgs *)e
{
  [_localMedia.layoutManager removeRemoteVideoControlWithPeerId:e.peerId];
}

- (void)logLinkInit:(FMIceLinkLinkInitArgs *)e
{
  [FMLog infoWithMessage:@"Link to peer initializing..."];
}

- (void)logLinkUp:(FMIceLinkLinkUpArgs *)e
{
  [FMLog infoWithMessage:@"Link to peer is UP."];
}

- (void)logLinkDown:(FMIceLinkLinkDownArgs *)e
{
  [FMLog infoWithMessage:[NSString stringWithFormat:@"Link to peer is DOWN. %@", e.exception.message]];
}

- (void)stopConference
{
     [_conference removeOnLinkInit:_logLinkInitEvent];
     [_conference removeOnLinkUp:_logLinkUpEvent];
     [_conference removeOnLinkDown:_logLinkDownEvent];
     _conference = nil;

     [_videoStream removeOnLinkInit:_addRemoteVideoControlEvent];
     [_videoStream removeOnLinkDown:_removeRemoteVideoControlEvent];
     _videoStream = nil;
     _audioStream = nil;
}

- (void)useNextVideoDevice
{
  [_localMedia.localMediaStream useNextVideoDevice];
}

- (void)pauseAudio
{
  [_localMedia.localMediaStream pauseAudio];
}

- (void)resumeAudio
{
  [_localMedia.localMediaStream resumeAudio];
}

@end
