/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Container/Vect2.h>
#include <Pineapple/Engine/Graphics/Tile.h>
#include <Pineapple/Engine/Util/Format.h>
#include <Pineapple/Engine/Util/Macro.h>

namespace pa
{
	class TileMap
	{
	public:
		TileMap(int width, int height, Tile* tiles = nullptr);

		// Gets the size of this tile map (measured in tiles)
		PA_FORMAT_VECTOR_GET_CONST(int, Size, m_size);

		// Sets the size of this tile map (measured in tiles)
		PA_FORMAT_VECTOR_SET_ALL(int, Size, m_size);

		// Gets the tile located at coordinates x and y
		Tile get(int x, int y) const;

	private:
		PA_FORMAT_VECTOR_VAR(int, Size, m_size);

		// A 2d array of Tile
		Tile* const m_tileData;
	};
}
