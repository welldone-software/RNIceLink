package com.rnicelink;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import com.facebook.react.uimanager.SimpleViewManager;
import com.facebook.react.uimanager.ThemedReactContext;
import fm.SingleAction;
import fm.icelink.webrtc.DefaultProviders;

public class IceLinkConferenceManager extends SimpleViewManager<View> {
  private Logger logger = Logger.get("IceLink");

  @Override
  public String getName() {
    return "IceLinkConference";
  }

  @Override
  protected View createViewInstance(ThemedReactContext reactContext) {
    LayoutInflater layoutInflater = LayoutInflater.from(reactContext);
    ViewGroup videoContainer = (ViewGroup) layoutInflater.inflate(R.layout.video_container, null);
    startSignalling();
    startLocalMedia(videoContainer);
    return videoContainer;
  }

  private void startSignalling() {
    try {
      IceLinkConference iceLinkConference = IceLinkConference.getInstance();
      iceLinkConference.startSignalling(new SingleAction<String>() {
        @Override
        public void invoke(String error) {
          if (error != null) {
            logger.error("startSignalling failed. error:" + error);
          }
        }
      });
    } catch (Exception e) {
      logger.error(e);
    }
  }

  private void stopSignalling() {
    try {
      IceLinkConference iceLinkConference = IceLinkConference.getInstance();
      iceLinkConference.stopSignalling(new SingleAction<String>() {
        @Override
        public void invoke(String error) {
          if (error != null) {
            logger.error("stopSignalling failed. error:" + error);
          }
        }
      });
    } catch (Exception e) {
      logger.error(e);
    }
  }

  private void startLocalMedia(ViewGroup videoContainer) {
    try {
      DefaultProviders.setAndroidContext(videoContainer.getContext());
      IceLinkConference iceLinkConference = IceLinkConference.getInstance();
      iceLinkConference.startLocalMedia(videoContainer, new SingleAction<String>() {
        @Override
        public void invoke(String error) {
          if (error != null) {
            logger.error("startLocalMedia failed. error:" + error);
          }
        }
      });
    } catch (Exception e) {
      logger.error(e);
    }
  }

  private void stopLocalMedia() {
    try {
      IceLinkConference iceLinkConference = IceLinkConference.getInstance();
      iceLinkConference.stopLocalMedia(new SingleAction<String>() {
        @Override
        public void invoke(String error) {
          if (error != null) {
            logger.error("stopLocalMedia failed. error:" + error);
          }
        }
      });
    } catch (Exception e) {
      logger.error(e);
    }
  }

  private void startConference() {
    try {
      IceLinkConference iceLinkConference = IceLinkConference.getInstance();
      iceLinkConference.startConference(new SingleAction<String>() {
        @Override
        public void invoke(String error) {
          if (error != null) {
            logger.error("startConference failed. error:" + error);
          }
        }
      });
    } catch (Exception e) {
      logger.error(e);
    }
  }

  private void stopConference() {
    try {
      IceLinkConference iceLinkConference = IceLinkConference.getInstance();
      iceLinkConference.stopConference(new SingleAction<String>() {
        @Override
        public void invoke(String error) {
          if (error != null) {
            logger.error("stopConference failed. error:" + error);
          }
        }
      });
    } catch (Exception e) {
      logger.error(e);
    }
  }
}
