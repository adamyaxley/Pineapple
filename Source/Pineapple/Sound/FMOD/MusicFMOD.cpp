/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Platform/File.h>
#include <Pineapple/Sound/FMOD/MusicFMOD.h>
#include <Pineapple/Sound/FMOD/UtilFMOD.h>

pa::MusicFMOD::MusicFMOD(pa::Sound& sound, FMOD::System* system, const char* path)
	: pa::Music(sound, path)
	, m_system(system)
	, m_sound(nullptr)
	, m_channel(nullptr)
{
}

pa::MusicFMOD::~MusicFMOD()
{
}

bool pa::MusicFMOD::onLoad()
{
	FMOD_RESULT result =
		m_system->createStream((pa::File::getAssetsPath() + getPath()).c_str(), FMOD_DEFAULT, nullptr, &m_sound);
	return pa::UtilFMOD::checkResult(result);
}

bool pa::MusicFMOD::onUnload()
{
	FMOD_RESULT result = m_sound->release();
	m_sound = nullptr;
	m_channel = nullptr;
	return pa::UtilFMOD::checkResult(result);
}

void pa::MusicFMOD::play()
{
	PA_ASSERTF(isLoaded(), "Sound is not loaded");
	m_sound->setMode(FMOD_LOOP_OFF);
	FMOD_RESULT result = m_system->playSound(m_sound, 0, false, &m_channel);
	pa::UtilFMOD::checkResult(result);
}

void pa::MusicFMOD::loop()
{
	PA_ASSERTF(isLoaded(), "Sound is not loaded");
	m_sound->setMode(FMOD_LOOP_NORMAL);
	FMOD_RESULT result = m_system->playSound(m_sound, 0, false, &m_channel);
	pa::UtilFMOD::checkResult(result);
}

void pa::MusicFMOD::stop()
{
	PA_ASSERTF(isLoaded(), "Sound is not loaded");
	bool isPlaying = false;
	FMOD_RESULT result = m_channel->isPlaying(&isPlaying);
	pa::UtilFMOD::checkResult(result);

	if (isPlaying)
	{
		m_channel->stop();
	}
}

void pa::MusicFMOD::pause()
{
	PA_ASSERTF(isLoaded(), "Sound is not loaded");
	bool isPlaying = false;
	FMOD_RESULT result = m_channel->isPlaying(&isPlaying);
	pa::UtilFMOD::checkResult(result);

	if (isPlaying)
	{
		m_channel->setPaused(true);
	}
}

void pa::MusicFMOD::resume()
{
	PA_ASSERTF(isLoaded(), "Sound is not loaded");
	bool isPlaying = false;
	FMOD_RESULT result = m_channel->isPlaying(&isPlaying);
	pa::UtilFMOD::checkResult(result);

	if (isPlaying)
	{
		m_channel->setPaused(false);
	}
}
