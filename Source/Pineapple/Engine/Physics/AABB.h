/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Container/Vect2.h>
#include <Pineapple/Engine/Physics/Particle.h>
#include <Pineapple/Engine/Util/Macro.h>

namespace pa
{
	class AABB
	{
	public:
		// Constructor and destructor
		AABB();
		~AABB();

		// Checks if this AABB collides with another AABB during a certain time
		bool collidesWithStatic(const pa::AABB& other) const;
		bool collidesWithStatic(const AABB& other, float& entryTime, Vect2<float>& response) const;
		Vect2<float> resolve(const AABB& other, const float impactTime, const Vect2<float>& response) const;

		// Quickly check if this intersects with another AABB
		bool intersects(const AABB& other) const;

		AABB calculateSweptAABB() const;

		PA_FORMAT_VECTOR_REAL(Position, m_position)
		PA_FORMAT_VECTOR_REAL(Displacement, m_displacement)
		PA_FORMAT_VECTOR_REAL(Size, m_size)
	};
}
