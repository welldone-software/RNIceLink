package com.rnicelink;

import android.view.View;
import android.view.ViewGroup;
import java.util.Locale;
import aopus.OpusCodec;
import aopus.OpusEchoCanceller;
import avp8.Vp8Codec;
import fm.AndroidLogProvider;
import fm.EmptyFunction;
import fm.Log;
import fm.LogLevel;
import fm.SingleAction;
import fm.icelink.Certificate;
import fm.icelink.Conference;
import fm.icelink.LinkDownArgs;
import fm.icelink.LinkInitArgs;
import fm.icelink.LinkUpArgs;
import fm.icelink.Stream;
import fm.icelink.StreamLinkDownArgs;
import fm.icelink.StreamLinkInitArgs;
import fm.icelink.webrtc.AndroidAudioCaptureProvider;
import fm.icelink.webrtc.AudioCodec;
import fm.icelink.webrtc.AudioStream;
import fm.icelink.webrtc.LinkExtensions;
import fm.icelink.webrtc.VideoCodec;
import fm.icelink.webrtc.VideoStream;

/*
 * Make sure you add permission to access CAMERA and RECORD_AUDIO
 * to your Android application manifest (AndroidManifest.xml):
 *   <uses-permission android:name="android.permission.CAMERA"/>
 *   <uses-permission android:name="android.permission.RECORD_AUDIO"/>
 */

public class IceLinkConference {
  private String icelinkServerAddress = "demo.icelink.fm:3478";
  private String websyncServerUrl = "http://v4.websync.fm/websync.ashx"; // WebSync On-Demand

  private Signalling signalling;
  private LocalMedia localMedia;

  private AudioStream audioStream;
  private VideoStream videoStream;
  private Conference conference;

  private String sessionId;

  public String getSessionId() {
    return this.sessionId;
  }

  public void setSessionId(String sid) {
    this.sessionId = sid;
  }

  private boolean enableSoftwareEchoCancellation = OpusEchoCanceller.isSupported();
  private OpusEchoCanceller opusEchoCanceller = null;
  private int opusClockRate = 48000;
  private int opusChannels = 2;

  private Certificate certificate;

  private SingleAction<LinkInitArgs> logLinkInitEvent;
  private SingleAction<LinkUpArgs> logLinkUpEvent;
  private SingleAction<LinkDownArgs> logLinkDownEvent;
  private SingleAction<StreamLinkInitArgs> addRemoteVideoControlEvent;
  private SingleAction<StreamLinkDownArgs> removeRemoteVideoControlEvent;

  private IceLinkConference() throws Exception {
    logLinkInitEvent = new SingleAction<LinkInitArgs>() {
      public void invoke(LinkInitArgs e) {
        logLinkInit(e);
      }
    };
    logLinkUpEvent = new SingleAction<LinkUpArgs>() {
      public void invoke(LinkUpArgs e) {
        logLinkUp(e);
      }
    };
    logLinkDownEvent = new SingleAction<LinkDownArgs>() {
      public void invoke(LinkDownArgs e) {
        logLinkDown(e);
      }
    };
    addRemoteVideoControlEvent = new SingleAction<StreamLinkInitArgs>() {
      public void invoke(StreamLinkInitArgs e) {
        addRemoteVideoControl(e);
      }
    };
    removeRemoteVideoControlEvent = new SingleAction<StreamLinkDownArgs>() {
      public void invoke(StreamLinkDownArgs e) {
        removeRemoteVideoControl(e);
      }
    };

    // Log to the Android console.
    Log.setProvider(new AndroidLogProvider(LogLevel.Info));

    // WebRTC has chosen VP8 as its mandatory video codec.
    // Since video encoding is best done using native code,
    // reference the video codec at the application-level.
    // This is required when using a WebRTC video stream.
    VideoStream.registerCodec("VP8", new EmptyFunction<VideoCodec>() {
      public VideoCodec invoke() {
        return new Vp8Codec();
      }
    }, true);

    // For improved audio quality, we can use Opus. By
    // setting it as the preferred audio codec, it will
    // override the default PCMU/PCMA codecs.
    AudioStream.registerCodec("opus", opusClockRate, opusChannels, new EmptyFunction<AudioCodec>() {
      public AudioCodec invoke() {
        if (enableSoftwareEchoCancellation) {
          return new OpusCodec(opusEchoCanceller);
        } else {
          return new OpusCodec();
        }
      }
    }, true);

    if (!enableSoftwareEchoCancellation) {
      AndroidAudioCaptureProvider.setDefaultUseAcousticEchoCanceler(true);
    }

    // To save time, generate a DTLS certificate when the
    // app starts and reuse it for multiple conferences.
    certificate = Certificate.generateCertificate();
  }

  private static IceLinkConference iceLinkConference;

  public static synchronized IceLinkConference getInstance() throws Exception {
    if (iceLinkConference == null) {
      iceLinkConference = new IceLinkConference();
    }
    return iceLinkConference;
  }

  public void startSignalling(SingleAction<String> callback) throws Exception {
    signalling = new Signalling(websyncServerUrl);
    signalling.start(callback);
  }

  public void stopSignalling(SingleAction<String> callback) throws Exception {
    signalling.stop(callback);
    signalling = null;
  }

  public void startLocalMedia(ViewGroup videoContainer, SingleAction<String> callback) throws Exception {
    localMedia = new LocalMedia();
    localMedia.start(videoContainer, callback);
  }

  public void stopLocalMedia(SingleAction<String> callback) throws Exception {
    localMedia.stop(callback);
    localMedia = null;
  }

  public void startConference(SingleAction<String> callback) throws Exception {
    // Create a WebRTC audio stream description (requires a
    // reference to the local audio feed).
    audioStream = new AudioStream(localMedia.getLocalMediaStream());

    // Create a WebRTC video stream description (requires a
    // reference to the local video feed). Whenever a P2P link
    // initializes using this description, position and display
    // the remote video control on-screen by passing it to the
    // layout manager created above. Whenever a P2P link goes
    // down, remove it.
    videoStream = new VideoStream(localMedia.getLocalMediaStream());
    videoStream.addOnLinkInit(addRemoteVideoControlEvent);
    videoStream.addOnLinkDown(removeRemoteVideoControlEvent);

    // Create a new IceLink conference.
    conference = new Conference(icelinkServerAddress, new Stream[]{audioStream, videoStream});

    // Use our pre-generated DTLS certificate.
    conference.setDtlsCertificate(certificate);

    // Supply TURN relay credentials in case we are behind a
    // highly restrictive firewall. These credentials will be
    // verified by the TURN server.
    conference.setRelayUsername("test");
    conference.setRelayPassword("pa55w0rd!");

    // Add a few event handlers to the conference so we can see
    // when a new P2P link is created or changes state.
    conference.addOnLinkInit(logLinkInitEvent);
    conference.addOnLinkUp(logLinkUpEvent);
    conference.addOnLinkDown(logLinkDownEvent);

    // Start echo canceller.
    if (enableSoftwareEchoCancellation) {
      opusEchoCanceller = new OpusEchoCanceller(opusClockRate, opusChannels);
      opusEchoCanceller.start();
    }

    // Attach signalling to the conference.
    signalling.attach(conference, sessionId, callback);
  }

  private void addRemoteVideoControl(StreamLinkInitArgs e) {
    try {
      View remoteVideoControl = (View) LinkExtensions.getRemoteVideoControl(e.getLink());
      localMedia.getLayoutManager().addRemoteVideoControl(e.getPeerId(), remoteVideoControl);
    } catch (Exception ex) {
      Log.error("Could not add remote video control.", ex);
    }
  }

  private void removeRemoteVideoControl(StreamLinkDownArgs e) {
    try {
      if (localMedia != null && localMedia.getLayoutManager() != null) {
        localMedia.getLayoutManager().removeRemoteVideoControl(e.getPeerId());
      }
    } catch (Exception ex) {
      Log.error("Could not remove remote video control.", ex);
    }
  }

  private void logLinkInit(LinkInitArgs e) {
    Log.info("Link to peer initializing...");
  }

  private void logLinkUp(LinkUpArgs e) {
    Log.info("Link to peer is UP.");
  }

  private void logLinkDown(LinkDownArgs e) {
    Log.info(String.format(Locale.getDefault(), "Link to peer is DOWN. %s", e.getException().getMessage()));
  }

  public void stopConference(final SingleAction<String> callback) throws Exception {
    // Detach signalling from the conference.
    signalling.detach(new SingleAction<String>() {
      public void invoke(String error) {
        // Stop echo canceller.
        if (enableSoftwareEchoCancellation) {
          opusEchoCanceller.stop();
          opusEchoCanceller = null;
        }

        conference.removeOnLinkInit(logLinkInitEvent);
        conference.removeOnLinkUp(logLinkUpEvent);
        conference.removeOnLinkDown(logLinkDownEvent);
        conference = null;

        videoStream.removeOnLinkInit(addRemoteVideoControlEvent);
        videoStream.removeOnLinkDown(removeRemoteVideoControlEvent);
        videoStream = null;

        audioStream = null;

        callback.invoke(error);
      }
    });
  }

  public void useNextVideoDevice() {
    localMedia.getLocalMediaStream().useNextVideoDevice();
  }

  public void pauseLocalVideo() {
    localMedia.getLocalMediaStream().pauseVideo();
  }

  public void resumeLocalVideo() {
    localMedia.getLocalMediaStream().resumeVideo();
  }
}
