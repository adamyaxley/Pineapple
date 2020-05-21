#pragma once

#include <android/native_activity.h>
#include <android_native_app_glue.h>

namespace pa
{
	namespace AndroidBridge
	{
		ANativeActivity* getNativeActivity();

		android_app* getAndroidApp();

		void setAndroidApp(android_app* state);

		const char* getInternalDataPath();

		JNIEnv* getEnv();
	}
}
