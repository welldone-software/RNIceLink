import Foundation

@objc(IceLinkConferenceManager)
class IceLinkConferenceManager: RCTViewManager {
  @IBOutlet var videoContainer: UIView!

  let iceLinkConfrence = IceLinkConference()

  override init() {
    super.init()
    NSBundle.mainBundle().loadNibNamed("VideoContainer", owner: self, options: nil)
    iceLinkConfrence.sessionId = "090909"
    startSignalling()
    startLocalMedia()
    startConference()
  }

  func startSignalling() {
    iceLinkConfrence.startSignalling { message in
      if let message = message {
        NSLog("startSignalling failed. error (%@)", message)
      }
    }
  }

  func stopSignalling() {
    iceLinkConfrence.stopSignalling { message in
      if let message = message {
        NSLog("stopSignalling failed. error (%@)", message)
      }
    }
  }

  func startLocalMedia() {
    iceLinkConfrence.startLocalMedia(videoContainer) { message in
      if let message = message {
        NSLog("startLocalMedia failed. error (%@)", message)
      }
    }
  }

  func stopLocalMedia() {
    iceLinkConfrence.stopLocalMedia { message in
      if let message = message {
        NSLog("stopLocalMedia failed. error (%@)", message)
      }
    }
  }

  func startConference() {
    iceLinkConfrence.startConference { message in
      if let message = message {
        NSLog("startConference failed. error (%@)", message)
      }
    }
  }

  func stopConference() {
    iceLinkConfrence.stopConference { message in
      if let message = message {
        NSLog("stopConference failed. error (%@)", message)
      }
    }
  }

  func useNextVideoDevice() {
    iceLinkConfrence.useNextVideoDevice()
  }

  func pauseAudio() {
    iceLinkConfrence.pauseAudio()
  }

  func resumeAudio() {
    iceLinkConfrence.resumeAudio()
  }

  override func view() -> UIView {


    return videoContainer
  }
}
