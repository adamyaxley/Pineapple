package com.pineapple;

import android.app.Activity;
import android.content.Intent;
import android.util.Log;
import android.os.Bundle;
import android.content.res.Configuration;
import android.content.pm.ActivityInfo;
import android.view.View;

import com.pineapple.util.paUtil;

//import com.google.android.gms.common.GooglePlayServicesUtil;
//import com.google.android.gms.common.ConnectionResult;

public class paNativeActivity extends android.app.NativeActivity
{
	void setImmersiveSticky() {
		View decorView = getWindow().getDecorView();
		decorView.setSystemUiVisibility(View.SYSTEM_UI_FLAG_FULLSCREEN
				| View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
				| View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY
				| View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
				| View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
				| View.SYSTEM_UI_FLAG_LAYOUT_STABLE);
	}

	//public static int PLAY_SERVICES_RESOLUTION_REQUEST = 91745821;
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);
        Log.d(paUtil.TAG, "onActivityResult(" + requestCode + "," + resultCode + "," + data);
		nativeOnActivityResult(this, requestCode,resultCode, data);
    }
	
	static {
		System.loadLibrary("NinjaCat");
	}
	
	private void requestCorrectOrientation()
	{
		setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE); // FORCE LANDSCAPE
	}
	
	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		requestCorrectOrientation();

		// Hide toolbar
		int SDK_INT = android.os.Build.VERSION.SDK_INT;
		if (SDK_INT >= 19) {
			setImmersiveSticky();

			View decorView = getWindow().getDecorView();
			decorView
					.setOnSystemUiVisibilityChangeListener(new View.OnSystemUiVisibilityChangeListener() {
						@Override
						public void onSystemUiVisibilityChange(int visibility) {
							setImmersiveSticky();
						}
					});
		}

		nativeOnActivityCreated(this, savedInstanceState);
	}

	protected void onDestroy() {
		super.onDestroy();
		requestCorrectOrientation();
		nativeOnActivityDestroyed(this);
	}

	protected void onPause() {
		super.onPause();
		requestCorrectOrientation();
		nativeOnActivityPaused(this);
	}

	protected void onResume() {
		super.onResume();
		requestCorrectOrientation();

		// Hide toolbar
		int SDK_INT = android.os.Build.VERSION.SDK_INT;
		if (SDK_INT >= 11 && SDK_INT < 14) {
			getWindow().getDecorView().setSystemUiVisibility(
					View.STATUS_BAR_HIDDEN);
		} else if (SDK_INT >= 14 && SDK_INT < 19) {
			getWindow().getDecorView().setSystemUiVisibility(
					View.SYSTEM_UI_FLAG_FULLSCREEN
							| View.SYSTEM_UI_FLAG_LOW_PROFILE);
		} else if (SDK_INT >= 19) {
			setImmersiveSticky();
		}

		nativeOnActivityResumed(this);
		
		/*int result = GooglePlayServicesUtil.isGooglePlayServicesAvailable(this);
		if (result != ConnectionResult.SUCCESS) {
			if (GooglePlayServicesUtil.isUserRecoverableError(result)) {
				Log.i(paUtil.TAG, "Google play services not present or up to date. showing dialog");
				GooglePlayServicesUtil.getErrorDialog(result, this, PLAY_SERVICES_RESOLUTION_REQUEST).show();
			} else {
				// Device not supported (either quit or disable google play services for this device)
				Log.i(paUtil.TAG, "Google play services not supported on this device");
				finish();
			}
		} else {
			Log.i(paUtil.TAG, "Google play services present and up to date. Yay!");
		}*/
	}

	protected void onStart(){
		super.onStart();
		requestCorrectOrientation();
		nativeOnActivityStarted(this);
	}

	protected void onStop(){
		super.onStop();
		requestCorrectOrientation();
		nativeOnActivityStopped(this);
	}

	protected void onSaveInstanceState(Bundle outState) {
		super.onSaveInstanceState(outState);
		nativeOnActivitySaveInstanceState(this, outState);
	}
	
	@Override
	public void onConfigurationChanged(Configuration newConfig) {
		super.onConfigurationChanged(newConfig);
		requestCorrectOrientation();
	}

	// Implemented in C++.
	public static native void nativeOnActivityResult(Activity activity, int requestCode, int resultCode, Intent data);

	public static native void nativeOnActivityCreated(Activity activity, Bundle savedInstanceState);

	private static native void nativeOnActivityDestroyed(Activity activity);

	private static native void nativeOnActivityPaused(Activity activity);

	private static native void nativeOnActivityResumed(Activity activity);

	private static native void nativeOnActivitySaveInstanceState(Activity activity, Bundle outState);

	private static native void nativeOnActivityStarted(Activity activity);

	private static native void nativeOnActivityStopped(Activity activity);
}