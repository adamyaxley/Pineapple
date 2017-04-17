/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Container/Pool.h>
#include <list>

namespace pa
{
	class DynamicPool
	{
	public:
		DynamicPool() = delete;
		DynamicPool(const DynamicPool& copy) = delete;
		DynamicPool(DynamicPool&& move) = default;

		DynamicPool(std::size_t maxObjectSize);
		DynamicPool(std::size_t maxObjectSize, std::size_t size);
		~DynamicPool();

		template <typename T, typename... Args>
		typename Pool::Ptr<T> acquire(Args&&... args);

		int getSize() const noexcept;
		int getCapacity() const noexcept;

		void reserve(std::size_t size);

	private:
		Pool& getFreePool();

		std::list<Pool> m_pools;

		const int m_maxObjectSize;
		int m_nextSize;
	};
}

#include <Pineapple/Engine/Container/DynamicPool.inl>
