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
  
  @objc
  var iceLinkServerAddress: String? {
    didSet {
      if iceLinkServerAddress != nil {
        addConferenceLink()
      }
    }
  }
  
  @objc
  var receiveOfferAnswer: String? {
    didSet {
      if receiveOfferAnswer != nil {
        let conference = self.iceLinkConfrence.conference!
        let offerAnswer = FMIceLinkOfferAnswer.fromJson(withOfferAnswerJson: receiveOfferAnswer)
        conference.receive(offerAnswer, peerId: peerId)
      }
    }
  }
  
  @objc
  var receiveCandidate: String? {
    didSet {
      if receiveCandidate != nil {
        let conference = self.iceLinkConfrence.conference!
        let offerAnswer = FMIceLinkOfferAnswer.fromJson(withOfferAnswerJson: receiveOfferAnswer)
        conference.receive(offerAnswer, peerId: peerId)
      }
    }
  }
  
  @objc
  var onOfferAnswer: RCTBubblingEventBlock? {
    didSet {
      if onOfferAnswer != nil {
        let conference = self.iceLinkConfrence.conference!
        conference.add(onLinkOfferAnswer: { (args: FMIceLinkLinkOfferAnswerArgs?) in
          let json = FMIceLinkLinkOfferAnswerArgs.toJson(with: args)!          
          self.onOfferAnswer?(["offerAnswer": json])
        })
        
        addConferenceLink()
      }
    }
  }
  
  @objc
  var onCandidate: RCTBubblingEventBlock? {
    didSet {
      if onCandidate != nil {
        let conference = self.iceLinkConfrence.conference!
        conference.add(onLinkCandidateBlock: { (args: FMIceLinkLinkCandidateArgs?) in
          let candidate = ["candidate": FMIceLinkLinkCandidateArgs.toJson(with: args)]
          self.onCandidate!(candidate)
        })
        
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
  
  func isReadyForLink() -> Bool {
    return sessionId != nil
      && peerId != nil
      && iceLinkServerAddress != nil
      && onOfferAnswer != nil
  }
  
  func addConferenceLink() {
    if isReadyForLink() {
      iceLinkConfrence.sessionId = sessionId
      iceLinkConfrence.icelinkServerAddress = iceLinkServerAddress
      
      let conference = self.iceLinkConfrence.conference!
      if !conference.isLinked(withPeerId: peerId) {
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
