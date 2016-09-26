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
  var onOfferAnswer: RCTBubblingEventBlock?

  @objc
  var iceLinkServerAddress: String? {
    get {
      return iceLinkConfrence.icelinkServerAddress
    }
    
    set (value) {
      iceLinkConfrence.icelinkServerAddress = value
    }
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
  
  @objc
  var peerId: String? {
    didSet {
      if let peerId = peerId {
        let conference = self.iceLinkConfrence.conference!
        conference.link(withPeerId: peerId)
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
    let conference = iceLinkConfrence.conference!
    conference.add(onLinkOfferAnswer: { (args: FMIceLinkLinkOfferAnswerArgs?) in
      if let onOfferAnswer = self.onOfferAnswer {
        let offerAnswer = FMIceLinkLinkOfferAnswerArgs.toJson(with: args)
        onOfferAnswer(["offerAnswer": offerAnswer])
      }
    })
    
    conference.add(onLinkCandidateBlock: { (args: FMIceLinkLinkCandidateArgs?) in
      
    })
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
