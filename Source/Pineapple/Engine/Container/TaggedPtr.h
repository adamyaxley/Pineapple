/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <cstdint>

namespace pa
{
	template <typename T>
	class TaggedPtr
	{
	private:
		static constexpr std::uintptr_t tagMask = alignof(T) - 1;

	public:
		TaggedPtr()
		{
		}
		~TaggedPtr()
		{
		}

		TaggedPtr(T* ptr, std::uint_fast8_t tag) noexcept
			: m_ptrAndTag(reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(ptr) | tag))
		{
			PA_ASSERTF(tag <= tagMask, "Entropy of tag is too high to be stored in this alignment");
			PA_ASSERTF((reinterpret_cast<uintptr_t>(ptr) & tagMask) == 0, "ptr is not properly aligned");
		}

		T* operator->() noexcept
		{
			return reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(m_ptrAndTag) & ~tagMask);
		}

		std::uint_fast8_t getTag() const noexcept
		{
			return (reinterpret_cast<uintptr_t>(m_ptrAndTag) & tagMask);
		}

	private:
		T* m_ptrAndTag;
	};
}
