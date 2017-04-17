/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Graphics/TileSet.h>

pa::TileSet::TileSet(int tileWidth, int tileHeight, const char* path)
	: pa::Resource(path)
	, m_tileSize(tileWidth, tileHeight)
	, m_defaultTileMap(1, 1)
{
}

const pa::Vect2<int>& pa::TileSet::getTileSize() const
{
	return m_tileSize;
}

const pa::Vect2<int>& pa::TileSet::getSize() const
{
	return m_size;
}

void pa::TileSet::setSize(const pa::Vect2<int>& size)
{
	PA_ASSERTF(size.x >= getTileSize().x || size.y >= getTileSize().y,
			   "The size of the TileSet ({}, {}) cannot be smaller than the tile size ({}, {})", size.x, size.y,
			   getTileSize().x, getTileSize().y);
	m_size = size;
	m_defaultTileMap.setSize(size.x / getTileSize().x, size.y / getTileSize().y);
}

// Creates a map with horizontal and vertical wrapping
std::unique_ptr<pa::Map> pa::TileSet::createWrappedMap(float x, float y, const pa::TileMap tilemap, int priority)
{
	return createMap(x, y, tilemap, true, true, priority);
}

// Creates a map without any specific Tile Map, and no wrapping
std::unique_ptr<pa::Map> pa::TileSet::createPlainMap(float x, float y, int priority)
{
	return createMap(x, y, getDefaultTileMap(), false, false, priority);
}

// Creates a map without any specific Tile Map, and horizontal and vertical wrapping
std::unique_ptr<pa::Map> pa::TileSet::createPlainWrappedMap(float x, float y, int priority)
{
	return createMap(x, y, getDefaultTileMap(), true, true, priority);
}

// Get the default Tile Map
pa::TileMap pa::TileSet::getDefaultTileMap() const
{
	return m_defaultTileMap;
}

// Get underlying texture format
pa::Texture::Format pa::TileSet::getFormat() const
{
	return m_format;
}

void pa::TileSet::setFormat(pa::Texture::Format format)
{
	m_format = format;
}
