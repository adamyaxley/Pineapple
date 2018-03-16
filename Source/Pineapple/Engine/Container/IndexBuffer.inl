/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Platform/Memory.h>

PA_FORCE_INLINE pa::IndexBuffer::IndexBuffer(std::size_t capacity)
	: pa::IndexBuffer(0, capacity)
{
}

PA_FORCE_INLINE pa::IndexBuffer::IndexBuffer(const std::size_t startIndex, const std::size_t capacity)
	: m_size(capacity)
	, m_capacity(capacity)
{
	m_buffer = static_cast<std::size_t*>(pa::Memory::allocate(capacity * sizeof(std::size_t)));

	// Fill with indexes
	for (std::size_t i = 0; i < capacity; i++)
	{
		*(m_buffer + i) = i + startIndex;
	}
}

PA_FORCE_INLINE pa::IndexBuffer::~IndexBuffer()
{
	if (m_buffer)
	{
		pa::Memory::deallocate(m_buffer);
	}
}

PA_FORCE_INLINE bool pa::IndexBuffer::empty() const
{
	return (m_size == 0);
}

PA_FORCE_INLINE std::size_t pa::IndexBuffer::acquire()
{
	PA_ASSERTF(!empty(), "The index buffer is empty");

	--m_size;

	std::size_t id = *(m_buffer + m_size);

	return id;
}

PA_FORCE_INLINE void pa::IndexBuffer::release(const std::size_t id)
{
	PA_ASSERTF(m_size != getCapacity(), "Cannot release index into full buffer");
	PA_ASSERTF(id < getCapacity() && id >= 0, "Cannot release an index ({}) outside of the range", id);

	*(m_buffer + m_size) = id;

	++m_size;
}

PA_FORCE_INLINE std::size_t pa::IndexBuffer::getSize() const noexcept
{
	return m_size;
}

PA_FORCE_INLINE std::size_t pa::IndexBuffer::getCapacity() const noexcept
{
	return m_capacity;
}