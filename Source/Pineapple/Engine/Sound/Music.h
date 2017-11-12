/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Platform/Resource.h>
#include <Pineapple/Engine/Sound/Sound.h>

namespace pa
{
	class Music : public Resource
	{
	public:
		Music(Sound& sound, const FilePath& path);
		~Music();

		virtual void play() = 0;
		virtual void loop() = 0;
		virtual void stop() = 0;
		virtual void pause() = 0;
		virtual void resume() = 0;

	private:
		Sound& m_sound;
		Sound::Handle m_handle;
	};
}
