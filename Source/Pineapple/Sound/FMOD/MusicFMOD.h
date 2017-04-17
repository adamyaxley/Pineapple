/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <fmod.hpp>

#include <Pineapple/Engine/Sound/Music.h>
#include <Pineapple/Engine/Util/Macro.h>

namespace pa
{
	class MusicFMOD : public Music
	{
	public:
		MusicFMOD(Sound& sound, FMOD::System* system, const char* path);
		~MusicFMOD();

		virtual bool onLoad() override;
		virtual bool onUnload() override;

		virtual void play() override;
		virtual void loop() override;
		virtual void stop() override;
		virtual void pause() override;
		virtual void resume() override;

	private:
		FMOD::System* m_system;

		FMOD::Sound* m_sound;
		FMOD::Channel* m_channel;
	};
}
