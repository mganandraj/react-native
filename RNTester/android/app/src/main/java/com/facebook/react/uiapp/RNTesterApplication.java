/**
 * Copyright (c) 2015-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 *
 */

package com.facebook.react.uiapp;

import android.app.Application;

import com.facebook.infer.annotation.Assertions;
import com.facebook.react.ReactApplication;
import com.facebook.react.ReactInstanceManager;
import com.facebook.react.ReactInstanceManagerBuilder;
import com.facebook.react.ReactNativeHost;
import com.facebook.react.ReactPackage;
import com.facebook.react.common.LifecycleState;
import com.facebook.react.shell.MainReactPackage;

import java.util.Arrays;
import java.util.List;

import javax.annotation.Nullable;

public class RNTesterApplication extends Application implements ReactApplication {
  private final ReactNativeHost mReactNativeHost = new ReactNativeHost(this) {
    @Override
    public String getJSMainModuleName() {
      return "RNTester/js/RNTesterApp.android";
    }

    @Override
    public @Nullable String getBundleAssetName() {
      return "RNTesterApp.android.bundle";
    }

    @Override
    public boolean getUseDeveloperSupport() {
      return true;
    }

    @Override
    public List<ReactPackage> getPackages() {
      return Arrays.<ReactPackage>asList(
        new MainReactPackage()
      );
    }

    @Override
    protected ReactInstanceManager createReactInstanceManager() {
      ReactInstanceManagerBuilder builder = ReactInstanceManager.builder()
        .setApplication(RNTesterApplication.this)
        .setJSMainModulePath(getJSMainModuleName())
        .setUseDeveloperSupport(getUseDeveloperSupport())
        .setRedBoxHandler(getRedBoxHandler())
        .setUIImplementationProvider(getUIImplementationProvider())
        .setInitialLifecycleState(LifecycleState.RESUMED);

      for (ReactPackage reactPackage : getPackages()) {
        builder.addPackage(reactPackage);
      }

      String jsBundleFile = getJSBundleFile();
      if (jsBundleFile != null) {
        builder.setJSBundleFile(jsBundleFile);
      } else {
        builder.setBundleAssetName(Assertions.assertNotNull(getBundleAssetName()));
      }
      return builder.build();
    }
  };

  @Override
  public ReactNativeHost getReactNativeHost() {
    return mReactNativeHost;
  }



};
