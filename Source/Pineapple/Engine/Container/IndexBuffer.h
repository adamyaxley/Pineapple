/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Platform/Memory.h>
#include <Pineapple/Engine/Util/Macro.h>

// Stores an arbitrary number of indexes ranging from 0 to(size - 1).Has O(1)
// operations for aquiring a free index, and releasing a used one.
namespace pa
{
	class IndexBuffer
	{
	public:
		PA_FORCE_INLINE IndexBuffer(IndexBuffer&& move) = delete;

		// Initialise a buffer of indexes ranging from 0 to (capacity - 1)
		PA_FORCE_INLINE IndexBuffer(std::size_t capacity);

		// Initialise a buffer of indexes ranging from startIndex to endIndex
		PA_FORCE_INLINE IndexBuffer(const int startIndex, std::size_t capacity);

		// Destructor
		PA_FORCE_INLINE ~IndexBuffer();

		// Returns true if the buffer is empty
		PA_FORCE_INLINE bool empty() const;

		// Gets the size of the buffer
		PA_FORCE_INLINE int getSize() const noexcept;

		// Gets the capacity of the buffer
		PA_FORCE_INLINE int getCapacity() const noexcept;

		// Acquire a free index
		PA_FORCE_INLINE int acquire();

		// Release a index back to the buffer
		PA_FORCE_INLINE void release(int id);

	private:
		// Buffer start pointer
		int* m_buffer;

		// Size of the renaming buffer
		int m_size;

		// Total size of the buffers capacity
		const int m_capacity;
	};
}

#include <Pineapple/Engine/Container/IndexBuffer.inl>
