#pragma once
#include <jni.h>

namespace pa
{
	struct BindingEffectSP
	{
		jclass classObject;

		jmethodID startup;
		jmethodID shutdown;
		jmethodID load;
		jmethodID unload;
		jmethodID play;
	};
}
