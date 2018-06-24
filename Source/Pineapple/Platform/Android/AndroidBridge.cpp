#include <Pineapple/Platform/Android/AndroidBridge.h>

static ANativeActivity* g_androidBridgeNativeActivity = nullptr;

ANativeActivity* pa::AndroidBridge::getNativeActivity()
{
	return g_androidBridgeNativeActivity;
}

void pa::AndroidBridge::setNativeActivity(ANativeActivity* activity)
{
	g_androidBridgeNativeActivity = activity;
}

const char* pa::AndroidBridge::getInternalDataPath()
{
	const char* path = getNativeActivity()->internalDataPath;

	if (!path)
	{
		JNIEnv* jni;
		getNativeActivity()->vm->AttachCurrentThread(&jni, NULL);

		jclass activityClass = jni->GetObjectClass(getNativeActivity()->clazz);
		jmethodID getFilesDir = jni->GetMethodID(activityClass, "getFilesDir", "()Ljava/io/File;");
		jobject fileObject = jni->CallObjectMethod(getNativeActivity()->clazz, getFilesDir);
		jclass fileClass = jni->GetObjectClass(fileObject);
		jmethodID getAbsolutePath = jni->GetMethodID(fileClass, "getAbsolutePath", "()Ljava/lang/String;");
		jobject pathObject = jni->CallObjectMethod(fileObject, getAbsolutePath);
		path = jni->GetStringUTFChars((jstring)pathObject, NULL);

		jni->DeleteLocalRef(pathObject);
		jni->DeleteLocalRef(fileClass);
		jni->DeleteLocalRef(fileObject);
		jni->DeleteLocalRef(activityClass);

		getNativeActivity()->vm->DetachCurrentThread();
	}

	return path;
}