#include <asm/unistd.h>
#include <pthread.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <string>
#include <Pineapple/Engine/Platform/Log.h>
#include <Pineapple/Engine/Util/Macro.h>
#include <Pineapple/Platform/Android/AndroidJNI.h>
#include <Pineapple/Platform/Android/AndroidBridge.h>

namespace pa
{
	namespace AndroidJNI
	{
		static JavaVM* g_jvm = nullptr;

		// Key for per-thread JNIEnv* data.  Non-NULL in threads attached to |g_jvm| by
		// AttachCurrentThreadIfNeeded(), NULL in unattached threads and threads that
		// were attached by the JVM because of a Java->native call.
		static pthread_key_t g_jni_ptr;
		static pthread_once_t g_jni_ptr_once = PTHREAD_ONCE_INIT;

		static JNIEnv* getEnv()
		{
			void* env = nullptr;
			jint status = g_jvm->GetEnv(&env, JNI_VERSION_1_6);
			if (!(((env != nullptr) && (status == JNI_OK)) ||
				  ((env == nullptr) && (status == JNI_EDETACHED))))
			{
				pa::Log::info("Unexpected GetEnv return: {}", status);
			}
			return reinterpret_cast<JNIEnv*>(env);
		}

		static void threadDestructor(void* prev_jni_ptr)
		{
			if (!getEnv())
			{
				return;
			}
			if (getEnv() != prev_jni_ptr)
			{
				pa::Log::info("Detaching from another thread");
			}
			jint status = g_jvm->DetachCurrentThread();
			PA_ASSERTF(status == JNI_OK, "Failed to detach thread: {}", status);
		}

		static void createJNIPtrKey()
		{
			if (pthread_key_create(&g_jni_ptr, &threadDestructor))
			{
				pa::Log::info("pthread_key_create");
			}
		}

		jint initGlobalJniVariables(JavaVM* jvm)
		{
			PA_ASSERTF(!g_jvm, "Error: initGlobalJniVariables() called twice");
			g_jvm = jvm;
			PA_ASSERTF(g_jvm, "Error: jvm is null");
			if (pthread_once(&g_jni_ptr_once, &createJNIPtrKey))
			{
				pa::Log::info("Error: pthread_once");
			}
			JNIEnv* jni = nullptr;
			if (jvm->GetEnv(reinterpret_cast<void**>(&jni), JNI_VERSION_1_6) != JNI_OK)
			{
				return -1;
			}
			return JNI_VERSION_1_6;
		}

		// Return a JNIEnv* usable on this thread.  Attaches to g_jvm if necessary.
		JNIEnv* attachCurrentThreadIfNeeded()
		{
			JNIEnv* jni = getEnv();
			if (jni)
			{
				return jni;
			}
			if (pthread_getspecific(g_jni_ptr))
			{
				pa::Log::info("Error: TLS has a JNIEnv* but not attached");
			}
			JavaVMAttachArgs args;
			args.version = JNI_VERSION_1_6;
			args.name = "Pineapple Thread";
			args.group = nullptr;
			JNIEnv* env = nullptr;

			if (g_jvm->AttachCurrentThread(&env, &args))
			{
				pa::Log::info("Error: Failed to attach thread");
			}
			PA_ASSERTF(env, "AttachCurrentThread handed back NULL!");
			jni = reinterpret_cast<JNIEnv*>(env);
			if (pthread_setspecific(g_jni_ptr, jni))
			{
				pa::Log::info("Error: pthread_setspecific");
			}
			return jni;
		}

		bool handleExceptions()
		{
			auto env = getEnv();
			if (env->ExceptionCheck())
			{
				pa::Log::info("JNI Exception occurred!");
				env->ExceptionDescribe();
				env->ExceptionClear();
				return true;
			}
			else
			{
				return false;
			}
		}

		jclass findClass(const char* path)
		{
			auto env = getEnv();
			env->ExceptionClear();

			auto activity = pa::AndroidBridge::getNativeActivity();

			// Find the class loader object associated with the native activity. We have to use this one to access custom classes.
			jclass activityClass = env->FindClass("android/app/NativeActivity");
			jmethodID getClassLoaderMethod = env->GetMethodID(activityClass, "getClassLoader", "()Ljava/lang/ClassLoader;");
			jobject classLoaderObject = env->CallObjectMethod(activity->clazz, getClassLoaderMethod);
			handleExceptions();

			// Find the load class method
			jclass classLoaderClass = env->FindClass("java/lang/ClassLoader");
			jmethodID loadClassMethod = env->GetMethodID(classLoaderClass, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");
			handleExceptions();

			// Use this class loader object to find any class
			jstring string = env->NewStringUTF(path);
			jclass classObject = static_cast<jclass>(env->CallObjectMethod(classLoaderObject, loadClassMethod, string));
			handleExceptions();
			env->DeleteLocalRef(string);

			return classObject;
		}
	}
}