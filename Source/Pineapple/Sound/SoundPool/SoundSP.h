#pragma once

#include <Pineapple/Engine/Sound/Sound.h>

namespace pa
{
	class SoundPool : public Sound
	{
	public:
		SoundPool(const FileSystem& fileSystem);
		~SoundPool();

		virtual void update() override {}

	private:
		virtual std::shared_ptr<Effect> createNativeEffect(const FilePath& path) override;
		virtual std::shared_ptr<Music> createNativeMusic(Sound& sound, const FilePath& path) override;
	};
}