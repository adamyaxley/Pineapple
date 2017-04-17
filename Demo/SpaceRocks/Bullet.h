#pragma once

#include <Pineapple/Pineapple.h>

#include "Warp.h"

class Bullet : public Warp, public pa::TimerHandler
{
public:
	Bullet(pa::World& world);

	void onCreate() override;
	void onStep(pa::Time deltaTime) override;
};
