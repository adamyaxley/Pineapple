/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Graphics/TileSet.h>

pa::TileSet::TileSet(int tileWidth, int tileHeight, const pa::FilePath& path)
	: pa::Resource(path)
	, m_tileSize(tileWidth, tileHeight)
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
