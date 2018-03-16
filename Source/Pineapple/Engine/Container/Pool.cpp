/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Container/Pool.h>

pa::Pool::Pool(std::size_t maxObjectSize, std::size_t size)
	: m_maxObjectSize(maxObjectSize)
	, m_indexBuffer(size)
{
	PA_ASSERTF(maxObjectSize > 0, "Max object size must be greater than 0");
	m_objects = static_cast<std::uint8_t*>(pa::Memory::allocate(size * maxObjectSize));
	PA_ASSERTF(m_objects != nullptr, "Failed to allocate memory pool of size {}", size * maxObjectSize);
}

pa::Pool::~Pool()
{
	PA_ASSERTF(getCapacity() == getSize(), "Pool is being deallocated before all of the objects are returned");
	pa::Memory::deallocate(m_objects);
}

std::size_t pa::Pool::getSize() const noexcept
{
	return m_indexBuffer.getSize();
}

std::size_t pa::Pool::getCapacity() const noexcept
{
	return m_indexBuffer.getCapacity();
}