#pragma once
#include <jni.h>

namespace pa
{
	struct BindingMusicSP
	{
		jclass classObject;

		jmethodID startup;
		jmethodID shutdown;
		jmethodID load;
		jmethodID unload;
		jmethodID play;
		jmethodID loop;
		jmethodID stop;
		jmethodID pause;
		jmethodID resume;
	};
}
