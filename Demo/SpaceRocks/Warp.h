#pragma once

#include <Pineapple/Pineapple.h>

class Warp : public pa::Entity
{
public:
	Warp(pa::World& world);

	virtual void onStep(pa::Time deltaTime) override;
};