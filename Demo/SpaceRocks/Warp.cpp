#include "Warp.h"

Warp::Warp(pa::World& world)
	: pa::Entity(world)
{
}

void Warp::onStep(pa::Time deltaTime)
{
	updatePhysics(deltaTime);

	auto& graphicsSize = getWorld().getPlatform()->getGraphics()->getSize();
	getPosition() += graphicsSize;
	getPosition().x = fmod(getPosition().x, graphicsSize.x);
	getPosition().y = fmod(getPosition().y, graphicsSize.y);

	updateSprite();
}
