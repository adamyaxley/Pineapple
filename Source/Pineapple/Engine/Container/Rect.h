/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

namespace pa
{
	template <class T>
	struct Rect
	{
		Rect()
			: x1(0)
			, y1(0)
			, x2(0)
			, y2(0)
		{
		}
		Rect(T _x1, T _y1, T _x2, T _y2)
			: x1(_x1)
			, y1(_y1)
			, x2(_x2)
			, y2(_y2)
		{
		}
		~Rect()
		{
		}

		T x1, y1, x2, y2;
	};
}
