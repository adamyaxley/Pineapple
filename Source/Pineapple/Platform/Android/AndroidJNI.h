#pragma once
#include <jni.h>

namespace pa
{
	namespace AndroidJNI
	{
		jint initGlobalJniVariables(JavaVM* jvm);

		JNIEnv* attachCurrentThreadIfNeeded();

		bool handleExceptions();

		jclass findClass(const char* path);
	}
}
