/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Physics/AABB.h>

#include <float.h>

pa::AABB::AABB()
{
}

pa::AABB::~AABB()
{
}

bool pa::AABB::collidesWithStatic(const pa::AABB& other) const
{
	// <todo> optimise this
	float entryTime;
	pa::Vect2<float> normal;
	return collidesWithStatic(other, entryTime, normal);
}

// Checks overlap of two AABB bounding boxes
bool pa::AABB::collidesWithStatic(const pa::AABB& other, float& entryTime, pa::Vect2<float>& normal) const
{
	// Do broadphase
	pa::AABB broadphase = calculateSweptAABB();

	if (!broadphase.intersects(other))
	{
		return false;
	}

	float xEntryDistance, yEntryDistance;
	float xExitDistance, yExitDistance;

	// find the distance between the objects on the near and far sides for both x and y
	if (getDisplacementConst().x > 0.0f)
	{
		xEntryDistance = other.getPositionConst().x - (getPositionConst().x + getSizeConst().x);
		xExitDistance = (other.getPositionConst().x + other.getSizeConst().x) - getPositionConst().x;
	}
	else
	{
		xEntryDistance = (other.getPositionConst().x + other.getSizeConst().x) - getPositionConst().x;
		xExitDistance = other.getPositionConst().x - (getPositionConst().x + getSizeConst().x);
	}

	if (getDisplacementConst().y > 0.0f)
	{
		yEntryDistance = other.getPositionConst().y - (getPositionConst().y + getSizeConst().y);
		yExitDistance = (other.getPositionConst().y + other.getSizeConst().y) - getPositionConst().y;
	}
	else
	{
		yEntryDistance = (other.getPositionConst().y + other.getSizeConst().y) - getPositionConst().y;
		yExitDistance = other.getPositionConst().y - (getPositionConst().y + getSizeConst().y);
	}

	// Find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
	float xEntryTime, yEntryTime;
	float xExitTime, yExitTime;

	if (getDisplacementConst().x == 0.0f)
	{
		xEntryTime = -FLT_MAX;
		xExitTime = FLT_MAX;
	}
	else
	{
		xEntryTime = xEntryDistance / getDisplacementConst().x;
		xExitTime = xExitDistance / getDisplacementConst().x;
	}

	if (getDisplacementConst().y == 0.0f)
	{
		yEntryTime = -FLT_MAX;
		yExitTime = FLT_MAX;
	}
	else
	{
		yEntryTime = yEntryDistance / getDisplacementConst().y;
		yExitTime = yExitDistance / getDisplacementConst().y;
	}

	// Time at which the closest axis will enter
	entryTime = PA_MAX(xEntryTime, yEntryTime);

	// Time at which the closest axis will exit
	float exitTime = PA_MIN(xExitTime, yExitTime);

	// Check for no collision
	if (entryTime > exitTime || (xEntryTime < 0.0f && yEntryTime < 0.0f) || // This objects axis have passed the others
																			// (or are on the other side)
		entryTime > 1.0f)													// This object has not yet entered the other
	{
		return false;
	}
	else // Collision
	{
		// Calculate normal of collided surface
		if (xEntryTime > yEntryTime)
		{
			if (xEntryDistance < 0.0f)
			{
				normal.x = 1.0f;
				normal.y = 0.0f;
			}
			else
			{
				normal.x = -1.0f;
				normal.y = 0.0f;
			}
		}
		else
		{
			if (yEntryDistance < 0.0f)
			{
				normal.x = 0.0f;
				normal.y = 1.0f;
			}
			else
			{
				normal.x = 0.0f;
				normal.y = -1.0f;
			}
		}

		return true;
	}
}

pa::Vect2<float> pa::AABB::resolve(const pa::AABB& other, const float impactTime,
								   const pa::Vect2<float>& response) const
{
	pa::Vect2<float> position;
	float extra = 0.001f;

	if (response.y > 0)
	{
		// Bottom
		position.x = getPositionConst().x + getDisplacementConst().x;
		position.y = other.getPositionConst().y + other.getSizeConst().y + extra;
	}
	else if (response.y < 0)
	{
		// Top
		position.x = getPositionConst().x + getDisplacementConst().x;
		position.y = other.getPositionConst().y - getSizeConst().y - extra;
	}
	else if (response.x > 0)
	{
		// Right
		position.x = other.getPositionConst().x + other.getSizeConst().x + extra;
		position.y = getPositionConst().y + getDisplacementConst().y;
	}
	else
	{
		// Left
		position.x = other.getPositionConst().x - getSizeConst().x - extra;
		position.y = getPositionConst().y + getDisplacementConst().y;
	}

	return position;
}

bool pa::AABB::intersects(const pa::AABB& other) const
{
	return !(getPositionConst().x + getSizeConst().x <= other.getPositionConst().x ||
			 getPositionConst().x >= other.getPositionConst().x + other.getSizeConst().x ||
			 getPositionConst().y + getSizeConst().y <= other.getPositionConst().y ||
			 getPositionConst().y >= other.getPositionConst().y + other.getSizeConst().y);
}

pa::AABB pa::AABB::calculateSweptAABB() const
{
	pa::AABB broadphasebox;
	broadphasebox.getPosition().x =
		getDisplacementConst().x > 0 ? getPositionConst().x : getPositionConst().x + getDisplacementConst().x;
	broadphasebox.getPosition().y =
		getDisplacementConst().y > 0 ? getPositionConst().y : getPositionConst().y + getDisplacementConst().y;
	broadphasebox.getSize().x = getDisplacementConst().x > 0 ? getDisplacementConst().x + getSizeConst().x
															 : getSizeConst().x - getDisplacementConst().x;
	broadphasebox.getSize().y = getDisplacementConst().y > 0 ? getDisplacementConst().y + getSizeConst().y
															 : getSizeConst().y - getDisplacementConst().y;

	return broadphasebox;
}
