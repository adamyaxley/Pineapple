#include <Pineapple/Platform/Android/AndroidUtil.h>
#include <Pineapple/Platform/Android/AndroidBridge.h>
#include <Pineapple/Platform/Android/ScopedEnvJNI.h>
#include <Pineapple/Engine/Util/Macro.h>

pa::AndroidUtil::AndroidUtil()
{
	ScopedEnvJNI env;

	m_class = env.findClass("com.pineapple.util.paUtil");
	PA_ASSERTF(m_class != NULL, "Could not find required paUtil class");

	m_setContextMethod = env.get()->GetStaticMethodID(m_class, "setContext", "(Landroid/content/Context;)V");
	PA_ASSERTF(m_setContextMethod != NULL, "Could not find required paUtil.setContext method");

	m_openUrlMethod = env.get()->GetStaticMethodID(m_class, "openUrl", "(Ljava/lang/String;)V");
	PA_ASSERTF(m_openUrlMethod != NULL, "Could not find required paUtil.openUrl method");

	env.get()->CallStaticVoidMethod(m_class, m_setContextMethod, AndroidBridge::getNativeActivity()->clazz);
	env.handleExceptions();
}

pa::AndroidUtil::~AndroidUtil()
{}

void pa::AndroidUtil::openUrl(const char* url) const
{
	/*I/ActivityManager(  714): START u0 {act=android.intent.action.VIEW dat=https://www.facebook.com/Official100Ballz cmp=com.android.browser/.BrowserActivity} from
	pid 26154*/

	pa::ScopedEnvJNI env;

	jstring string = env.get()->NewStringUTF(url);
	env.get()->CallStaticVoidMethod(m_class, m_openUrlMethod, string);
	env.handleExceptions();
	env.get()->DeleteLocalRef(string);
}