/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Graphics/Graphics.h>
#include <Pineapple/Engine/Prefab/Asset/Asset.h>
#include <Pineapple/Engine/Prefab/UI/Fade.h>

pa::Fade::Fade(pa::World& world, int priority)
	: pa::Object(world)
	, m_background(nullptr)
	, m_delta(0)
	, m_target(0)
{
	m_background = getWorld().create<pa::Background>(priority);
	m_background->setColour(pa::ColourSet::Black);
}

pa::Fade::~Fade()
{
}

void pa::Fade::onDestroy()
{
	m_background->destroy();
}

void pa::Fade::fade(float from, float to, Time time)
{
	m_background->getColour().A = from;
	m_target = to;
	m_delta = (from < to ? 1.f : -1.f) / time.count();
}

bool pa::Fade::isFading() const
{
	return (m_delta != 0.f);
}

void pa::Fade::onStep(Time deltaTime)
{
	if (isFading())
	{
		float& alpha = m_background->getColour().A;

		alpha += m_delta * deltaTime.count();

		if (m_delta < 0)
		{
			if (alpha < m_target)
			{
				alpha = m_target;
				m_delta = 0.f;
			}
		}
		else
		{
			if (alpha > m_target)
			{
				alpha = m_target;
				m_delta = 0.f;
			}
		}
	}
}

void pa::Fade::setColour(const pa::Colour& colour)
{
	m_background->setColour(colour);
}

pa::Colour& pa::Fade::getColour()
{
	return m_background->getColour();
}