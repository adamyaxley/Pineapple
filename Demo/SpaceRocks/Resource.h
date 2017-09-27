#pragma once

#include <Pineapple/Pineapple.h>

struct Resource
{
	std::shared_ptr<pa::Texture> ship;
	std::shared_ptr<pa::Texture> dot;
	std::shared_ptr<pa::Texture> rock;
	std::shared_ptr<pa::Texture> smallRock;

	std::shared_ptr<pa::TileSet> background;
	std::shared_ptr<pa::TileMap> backgroundTileMap;

	std::shared_ptr<pa::Effect> destroy;
	std::shared_ptr<pa::Effect> fire;
	std::shared_ptr<pa::Effect> respawn;

	void create(std::shared_ptr<pa::Platform> platform);
};

extern Resource g_resource;