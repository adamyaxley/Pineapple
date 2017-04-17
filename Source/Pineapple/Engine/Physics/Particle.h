/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Container/Vect2.h>
#include <Pineapple/Engine/System/Time.h>
#include <Pineapple/Engine/Util/Format.h>

namespace pa
{
	class Particle
	{
	public:
		void stepMotion(Time deltaTime);

		Vect2<float> calculatePosition(float time) const;
#if 0
		float calculateXSpeedAtX(float x) const;

		float calculateXPosition(float time) const;

		bool calculateFirstTimeForXDisplacement(float displacement, float& time) const;

		bool calculateLastTimeForXDisplacement(float displacement, float& time) const;

		int calculateTimeForXDisplacement(float displacement, float& time1, float& time2) const;

		bool calculateFirstTimeForYDisplacement(float displacement, float& time) const;

		bool calculateLastTimeForYDisplacement(float displacement, float& time) const;

		int calculateTimeForYDisplacement(float displacement, float& time1, float& time2) const;

		// Calculates the first time that the displacement is reached
		bool calculateFirstTimeForDisplacement(float displacement, float velocity, float acceleration,
											   float& time) const;

		// Calculates the last time that the displacement is reached
		bool calculateLastTimeForDisplacement(float displacement, float velocity, float acceleration,
											  float& time) const;

		// Calculates the times that the displacement is met
		int calculateTimeForDisplacement(float displacement, float velocity, float acceleration, float& time1,
										 float& time2) const;

		float getDirection();
#endif
		PA_FORMAT_VECTOR_REAL(Position, m_position)
		PA_FORMAT_VECTOR_REAL(Velocity, m_velocity)
		PA_FORMAT_VECTOR_REAL(Acceleration, m_acceleration)

	private:
		// Vect2<float> m_position, m_velocity, m_acceleration;
	};
}
