/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Platform/Resource.h>

namespace pa
{
	class Effect : public Resource
	{
	public:
		Effect(const char* path);

		virtual void play() = 0;
		virtual void loop() = 0;
		// virtual void update() =0;
		/*virtual void stop();

		virtual void setVolume(float volume);*/
	};
}
