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
}

void pa::Object::step(Time deltaTime)
{
	onStep(deltaTime);
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
