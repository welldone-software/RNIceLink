import Foundation

class IceLinkConferenceView: UIView {
  let iceLinkConfrence = IceLinkConference()
  
  init() {
    super.init(frame: CGRect())
    startSignalling()
    startLocalMedia()
    startConference()
  }
  
  required init?(coder aDecoder: NSCoder) {
    fatalError("init(coder:) has not been implemented")
  }

  @objc
  var sessionId: String? {
    get {
      return iceLinkConfrence.sessionId
    }
    
    set (value) {
      iceLinkConfrence.sessionId = value
    }
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
    iceLinkConfrence.startLocalMedia(self) { message in
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
    iceLinkConfrence.start { message in
      if let message = message {
        NSLog("startConference failed. error (%@)", message)
      }
    }
  }

  func stopConference() {
    iceLinkConfrence.stop { message in
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
}
