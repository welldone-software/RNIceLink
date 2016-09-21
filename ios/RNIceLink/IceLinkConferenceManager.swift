import Foundation

@objc(IceLinkConferenceManager)
class IceLinkConferenceManager: RCTViewManager {
  override func view() -> UIView {
    return IceLinkConferenceView()
  }
}
