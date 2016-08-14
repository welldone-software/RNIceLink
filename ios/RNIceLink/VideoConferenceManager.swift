import Foundation

@objc(VideoConferenceManager)
class VideoConferenceManager: RCTViewManager {
  let containerView = UIView()

  override func view() -> UIView {
    let videoConfrence = VideoConference()
    
    return containerView
  }
}
