#include <Pineapple/Platform/Android/AndroidUtil.h>
#include <Pineapple/Platform/Android/AndroidBridge.h>
#include <Pineapple/Platform/Android/AndroidJNI.h>
#include <Pineapple/Engine/Util/Macro.h>

pa::AndroidUtil::AndroidUtil()
{
	auto env = pa::AndroidJNI::attachCurrentThreadIfNeeded();

	m_class = pa::AndroidJNI::findClass("com.pineapple.util.paUtil");
	PA_ASSERTF(m_class != NULL, "Could not find required paUtil class");

	m_setContextMethod = env->GetStaticMethodID(m_class, "setContext", "(Landroid/content/Context;)V");
	PA_ASSERTF(m_setContextMethod != NULL, "Could not find required paUtil.setContext method");

	m_openUrlMethod = env->GetStaticMethodID(m_class, "openUrl", "(Ljava/lang/String;)V");
	PA_ASSERTF(m_openUrlMethod != NULL, "Could not find required paUtil.openUrl method");

	env->CallStaticVoidMethod(m_class, m_setContextMethod, AndroidBridge::getNativeActivity()->clazz);
	pa::AndroidJNI::handleExceptions();
}

pa::AndroidUtil::~AndroidUtil()
{}

void pa::AndroidUtil::openUrl(const char* url) const
{
	/*I/ActivityManager(  714): START u0 {act=android.intent.action.VIEW dat=https://www.facebook.com/Official100Ballz cmp=com.android.browser/.BrowserActivity} from
	pid 26154*/

	auto env = pa::AndroidJNI::attachCurrentThreadIfNeeded();

	jstring string = env->NewStringUTF(url);
	env->CallStaticVoidMethod(m_class, m_openUrlMethod, string);
	pa::AndroidJNI::handleExceptions();
	env->DeleteLocalRef(string);
}