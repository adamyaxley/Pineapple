/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/System/World.h>

namespace pa
{
	class InputHandler
	{
	public:
		// Constructor and destructor
		InputHandler(World& world);
		~InputHandler();

		// User definable events
		virtual void onKeyPress(Key)
		{
		}
		virtual void onKeyRelease(Key)
		{
		}
		virtual void onKeyDown(Key)
		{
		}
		virtual void onCharInput(std::string input)
		{
		}
		virtual void onQuit()
		{
			m_world.end();
		}

	private:
		void process(const Input& input);

		World& m_world;
		World::CallbackIterator m_callbackIterator;
	};
}
