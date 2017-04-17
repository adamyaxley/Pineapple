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
	std::uniform_int_distribution<int> dis(0, 4);
	std::mt19937 gen;
	for (int i = 0; i < tilesWidth * tilesHeight; i++)
	{
		tileData[i] = dis(gen);
	}

	destroy = platform->getSound()->createEffect("Sound/destroy.wav");
	fire = platform->getSound()->createEffect("Sound/fire.wav");
	respawn = platform->getSound()->createEffect("Sound/respawn.wav");
}