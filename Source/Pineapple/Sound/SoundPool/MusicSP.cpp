#include <Pineapple/Sound/SoundPool/MusicSP.h>
#include <Pineapple/Engine/Sound/Sound.h>
#include <Pineapple/Platform/Android/ScopedEnvJNI.h>

pa::MusicSP::MusicSP(Sound& sound, const FilePath& path, const pa::BindingMusicSP& binding)
	: pa::Music(sound, path)
	, m_binding(binding)
	, m_soundId(-1)
{}

pa::MusicSP::~MusicSP()
{}

bool pa::MusicSP::onLoad()
{
	pa::ScopedEnvJNI env;

	jstring string = env.get()->NewStringUTF(getPath().asString().c_str());
	m_soundId = env.get()->CallStaticIntMethod(m_binding.classObject, m_binding.load, string);
	env.handleExceptions();
	env.get()->DeleteLocalRef(string);

	if (m_soundId <= 0)
	{
		pa::Log::info("Failed to load music: {} {}", m_soundId, getPath().asString());
		return false;
	}
	else
	{
		pa::Log::info("Successfully loaded music: {}", getPath().asString());
	}

	return true;
}

bool pa::MusicSP::onUnload()
{
	pa::ScopedEnvJNI env;

	env.get()->CallStaticVoidMethod(m_binding.classObject, m_binding.unload, m_soundId);
	env.handleExceptions();
	m_soundId = -1;

	return true;
}

void pa::MusicSP::play()
{
	pa::ScopedEnvJNI env;

	env.get()->CallStaticVoidMethod(m_binding.classObject, m_binding.play, m_soundId);
	env.handleExceptions();
}

void pa::MusicSP::loop()
{
	pa::ScopedEnvJNI env;

	env.get()->CallStaticVoidMethod(m_binding.classObject, m_binding.loop, m_soundId);
	env.handleExceptions();
}

void pa::MusicSP::stop()
{
	pa::ScopedEnvJNI env;

	env.get()->CallStaticVoidMethod(m_binding.classObject, m_binding.stop, m_soundId);
	env.handleExceptions();
}

void pa::MusicSP::pause()
{
	pa::ScopedEnvJNI env;

	env.get()->CallStaticVoidMethod(m_binding.classObject, m_binding.pause, m_soundId);
	env.handleExceptions();
}

void pa::MusicSP::resume()
{
	pa::ScopedEnvJNI env;

	env.get()->CallStaticVoidMethod(m_binding.classObject, m_binding.resume, m_soundId);
	env.handleExceptions();
}