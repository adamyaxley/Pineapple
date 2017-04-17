/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#if (defined _MSC_VER) && (_MSC_VER < 1600)
typedef unsigned __int16 uint16_t;
#else
	#include <stdint.h>
#endif

#define PA_TILE_HFLIP (1 << 15)
#define PA_TILE_VFLIP (1 << 14)

#define PA_TILE_INDEX 16383

namespace pa
{
	typedef uint16_t Tile;

	// Indices range from 1 - 16383 and correspond to a tileset 0 is a transparent tile
	// Where tiles can be of arbitrary size (multiple of 8)
	/*
	 1  2  3  4
	 5  6  7  8
	*/
	// Use like:
	/*
	Tile T1 = 1;
	Tile T2 = 2 | PA_TILE_HFLIP | PA_TILE_VFLIP;
	Tile T3 = 3;

	Tile* myMap =
		{ T1, T1, T1,
		  T1, T2, T1,
		  T3, T3, T3 };
	*/
}
