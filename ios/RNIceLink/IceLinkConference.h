#import <Foundation/Foundation.h>

#import "FM.h"
#import "FMIceLink.h"
#import "FMIceLinkWebRTC.h"

#import "Signalling.h"
#import "LocalMedia.h"

@interface IceLinkConference : NSObject
{
  LocalMedia *_localMedia;

  FMIceLinkWebRTCAudioStream *_audioStream;
  FMIceLinkWebRTCVideoStream *_videoStream;

  FMIceLinkConference *_conference;

  NSString *_sessionId;
  NSString *_icelinkServerAddress;

  FMIceLinkCertificate *_certificate;

  FMCallback *_addRemoteVideoControlEvent;
  FMCallback *_removeRemoteVideoControlEvent;
  FMCallback *_logLinkInitEvent;
  FMCallback *_logLinkUpEvent;
  FMCallback *_logLinkDownEvent;
}

@property (nonatomic, retain) NSString *sessionId;
@property (nonatomic, retain) NSString *icelinkServerAddress;
@property (nonatomic, retain) FMIceLinkConference *conference;

+ (IceLinkConference *)instance;

- (void)startLocalMedia:(UIView *)videoContainer callback:(void (^)(NSString *))callback;
- (void)stopLocalMedia:(void (^)(NSString *))callback;
- (void)startConference;
- (void)stopConference;
- (void)useNextVideoDevice;
- (void)pauseAudio;
- (void)resumeAudio;

@end
