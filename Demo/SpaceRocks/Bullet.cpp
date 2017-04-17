#include "Bullet.h"
#include "Resource.h"
#include "Rock.h"

Bullet::Bullet(pa::World& world)
	: Warp(world)
	, pa::TimerHandler(world)
{
}

void Bullet::onCreate()
{
	setSprite(g_resource.dot->createSprite());
	startTimer(pa::Time(1.0f), [this] { destroy(); });
}

void Bullet::onStep(pa::Time deltaTime)
{
	Warp::onStep(deltaTime);

	for (auto&& rock : getWorld().getChildList<Rock>())
	{
		if (rock->getAABB().calculateSweptAABB().intersects(getAABB().calculateSweptAABB()))
		{
			rock->destroy();
			destroy();
			break;
		}
	}
}
