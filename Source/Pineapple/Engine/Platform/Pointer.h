/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Container/Vect2.h>
#include <Pineapple/Engine/Util/Macro.h>

namespace pa
{
	class Pointer
	{
	public:
		PA_FORCE_INLINE Pointer();
		PA_FORCE_INLINE ~Pointer();

		// Gets the pointers position
		PA_FORCE_INLINE const Vect2<int>& getPosition() const;

		// Sets the position of the pointer
		PA_FORCE_INLINE void setPosition(int x, int y);

		// Gets whether the pointer is being pressed down
		PA_FORCE_INLINE bool getDown() const;

		// Sets whether the pointer is being pressed down
		PA_FORCE_INLINE void setDown(bool down);

	private:
		Vect2<int> m_position;
		bool m_down;
	};
}

#include <Pineapple/Engine/Platform/Pointer.inl>
