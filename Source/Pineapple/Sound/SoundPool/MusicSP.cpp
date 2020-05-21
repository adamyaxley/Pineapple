#include <Pineapple/Sound/SoundPool/MusicSP.h>
#include <Pineapple/Engine/Sound/Sound.h>
#include <Pineapple/Platform/Android/AndroidJNI.h>

pa::MusicSP::MusicSP(const FilePath& path, const pa::BindingMusicSP& binding)
	: pa::Music(path)
	, m_binding(binding)
	, m_soundId(-1)
{}

pa::MusicSP::~MusicSP()
{}

bool pa::MusicSP::onLoad()
{
	auto env = pa::AndroidJNI::attachCurrentThreadIfNeeded();

	jstring string = env->NewStringUTF(getPath().asString().c_str());
	m_soundId = env->CallStaticIntMethod(m_binding.classObject, m_binding.load, string);
	pa::AndroidJNI::handleExceptions();
	env->DeleteLocalRef(string);

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
	auto env = pa::AndroidJNI::attachCurrentThreadIfNeeded();

	env->CallStaticVoidMethod(m_binding.classObject, m_binding.unload, m_soundId);
	pa::AndroidJNI::handleExceptions();
	m_soundId = -1;

	return true;
}

void pa::MusicSP::play()
{
	auto env = pa::AndroidJNI::attachCurrentThreadIfNeeded();

	env->CallStaticVoidMethod(m_binding.classObject, m_binding.play, m_soundId);
	pa::AndroidJNI::handleExceptions();
}

void pa::MusicSP::loop()
{
	auto env = pa::AndroidJNI::attachCurrentThreadIfNeeded();

	env->CallStaticVoidMethod(m_binding.classObject, m_binding.loop, m_soundId);
	pa::AndroidJNI::handleExceptions();
}

void pa::MusicSP::stop()
{
	auto env = pa::AndroidJNI::attachCurrentThreadIfNeeded();

	env->CallStaticVoidMethod(m_binding.classObject, m_binding.stop, m_soundId);
	pa::AndroidJNI::handleExceptions();
}

void pa::MusicSP::pause()
{
	auto env = pa::AndroidJNI::attachCurrentThreadIfNeeded();

	env->CallStaticVoidMethod(m_binding.classObject, m_binding.pause, m_soundId);
	pa::AndroidJNI::handleExceptions();
}

void pa::MusicSP::resume()
{
	auto env = pa::AndroidJNI::attachCurrentThreadIfNeeded();

	env->CallStaticVoidMethod(m_binding.classObject, m_binding.resume, m_soundId);
	pa::AndroidJNI::handleExceptions();
}