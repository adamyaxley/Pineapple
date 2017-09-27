#include "Level.h"
#include "Player.h"
#include "Resource.h"
#include "Rock.h"

Level::Level(pa::World& world)
	: pa::Object(world)
	, pa::InputHandler(world)
{
	m_background = g_resource.background->createMap(g_resource.backgroundTileMap, 0, 0, false, false, -1);
}

void Level::onCreate()
{
	getWorld().create<Player>()->getPosition().cart(320, 320);
	getWorld().create<Rock>()->getPosition().cart(64, 64);
	getWorld().create<Rock>()->getPosition().cart(570, 64);
	getWorld().create<Rock>()->getPosition().cart(570, 570);
	getWorld().create<Rock>()->getPosition().cart(64, 570);
}

void Level::onStep(pa::Time deltaTime)
{
	if (getWorld().getList<Rock>().size() + getWorld().getList<SmallRock>().size() == 0)
	{
		getWorld().resetNextStep<Level>();
	}
}
