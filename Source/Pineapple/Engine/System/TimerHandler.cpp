/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/System/TimerHandler.h>

pa::TimerHandler::TimerHandler(pa::World& world)
	: m_world(world)
{
	m_callbackIterator =
		m_world.registerPostStepInstancesCallback([this](pa::World&, const pa::Input& input) { this->process(); });
}

pa::TimerHandler::~TimerHandler()
{
	m_world.unregisterPostStepInstancesCallback(m_callbackIterator);
}

void pa::TimerHandler::process()
{
	while (!m_timers.empty() && m_timers.top().alarm <= m_world.getTime())
	{
		auto timer = std::move(m_timers.top());
		m_timers.pop();
		timer.callback();

		if (timer.repeat)
		{
			timer.alarm += timer.duration;
			m_timers.push(timer);
		}
	}
}