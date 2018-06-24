#pragma once

#include <android/native_activity.h>
#include <jni.h>

namespace pa
{
	class AndroidUtil
	{
	public:

		AndroidUtil();
		~AndroidUtil();

		void openUrl(const char* url) const;

	private:

		jclass m_class;

		jmethodID m_setContextMethod;
		jmethodID m_openUrlMethod;
	};
}
