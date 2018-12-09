#include <Pineapple/Platform/Android/ScopedEnvJNI.h>
#include <Pineapple/Engine/Util/Macro.h>

pa::ScopedEnvJNI::ScopedEnvJNI()
	: m_activity(pa::AndroidBridge::getNativeActivity())
	, m_env(NULL)
	, m_detach(false)
{
	int getEnvStatus = m_activity->vm->GetEnv((void**)&m_env, JNI_VERSION_1_6);

	switch (getEnvStatus)
	{
	case JNI_EDETACHED:
	{
		//pa::Log::info("ScopedJNI: thread not attached");

		if (m_activity->vm->AttachCurrentThread(&m_env, NULL) != 0)
		{
			pa::Log::info("ScopedJNI: Failed to attach thread");
		}
		else
		{
			m_detach = true;
			//pa::Log::info("ScopedJNI: Successfully attached thread");
		}
		break;
	}
	case JNI_EVERSION:
	{
		pa::Log::info("ScopedJNI: jni version JNI_VERSION_1_6 not supported");
		break;
	}
	case JNI_OK:
	{
		//pa::Log::info("ScopedJNI: thread is already attached");
		break;
	}
	default:
	{
		pa::Log::info("ScopedJNI: unknown error: %d", getEnvStatus);
	}
	}


	PA_ASSERTF(m_env != NULL, "JNIEnv is null")
}

pa::ScopedEnvJNI::~ScopedEnvJNI()
{
	if (m_detach /* && ATTACHED */)
	{
		m_activity->vm->DetachCurrentThread();
	}
}

jclass pa::ScopedEnvJNI::findClass(const char* path)
{
	get()->ExceptionClear();

	// Find the class loader object associated with the native activity. We have to use this one to access custom classes.
	jclass activityClass = get()->FindClass("android/app/NativeActivity");
	jmethodID getClassLoaderMethod = get()->GetMethodID(activityClass, "getClassLoader", "()Ljava/lang/ClassLoader;");
	jobject classLoaderObject = get()->CallObjectMethod(m_activity->clazz, getClassLoaderMethod);
	handleExceptions();

	// Find the load class method
	jclass classLoaderClass = get()->FindClass("java/lang/ClassLoader");
	jmethodID loadClassMethod = get()->GetMethodID(classLoaderClass, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");
	handleExceptions();

	// Use this class loader object to find any class
	jstring string = get()->NewStringUTF(path);
	jclass classObject = static_cast<jclass>(get()->CallObjectMethod(classLoaderObject, loadClassMethod, string));
	handleExceptions();
	get()->DeleteLocalRef(string);

	return classObject;
}

bool pa::ScopedEnvJNI::handleExceptions()
{
	if (get()->ExceptionCheck())
	{
		pa::Log::info("ScopedJNI: Exception occurred!");
		get()->ExceptionDescribe();
		get()->ExceptionClear();
		return true;
	}
	else
	{
		return false;
	}
}

/*long paScopedEnvJNI::getObjectSize(jobject object)
{
// Find java instrumentation class NOT AVAILABLE ON ANDROID
jclass instrumentationClass = findClass("java.lang.instrument.Instrumentation");
PA_PRINT_META();
// Create an instance
jmethodID constructor = get()->GetMethodID(instrumentationClass, "<init>", "()V");
jobject instrumentationObject = get()->NewObject(instrumentationClass, constructor);
PA_PRINT_META();
// Call the getObjectSize method
jmethodID getObjectSizeMethod = get()->GetMethodID(instrumentationClass, "getObjectSize", "(Ljava/lang/Object;)J"); // long getObjectSize(Object)
long size = get()->CallLongMethod(instrumentationObject, getObjectSizeMethod, object);

return size;
}*/
