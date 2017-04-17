/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Platform/File.h>
#include <Pineapple/Sound/FMOD/EffectFMOD.h>
#include <Pineapple/Sound/FMOD/UtilFMOD.h>

pa::EffectFMOD::EffectFMOD(FMOD::System* system, const char* path)
	: pa::Effect(path)
	, m_system(system)
	, m_sound(nullptr)
	, m_channel(nullptr)
{
}

pa::EffectFMOD::~EffectFMOD()
{
}

bool pa::EffectFMOD::onLoad()
{
	FMOD_RESULT result =
		m_system->createSound((pa::File::getAssetsPath() + getPath()).c_str(), FMOD_DEFAULT, nullptr, &m_sound);
	return pa::UtilFMOD::checkResult(result);
}

bool pa::EffectFMOD::onUnload()
{
	FMOD_RESULT result = m_sound->release();
	return pa::UtilFMOD::checkResult(result);
}

void pa::EffectFMOD::play()
{
	PA_ASSERTF(isLoaded(), "Sound is not loaded");
	m_sound->setMode(FMOD_LOOP_OFF);
	FMOD_RESULT result = m_system->playSound(m_sound, 0, false, &m_channel);
	pa::UtilFMOD::checkResult(result);
}

void pa::EffectFMOD::loop()
{
	PA_ASSERTF(isLoaded(), "Sound is not loaded");
	m_sound->setMode(FMOD_LOOP_NORMAL);
	FMOD_RESULT result = m_system->playSound(m_sound, 0, false, &m_channel);
	pa::UtilFMOD::checkResult(result);
}
