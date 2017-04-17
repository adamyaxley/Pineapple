/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/System/Timer.h>
#include <Pineapple/Engine/System/World.h>
#include <queue>

namespace pa
{
	class TimerHandler
	{
	public:
		// Constructor and destructor
		TimerHandler(World& world);
		~TimerHandler();

		template <typename T>
		void startTimer(Time time, T&& callback, bool repeat = false);

	private:
		void process();

		World& m_world;
		World::CallbackIterator m_callbackIterator;
		std::priority_queue<Timer, std::vector<Timer>, std::greater<Timer>> m_timers;
	};
}

#include <Pineapple/Engine/System/TimerHandler.inl>