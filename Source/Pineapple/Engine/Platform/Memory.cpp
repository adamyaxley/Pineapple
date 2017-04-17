/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Platform/Memory.h>
#include <Pineapple/Engine/Util/Macro.h>
#include <string>

void* pa::Memory::allocate(unsigned long size)
{
	void* addr = malloc(size);

	PA_ASSERTF(addr != nullptr, "Failed to allocate memory of size: {} bytes", size);
	// pa::Log::info("Allocated {} bytes", size);
	return addr;
}

void pa::Memory::deallocate(void* addr)
{
	// pa::Log::info("Deallocated {}", addr);
	free(addr);
}

void* pa::Memory::reallocate(void* block, unsigned long size)
{
	void* addr = realloc(block, size);
	PA_ASSERTF(addr != nullptr, "Failed to reallocate memory to size: {} bytes", size);
	pa::Log::info("Reallocated to {} bytes", size);
	return addr;
}