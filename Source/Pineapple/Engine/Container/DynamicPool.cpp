/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Container/DynamicPool.h>

#include <algorithm>

namespace paStd
{
	template <class InputIt, class T, class BinaryOperation>
	T accumulate(InputIt first, InputIt last, T init, BinaryOperation op)
	{
		for (; first != last; ++first)
		{
			init = op(init, *first);
		}
		return init;
	}
}

pa::DynamicPool::DynamicPool(std::size_t maxObjectSize)
	: m_maxObjectSize(maxObjectSize)
	, m_nextSize(0)
{
}

pa::DynamicPool::DynamicPool(std::size_t maxObjectSize, std::size_t size)
	: m_maxObjectSize(maxObjectSize)
	, m_nextSize(size)
{
	PA_ASSERTF(maxObjectSize > 0, "Max object size must be greater than 0");
	PA_ASSERTF(size > 0, "Reserved size must be greater than 0");
	m_pools.emplace_back(maxObjectSize, size);
}

pa::DynamicPool::~DynamicPool()
{
}

int pa::DynamicPool::getSize() const noexcept
{
	// use std::reduce() when C++17 comes out
	return paStd::accumulate(m_pools.begin(), m_pools.end(), 0,
					  [](int sum, const pa::Pool& pool) { return sum + pool.getSize(); });
}

int pa::DynamicPool::getCapacity() const noexcept
{
	return paStd::accumulate(m_pools.begin(), m_pools.end(), 0,
					  [](int sum, const pa::Pool& pool) { return sum + pool.getCapacity(); });
}

void pa::DynamicPool::reserve(std::size_t size)
{
	int capacity = getCapacity();

	if (capacity < static_cast<int>(size))
	{
		m_pools.emplace_back(m_maxObjectSize, size - capacity);
		m_nextSize = size;
	}
}

pa::Pool& pa::DynamicPool::getFreePool()
{
	// Find the first free pool <todo> use reverse iterator
	auto freePool =
		std::find_if(m_pools.rbegin(), m_pools.rend(), [this](const pa::Pool& pool) { return pool.getSize() > 0; });

	if (freePool != m_pools.rend())
	{
		// Use an object from a free pool
		return *freePool;
	}
	else
	{
		// Create a new pool, doubling the total size
		m_pools.emplace_back(m_maxObjectSize, m_nextSize);
		m_nextSize <<= 1;
		return m_pools.back();
	}
}
