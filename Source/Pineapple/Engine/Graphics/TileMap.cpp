/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Graphics/TileMap.h>

pa::TileMap::TileMap(int width, int height, pa::Tile* tiles /*= nullptr*/)
	: m_size(width, height)
	, m_tileData(tiles)
{
}

pa::Tile pa::TileMap::get(int x, int y) const
{
	PA_ASSERTF(x < m_size.x && x >= 0 && y < m_size.y && y >= 0, "Requested tile is not within bounds");

	if (m_tileData)
	{
		return m_tileData[y * m_size.x + x];
	}
	else
	{
		// Return a default pa::Tile that just has the tile ID
		return (y * m_size.x + x + 1);
	}
}