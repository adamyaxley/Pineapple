#include "Resource.h"
#include <random>

Resource g_resource;

void Resource::create(std::shared_ptr<pa::Platform> platform)
{
	ship = platform->getGraphics()->createTexture("Textures/ship.png");
	dot = platform->getGraphics()->createTexture("Textures/dot.png");
	rock = platform->getGraphics()->createTexture("Textures/rock.png");
	smallRock = platform->getGraphics()->createTexture("Textures/smallRock.png");

	background = platform->getGraphics()->createTileSet("Textures/background.png", 32, 32);
	backgroundTileMap = std::make_shared<pa::TileMap>(20, 20);
	std::uniform_int_distribution<int> dis(0, 4);
	std::mt19937 gen;
	for (int x = 0; x < backgroundTileMap->getSizeConst().x; x++)
	{
		for (int y = 0; y < backgroundTileMap->getSizeConst().y; y++)
		{
			backgroundTileMap->set(x, y, dis(gen));
		}
	}

	destroy = platform->getSound()->createEffect("Sound/destroy.wav");
	fire = platform->getSound()->createEffect("Sound/fire.wav");
	respawn = platform->getSound()->createEffect("Sound/respawn.wav");
}