#include <Pineapple/Sound/SoundPool/EffectSP.h>
#include <Pineapple/Engine/Sound/Sound.h>
#include <Pineapple/Platform/Android/ScopedEnvJNI.h>
#include <Pineapple/Engine/Platform/Log.h>
#include <Pineapple/Engine/Util/Macro.h>

pa::EffectSP::EffectSP(const FilePath& path, const pa::BindingEffectSP& binding)
	: pa::Effect(path)
	, m_binding(binding)
	, m_soundId(-1)
{}

pa::EffectSP::~EffectSP()
{}

bool pa::EffectSP::onLoad()
{
	pa::ScopedEnvJNI env;

	jstring string = env.get()->NewStringUTF(getPath().asString().c_str());
	m_soundId = env.get()->CallStaticIntMethod(m_binding.classObject, m_binding.load, string);
	env.handleExceptions();
	env.get()->DeleteLocalRef(string);

	if (m_soundId <= 0)
	{
		pa::Log::info("Failed to load sound: {} {}", m_soundId, getPath().asString());
		return false;
	}
	else
	{
		pa::Log::info("Successfully loaded sound: {}", getPath().asString());
	}

	return true;
}

bool pa::EffectSP::onUnload()
{
	pa::ScopedEnvJNI env;

	env.get()->CallStaticVoidMethod(m_binding.classObject, m_binding.unload);
	env.handleExceptions();
	m_soundId = -1;

	return true;
}

void pa::EffectSP::play()
{
	PA_ASSERTF(isLoaded(), "Sound is not loaded");
	pa::Log::info("paEffectSP::play()");
	pa::ScopedEnvJNI env;

	// Unused return pa::rameter stream
	env.get()->CallStaticIntMethod(m_binding.classObject, m_binding.play, m_soundId);
	env.handleExceptions();
}

void pa::EffectSP::loop()
{
	// Not implemented
}
