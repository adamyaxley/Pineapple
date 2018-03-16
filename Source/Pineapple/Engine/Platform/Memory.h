/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <cstddef>

namespace pa
{
	namespace Memory
	{
		void* allocate(std::size_t size);

		void deallocate(void*);

		void* reallocate(void*, std::size_t size);
	}
}
