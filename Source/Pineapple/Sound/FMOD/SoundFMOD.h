/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Sound/Sound.h>
#include <Pineapple/Engine/Util/Macro.h>

namespace pa
{
	class SoundFMOD : public Sound
	{
	public:
		SoundFMOD(const FileSystem& fileSystem);
		~SoundFMOD();

		virtual void update() override;

	private:
		virtual std::shared_ptr<Effect> createNativeEffect(const FilePath& path) override;
		virtual std::shared_ptr<Music> createNativeMusic(Sound& sound, const FilePath& path) override;

		FMOD::System* m_system;
	};
}
