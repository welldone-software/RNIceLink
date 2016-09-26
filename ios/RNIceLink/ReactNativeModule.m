#import "RCTViewManager.h"
#import "RCTBridgeModule.h"

@interface RCT_EXTERN_MODULE(IceLinkConferenceManager, RCTViewManager)
  RCT_EXPORT_VIEW_PROPERTY(iceLinkServerAddress, NSString*)
  RCT_EXPORT_VIEW_PROPERTY(sessionId, NSString*)
  RCT_EXPORT_VIEW_PROPERTY(peerId, NSString*)
  RCT_EXPORT_VIEW_PROPERTY(onOfferAnswer, RCTBubblingEventBlock)
@end
