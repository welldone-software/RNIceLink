import Foundation

@objc(IceLinkConferenceManager)
class IceLinkConferenceManager: RCTViewManager {
  let videoContainer = UIView()
  let iceLinkConfrence = IceLinkConference()

  func startSignalling() {
    iceLinkConfrence.startSignalling { message in
      NSLog("startSignalling failed. error (@)", message)
    }
  }

  func stopSignalling() {
    iceLinkConfrence.stopSignalling { message in
      NSLog("stopSignalling failed. error (@)", message)
    }
  }

  func startLocalMedia() {
    iceLinkConfrence.startLocalMedia(videoContainer) { message in
      NSLog("startLocalMedia failed. error (@)", message)
    }
  }

  func stopLocalMedia() {
    iceLinkConfrence.stopLocalMedia { message in
      NSLog("stopLocalMedia failed. error (@)", message)
    }
  }

  func startConference() {
    iceLinkConfrence.startConference { message in
      NSLog("startConference failed. error (@)", message)
    }
  }

  func stopConference() {
    iceLinkConfrence.stopConference { message in
      NSLog("stopConference failed. error (@)", message)
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
