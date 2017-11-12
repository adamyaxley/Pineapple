/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Platform/ResourceManager.h>

#include <list>
#include <memory>

namespace pa
{
	class Sound;

	namespace MakeInternal
	{
		std::unique_ptr<Sound> sound(const FileSystem& fileSystem);
	}

	class Effect;
	class Music;

	class Sound
	{
	public:
		using Handle = std::list<Music*>::const_iterator;

		Sound(const FileSystem& fileSystem);
		virtual ~Sound();

		void pauseMusic();
		void resumeMusic();

		void setMusicEnabled(bool enabled);
		void setEffectEnabled(bool enabled);

		bool getMusicEnabled();
		bool getEffectEnabled();

		ResourceManager& getResourceManager();

		std::shared_ptr<Effect> createEffect(const char* path, FileStorage storage = FileStorage::UserAsset);
		std::shared_ptr<Music> createMusic(const char* path, FileStorage storage = FileStorage::UserAsset);

		Handle registerMusic(Music* music);
		void unregisterMusic(Handle handle);

		virtual void update()
		{
		}

	private:
		virtual std::shared_ptr<Effect> createNativeEffect(const FilePath& path) = 0;
		virtual std::shared_ptr<Music> createNativeMusic(Sound& sound, const FilePath& path) = 0;

		ResourceManager m_resourceManager;

		bool m_musicEnabled = true;
		bool m_effectEnabled = true;

		std::list<Music*> m_musicList;

		const FileSystem& m_fileSystem;
	};
}
