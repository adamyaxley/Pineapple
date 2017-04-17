/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

template <typename T, typename... Args>
pa::Pool::Ptr<T> pa::DynamicPool::acquire(Args&&... args)
{
	auto& pool = getFreePool();
	return pool.acquire<T>(std::forward<Args>(args)...);
}