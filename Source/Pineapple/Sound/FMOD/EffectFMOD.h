/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <fmod.hpp>

#include <Pineapple/Engine/Sound/Effect.h>
#include <Pineapple/Engine/Util/Macro.h>

namespace pa
{
	class EffectFMOD : public Effect
	{
	public:
		EffectFMOD(FMOD::System* system, const char* path);
		~EffectFMOD();

		virtual bool onLoad() override;
		virtual bool onUnload() override;

		virtual void play() override;
		virtual void loop() override;

	private:
		FMOD::System* m_system;

		FMOD::Sound* m_sound;
		FMOD::Channel* m_channel;
	};
}
