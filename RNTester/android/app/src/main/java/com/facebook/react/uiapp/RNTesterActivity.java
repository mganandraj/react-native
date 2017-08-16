package com.facebook.react.uiapp;

import javax.annotation.Nullable;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.provider.Settings;
import android.util.Log;
import android.widget.Toast;

import com.facebook.react.ReactApplication;
import com.facebook.react.ReactInstanceManager;
import com.facebook.react.ReactNativeHost;
import com.facebook.react.ReactRootView;
import com.facebook.react.common.ReactConstants;
import com.facebook.react.modules.core.DefaultHardwareBackBtnHandler;

/**
 * Base Activity for React Native applications.
 */
public class RNTesterActivity extends Activity implements DefaultHardwareBackBtnHandler {

  private final int REQUEST_OVERLAY_PERMISSION_CODE = 1111;

  private static final String REDBOX_PERMISSION_GRANTED_MESSAGE =

    "Overlay permissions have been granted.";

  private static final String REDBOX_PERMISSION_MESSAGE =

    "Overlay permissions needs to be granted in order for react native apps to run in dev mode";

  /**
   * Returns the name of the main component registered from JavaScript.
   * This is used to schedule rendering of the component.
   * e.g. "MoviesApp"
   */
  protected @Nullable String getMainComponentName() {
    return "RNTesterApp";
  }


  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);

    boolean needsOverlayPermission = false;

    if (getReactNativeHost().getUseDeveloperSupport() && Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
      // Get permission to show redbox in dev builds.

      if (!Settings.canDrawOverlays(this)) {
        needsOverlayPermission = true;
        Intent serviceIntent = new Intent(Settings.ACTION_MANAGE_OVERLAY_PERMISSION, Uri.parse("package:" + getPackageName()));
        Log.w(ReactConstants.TAG, REDBOX_PERMISSION_MESSAGE);
        Toast.makeText(this, REDBOX_PERMISSION_MESSAGE, Toast.LENGTH_LONG).show();
        startActivityForResult(serviceIntent, REQUEST_OVERLAY_PERMISSION_CODE);
      }
    }

    if (getMainComponentName() != null && !needsOverlayPermission) {
      loadApp(getMainComponentName());
    }
  }

   protected final ReactNativeHost getReactNativeHost() {
     return ((ReactApplication) getApplication()).getReactNativeHost();
  }

  protected final ReactInstanceManager getReactInstanceManager() {
    return getReactNativeHost().getReactInstanceManager();
  }

  protected final void loadApp(String appKey) {
    mReactRootView = new ReactRootView(this);
    mReactRootView.startReactApplication(
      getReactNativeHost().getReactInstanceManager(),
      appKey,
      getLaunchOptions());

    setContentView(mReactRootView);
  }

  protected @Nullable Bundle getLaunchOptions() {
    return null;
  }

  private @Nullable
  ReactRootView mReactRootView;

  @Override
  protected void onPause() {
    super.onPause();

    if (getReactNativeHost().hasInstance()) {
      getReactNativeHost().getReactInstanceManager().onHostPause(this);
    }
  }



  @Override
  protected void onResume() {
    super.onResume();

    if (getReactNativeHost().hasInstance()) {
      getReactNativeHost().getReactInstanceManager().onHostResume(this, this);
    }
  }



  @Override
  protected void onDestroy() {
    super.onDestroy();

    if (getReactNativeHost().hasInstance()) {
      getReactNativeHost().getReactInstanceManager().onHostDestroy(this);
    }
  }


  @Override
  public void invokeDefaultOnBackPressed() {
    super.onBackPressed();
  }

  @Override
  public void onBackPressed() {
    if (getReactNativeHost().hasInstance()) {
      getReactNativeHost().getReactInstanceManager().onBackPressed();
    } else {
      super.onBackPressed();
    }
  }
}
