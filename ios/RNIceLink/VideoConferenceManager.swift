import Foundation

@objc(VideoConferenceManager)
class VideoConferenceManager: RCTViewManager {
  let videoContainer = UIView()
  let videoConfrence = VideoConference()

  override init() {
  }

  func startSignalling() {
    videoConfrence.startSignalling { message in
      NSLog("startSignalling failed. error (@)", message)
    }
  }

  func stopSignalling() {
    videoConfrence.stopSignalling { message in
      NSLog("stopSignalling failed. error (@)", message)
    }
  }

  func startLocalMedia() {
    videoConfrence.startLocalMedia(videoContainer) { message in
      NSLog("startLocalMedia failed. error (@)", message)
    }
  }

  func stopLocalMedia() {
    videoConfrence.stopLocalMedia { message in
      NSLog("stopLocalMedia failed. error (@)", message)
    }
  }

  func startConference() {
    videoConfrence.startConference { message in
      NSLog("startConference failed. error (@)", message)
    }
  }

  func stopConference() {
    videoConfrence.stopConference { message in
      NSLog("stopConference failed. error (@)", message)
    }
  }

  func useNextVideoDevice() {
    videoConfrence.useNextVideoDevice()
  }

  func pauseAudio() {
    videoConfrence.pauseAudio()
  }

  func resumeAudio() {
    videoConfrence.resumeAudio()
  }

  override func view() -> UIView {


    return videoContainer
  }
}
