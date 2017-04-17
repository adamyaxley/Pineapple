/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Physics/Particle.h>
#include <Pineapple/Engine/System/Time.h>
#include <Pineapple/Engine/Util/Macro.h>
#include <math.h>

void pa::Particle::stepMotion(Time deltaTime)
{
	// Equations of motion
	pa::Vect2<float> initialVelocity = m_velocity;
	m_velocity += m_acceleration * deltaTime.count();
	m_position += (initialVelocity + m_velocity) * (deltaTime.count() * 0.5f);
}

#if 0
pa::Vect2<float> pa::Particle::calculatePosition(float time) const
{
	// s = ut + .5 * at^2
	return (m_position + m_velocity * time + m_acceleration * time * time * 0.5f);
}

float pa::Particle::getDirection()
{
	return (float)atan2(m_velocity.y, m_velocity.x);
}

float pa::Particle::calculateXSpeedAtX(float x) const
{
	// v^2 = u^2 + 2as
	return sqrt(getVelocityConst().x * getVelocityConst().x +
				2 * getAccelerationConst().x * (x - getPositionConst().x));
}

float pa::Particle::calculateXPosition(float time) const
{
	// s = ut + .5 * at^2
	return (m_position.x + m_velocity.x * time + m_acceleration.x * time * time * 0.5f);
}

bool pa::Particle::calculateFirstTimeForXDisplacement(float displacement, float& time) const
{
	return calculateFirstTimeForDisplacement(displacement, m_velocity.x, m_acceleration.x, time);
}

bool pa::Particle::calculateLastTimeForXDisplacement(float displacement, float& time) const
{
	return calculateLastTimeForDisplacement(displacement, m_velocity.x, m_acceleration.x, time);
}

int pa::Particle::calculateTimeForXDisplacement(float displacement, float& time1, float& time2) const
{
	return calculateTimeForDisplacement(displacement, m_velocity.x, m_acceleration.x, time1, time2);
}

bool pa::Particle::calculateFirstTimeForYDisplacement(float displacement, float& time) const
{
	return calculateFirstTimeForDisplacement(displacement, m_velocity.y, m_acceleration.y, time);
}

bool pa::Particle::calculateLastTimeForYDisplacement(float displacement, float& time) const
{
	return calculateLastTimeForDisplacement(displacement, m_velocity.y, m_acceleration.y, time);
}

int pa::Particle::calculateTimeForYDisplacement(float displacement, float& time1, float& time2) const
{
	return calculateTimeForDisplacement(displacement, m_velocity.y, m_acceleration.y, time1, time2);
}

bool pa::Particle::calculateFirstTimeForDisplacement(float displacement, float velocity, float acceleration,
													 float& time) const
{
	float time1, time2;
	int solutions = calculateTimeForDisplacement(displacement, velocity, acceleration, time1, time2);

	switch (solutions)
	{
	case 0: return false; break;
	case 1:
		time = time1;
		return true;
		break;
	case 2:
		if (time1 >= 0 && time2 >= 0)
		{
			time = PA_MIN(time1, time2);
		}
		else
		{
			time = PA_MAX(time1, time2);
		}
		return true;
		break;
	default: PA_ASSERTF(false, "Incorrect number of solutions: {}", solutions); return false;
	}
}

bool pa::Particle::calculateLastTimeForDisplacement(float displacement, float velocity, float acceleration,
													float& time) const
{
	float time1, time2;
	int solutions = calculateTimeForDisplacement(displacement, velocity, acceleration, time1, time2);

	switch (solutions)
	{
	case 0: return false; break;
	case 1:
		time = time1;
		return true;
		break;
	case 2:
		time = PA_MAX(time1, time2);
		return true;
		break;
	default: PA_ASSERTF(false, "Incorrect number of solutions: {}", solutions); return false;
	}
}

int pa::Particle::calculateTimeForDisplacement(float displacement, float velocity, float acceleration, float& time1,
											   float& time2) const
{
	if (acceleration == 0.f)
	{
		time1 = displacement / velocity;
		return 1;
	}
	else
	{
		// Solving t = -(u +/- sqrt(u^2 + 2as)) / a
		float discriminant = velocity * velocity + 2 * acceleration * displacement;

		if (discriminant > 0.f)
		{
			// 2 solutions
			time1 = -(velocity + sqrt(discriminant)) / acceleration;
			time2 = -(velocity - sqrt(discriminant)) / acceleration;

			return 2;
		}
		else if (discriminant < 0.f)
		{
			// No solutions
			return 0;
		}
		else
		{
			// 1 solution
			time1 = -velocity / acceleration;

			return 1;
		}
	}
}

#endif