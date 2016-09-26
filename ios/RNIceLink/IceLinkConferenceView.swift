import Foundation

class IceLinkConferenceView: UIView {
  let iceLinkConfrence = IceLinkConference.instance()!
  
  init() {
    super.init(frame: CGRect())
    startLocalMedia()
    startConference()
  }
  
  required init?(coder aDecoder: NSCoder) {
    fatalError("init(coder:) has not been implemented")
  }

  @objc
  var onOfferAnswer: RCTBubblingEventBlock? {
    didSet {
      if onOfferAnswer != nil {
        addConferenceLink()
      }
    }
  }

  @objc
  var iceLinkServerAddress: String? {
    didSet {
      if iceLinkServerAddress != nil {
        addConferenceLink()
      }
    }
  }
  
  @objc
  var sessionId: String? {
    didSet {
      if sessionId != nil {
        addConferenceLink()
      }
    }
  }
  
  @objc
  var peerId: String? {
    didSet {
      if peerId != nil {
        addConferenceLink()
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
    iceLinkConfrence.startConference()    
  }

  func addConferenceLink() {
    if let sessionId = self.sessionId,
      let peerId = self.peerId,
      let iceLinkServerAddress = self.iceLinkServerAddress,
      let onOfferAnswer = self.onOfferAnswer {
      
      let conference = self.iceLinkConfrence.conference!
      if !conference.isLinked(withPeerId: peerId) {
          iceLinkConfrence.sessionId = sessionId
          iceLinkConfrence.icelinkServerAddress = iceLinkServerAddress

          conference.add(onLinkOfferAnswer: { (args: FMIceLinkLinkOfferAnswerArgs?) in
            let offerAnswer = FMIceLinkLinkOfferAnswerArgs.toJson(with: args)
            onOfferAnswer(["offerAnswer": offerAnswer])
          })
          
          conference.link(withPeerId: peerId)
      }
    }
  }

  func stopConference() {
    iceLinkConfrence.stopConference()
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
