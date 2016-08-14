import Foundation

@objc(VideoConferenceManager)
class VideoConferenceManager: RCTViewManager {

  override init () {
    FMLog.setProvider(FMNSLogProvider(logLevel:FMLogLevelInfo))

    FMIceLinkWebRTCVideoStream.registerCodecWithEncodingName(
      "VP8",
      createCodecBlock: { Vp8Codec() },
      preferred: true)

    FMIceLinkWebRTCAudioStream.registerCodecWithEncodingName(
      "opus",
      clockRate:48000,
      channels:2,
      createCodecBlock: { OpusCodec() },
      preferred: true)

  }

  override func view() -> UIView {
    let videoConfrence = VideoConference()
    videoConfrence.startReceiverMedia()
    return videoConfrence.view
  }
}
