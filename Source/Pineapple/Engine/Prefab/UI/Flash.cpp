/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Prefab/UI/Flash.h>

pa::Flash::Flash(pa::World& world, int priority)
	: pa::Object(world)
	, m_state(State::Idle)
{
	m_fade = getWorld().create<pa::Fade>(priority);
}

pa::Flash::~Flash()
{
}

void pa::Flash::flash(Time time, float intensity, pa::Colour colour)
{
	m_time = time;
	m_intensity = intensity;
	m_fade->setColour(colour);
	m_fade->fade(0.f, intensity, time / 2);
	m_state = State::FadeIn;
}

void pa::Flash::onDestroy()
{
	m_fade->destroy();
}

void pa::Flash::onStep(Time deltaTime)
{
	switch (m_state)
	{
	case State::Idle: break;
	case State::FadeIn:
		if (!m_fade->isFading())
		{
			// Finished, now fade out at the same rate
			m_fade->fade(m_intensity, 0.f, m_time / 2);
			m_state = State::FadeOut;
		}
		break;
	case State::FadeOut:
		if (!m_fade->isFading())
		{
			// Finished
			destroy();
		}
	}
}
