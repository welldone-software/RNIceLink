package com.rnicelink;

import android.view.LayoutInflater;
import android.view.View;

import com.facebook.react.uimanager.SimpleViewManager;
import com.facebook.react.uimanager.ThemedReactContext;

public class IceLinkConferenceManager extends SimpleViewManager<View> {
  public IceLinkConferenceManager() {

  }

  @Override
  public String getName() {
    return "IceLinkConferenceManager";
  }

  @Override
  protected View createViewInstance(ThemedReactContext reactContext) {
    LayoutInflater layoutInflater = LayoutInflater.from(reactContext);
    View containerView = layoutInflater.inflate(R.layout.video_container, null);
    return containerView;
  }
}
