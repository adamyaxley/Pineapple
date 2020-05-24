/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Sound/FMOD/EffectFMOD.h>
#include <Pineapple/Sound/FMOD/MusicFMOD.h>
#include <Pineapple/Sound/FMOD/SoundFMOD.h>
#include <Pineapple/Sound/FMOD/UtilFMOD.h>
#include <fmod.hpp>
#include <fmod_errors.h>

std::unique_ptr<pa::Sound> pa::MakeInternal::sound(const pa::FileSystem& fileSystem)
{
	return std::make_unique<pa::SoundFMOD>(fileSystem);
}

pa::SoundFMOD::SoundFMOD(const FileSystem& fileSystem)
	: pa::Sound(fileSystem)
{
	FMOD_RESULT result = FMOD::System_Create(&m_system);
	pa::UtilFMOD::checkResult(result);

	unsigned int version;

	result = m_system->getVersion(&version);
	pa::UtilFMOD::checkResult(result);

	if (version < FMOD_VERSION)
	{
		pa::Log::info("Error!  You are using an old version of FMOD {}.  This program requires {}\n", version,
					  FMOD_VERSION);
		throw std::exception();
	}

	result = m_system->init(32, FMOD_INIT_NORMAL, 0);
	pa::UtilFMOD::checkResult(result);
}

pa::SoundFMOD::~SoundFMOD()
{
	getResourceManager().unloadAll();
	FMOD_RESULT result = m_system->close();
	pa::UtilFMOD::checkResult(result);
	result = m_system->release();
	pa::UtilFMOD::checkResult(result);
}

void pa::SoundFMOD::update()
{
	m_system->update();
}

void pa::SoundFMOD::resume()
{
	m_system->mixerResume();
}

void pa::SoundFMOD::suspend()
{
	m_system->mixerSuspend();
}

std::shared_ptr<pa::Effect> pa::SoundFMOD::createNativeEffect(const pa::FilePath& path)
{
	return std::make_shared<pa::EffectFMOD>(m_system, path);
}

std::shared_ptr<pa::Music> pa::SoundFMOD::createNativeMusic(const pa::FilePath& path)
{
	return std::make_shared<pa::MusicFMOD>(m_system, path);
}