/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/System/Object.h>
#include <Pineapple/Engine/System/World.h>
#include <Pineapple/Engine/Util/Macro.h>

pa::Object::Object(pa::World& world)
	: m_world(world)
{
	// Instances that are created while the world is stepping aren't stepped
	// until the next tick. To implement this behaviour, store a single bit
	// indicating whether the next tick that it will step on is odd or even.
	// This allows the instance to skip a single step if necessary.
	if (world.isStepping() != (world.getTicks() % 2 == 0))
	{
		m_flags.set(Flags::StepsOnEvenTick);
	}
}

void pa::Object::step(Time deltaTime)
{
	if ((m_world.getTicks() % 2 == 1) != m_flags.getBool(Flags::StepsOnEvenTick))
	{
		onStep(deltaTime);
		m_flags.toggle(Flags::StepsOnEvenTick);
	}
}

void pa::Object::destroy()
{
	if (!isDead())
	{
		// Call the user defined destroy event
		onDestroy();

		// Set dead to true
		m_flags.set(Flags::IsDead);
	}
}

void pa::Object::kill()
{
	// Set dead to true
	m_flags.set(Flags::IsDead);
}

pa::World& pa::Object::getWorld()
{
	return m_world;
}

bool pa::Object::isDead()
{
	return m_flags.getBool(Flags::IsDead);
}
