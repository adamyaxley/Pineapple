#pragma once

#include <Pineapple/Platform/Android/AndroidBridge.h>
#include <android/native_activity.h>
#include <jni.h>

namespace pa
{
	class ScopedEnvJNI
	{
	public:

		ScopedEnvJNI();
		~ScopedEnvJNI();

		JNIEnv* get() { return m_env; }

		// Finds any class using the class loader object provided by the native activity
		// Specify classes in the form com.package.class
		jclass findClass(const char* path);

		// Returns the size of a jobject
		//long getObjectSize(jobject object);

		bool handleExceptions();

	private:

		ANativeActivity * m_activity;

		JNIEnv* m_env;

		bool m_detach;
	};
}
