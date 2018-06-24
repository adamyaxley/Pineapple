#pragma once

#include <android/native_activity.h>

namespace pa
{
	namespace AndroidBridge
	{
		ANativeActivity* getNativeActivity();

		void setNativeActivity(ANativeActivity* activity);

		const char* getInternalDataPath();
	}
}
