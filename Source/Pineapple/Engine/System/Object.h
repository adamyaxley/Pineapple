/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Container/Bitfield.h>
#include <Pineapple/Engine/System/Time.h>

namespace pa
{
	class World;

	class Object
	{
		// Non-copyable and non-assignable
		Object(const Object&) = delete;
		Object& operator=(const Object&) = delete;

	protected:
		Object(World& world);

	public:
		virtual ~Object()
		{
		}

		// User defined functions
		virtual void onCreate()
		{
		}
		virtual void onDestroy()
		{
		}
		virtual void onStep(Time deltaTime)
		{
		}

		// Steps the instance
		void step(Time deltaTime);

		// Destroys the instance
		void destroy();

		// Destroys the instance without calling onDestroy
		void kill();

		// Is this instance dead?
		bool isDead();

		// Retrieve the world that the instance is in
		World& getWorld();

	private:
		// A pointer to the world
		World& m_world;

		enum class Flags
		{
			IsDead,
			StepsOnEvenTick,
			_PineappleBitfieldEndMarker
		};

		// Object flags
		Bitfield<Flags> m_flags;
	};
}
