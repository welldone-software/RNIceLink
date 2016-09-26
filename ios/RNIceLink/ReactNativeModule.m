#import "RCTViewManager.h"
#import "RCTBridgeModule.h"

@interface RCT_EXTERN_MODULE(IceLinkConferenceManager, RCTViewManager)
  RCT_EXPORT_VIEW_PROPERTY(iceLinkServerAddress, NSString*)
  RCT_EXPORT_VIEW_PROPERTY(sessionId, NSString*)
  RCT_EXPORT_VIEW_PROPERTY(peerId, NSString*)
  RCT_EXPORT_VIEW_PROPERTY(receiveOfferAnswer, NSString*)
  RCT_EXPORT_VIEW_PROPERTY(receiveCandidate, NSString*)
  RCT_EXPORT_VIEW_PROPERTY(onOfferAnswer, RCTBubblingEventBlock)
  RCT_EXPORT_VIEW_PROPERTY(onCandidate, RCTBubblingEventBlock)
@end
