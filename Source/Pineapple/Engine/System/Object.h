/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Container/Bitfield.h>
#include <Pineapple/Engine/System/Time.h>
#include <Pineapple/Engine/System/World.h>

namespace pa
{
	class Object
	{
		// Non-copyable and non-assignable
		Object(const Object&) = delete;
		Object& operator=(const Object&) = delete;

	protected:
		PA_FORCE_INLINE Object(World& world);

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
		PA_FORCE_INLINE void step(Time deltaTime);

		// Destroys the instance
		PA_FORCE_INLINE void destroy();

		// Destroys the instance without calling onDestroy
		PA_FORCE_INLINE void kill();

		// Is this instance dead?
		PA_FORCE_INLINE bool isDead();

		// Retrieve the world that the instance is in
		PA_FORCE_INLINE World& getWorld();

	private:
		// A pointer to the world
		World& m_world;

		enum class Flags
		{
			IsDead,
			is_enum_bitfield
		};

		// Object flags
		Bitfield<Flags> m_flags;
	};
}

#include <Pineapple/Engine/System/Object.inl>
