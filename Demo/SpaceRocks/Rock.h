#pragma once

#include <Pineapple/Pineapple.h>
#include <random>

#include "Resource.h"
#include "Warp.h"

class Rock : public Warp, private pa::EnableChildList<Rock>
{
public:
	float m_rotation;

	Rock(pa::World& world);

	void onCreate() override;
	void onStep(pa::Time deltaTime) override;
	void onDestroy() override;

	static std::mt19937 gen;
};

class SmallRock : public Rock
{
public:
	SmallRock(pa::World& world);

	void onCreate() override;
	void onDestroy() override;
};
