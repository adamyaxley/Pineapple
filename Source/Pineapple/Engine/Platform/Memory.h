/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

namespace pa
{
	namespace Memory
	{
		void* allocate(unsigned long size);

		void deallocate(void*);

		void* reallocate(void*, unsigned long size);
	}
}
