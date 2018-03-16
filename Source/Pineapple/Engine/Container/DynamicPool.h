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

		std::size_t getSize() const noexcept;
		std::size_t getCapacity() const noexcept;

		void reserve(std::size_t size);

	private:
		Pool& getFreePool();

		std::list<Pool> m_pools;

		const std::size_t m_maxObjectSize;
		std::size_t m_nextSize;
	};
}

#include <Pineapple/Engine/Container/DynamicPool.inl>
