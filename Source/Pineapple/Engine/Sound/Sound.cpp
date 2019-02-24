/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Sound/Effect.h>
#include <Pineapple/Engine/Sound/Music.h>
#include <Pineapple/Engine/Sound/Sound.h>

pa::Sound::Sound(const FileSystem& fileSystem)
	: m_fileSystem(fileSystem)
{
}

pa::Sound::~Sound()
{
}

pa::ResourceManager& pa::Sound::getResourceManager()
{
	return m_resourceManager;
}

std::shared_ptr<pa::Effect> pa::Sound::createEffect(const char* path, pa::FileStorage storage)
{
	auto effect = createNativeEffect(pa::FilePath(m_fileSystem, storage, path));
	m_resourceManager.add(effect);
	return effect;
}

std::shared_ptr<pa::Music> pa::Sound::createMusic(const char* path, pa::FileStorage storage)
{
	auto music = createNativeMusic(pa::FilePath(m_fileSystem, storage, path));
	m_resourceManager.add(music);
	m_musicList.push_back(music);
	return music;
}

void pa::Sound::pauseMusic()
{
	for (auto music : m_musicList)
	{
		if (music->isLoaded())
		{
			music->pause();
		}
	}
}

void pa::Sound::resumeMusic()
{
	for (auto music : m_musicList)
	{
		if (music->isLoaded())
		{
			music->resume();
		}
	}
}

void pa::Sound::setMusicEnabled(bool enabled)
{
	m_musicEnabled = enabled;

	if (m_musicEnabled)
	{
		resumeMusic();
	}
	else
	{
		pauseMusic();
	}
}

void pa::Sound::setEffectEnabled(bool enabled)
{
	m_effectEnabled = enabled;
}

bool pa::Sound::getMusicEnabled()
{
	return m_musicEnabled;
}

bool pa::Sound::getEffectEnabled()
{
	return m_effectEnabled;
}
