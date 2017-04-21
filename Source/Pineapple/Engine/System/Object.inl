/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Util/Macro.h>

PA_FORCE_INLINE pa::Object::Object(pa::World& world)
	: m_world(world)
{
}

PA_FORCE_INLINE void pa::Object::step(Time deltaTime)
{
	onStep(deltaTime);
}

PA_FORCE_INLINE void pa::Object::destroy()
{
	if (!isDead())
	{
		// Call the user defined destroy event
		onDestroy();

		// Set dead to true
		m_flags.set(Flags::IsDead);
	}
}

PA_FORCE_INLINE void pa::Object::kill()
{
	// Set dead to true
	m_flags.set(Flags::IsDead);
}

PA_FORCE_INLINE pa::World& pa::Object::getWorld()
{
	return m_world;
}

PA_FORCE_INLINE bool pa::Object::isDead()
{
	return m_flags.getBool(Flags::IsDead);
}
