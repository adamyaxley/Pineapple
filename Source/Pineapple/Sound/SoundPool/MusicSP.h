#pragma once

#include <Pineapple/Engine/Sound/Music.h>
#include <Pineapple/Sound/SoundPool/BindingMusicSP.h>
#include <Pineapple/Engine/Util/Macro.h>

namespace pa
{
	class MusicSP : public Music
	{
	public:

		MusicSP(const FilePath& path, const BindingMusicSP& binding);
		~MusicSP();

		virtual bool onLoad() override;
		virtual bool onUnload() override;

		virtual void play() override;
		virtual void loop() override;
		virtual void stop() override;
		virtual void pause() override;
		virtual void resume() override;

	private:

		const BindingMusicSP& m_binding;

		int m_soundId;
	};
}
