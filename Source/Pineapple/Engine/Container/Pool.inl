/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

template <typename T>
template <typename U>
pa::Pool::Deleter<T>::Deleter(const Deleter<U>& convert)
{
	m_pool = convert.m_pool;
}

template <typename T>
pa::Pool::Deleter<T>::Deleter(pa::Pool* pool)
	: m_pool(pool)
{
}

template <typename T>
void pa::Pool::Deleter<T>::operator()(T* object)
{
	m_pool->release(object);
}

template <typename T, typename... Args>
pa::Pool::Ptr<T> pa::Pool::acquire(Args&&... args)
{
	PA_ASSERTF(sizeof(T) <= m_maxObjectSize, "Attempting to allocate an object larger than the max size");
	PA_ASSERTF(!m_indexBuffer.empty(), "Overallocation");

	// Get unused object
	auto index = m_indexBuffer.acquire();
	T* object = reinterpret_cast<T*>(&m_objects[index * m_maxObjectSize]);

	// Construct object in place
	new (object) T(std::forward<Args>(args)...);

	// Return this properly constructed object
	return pa::Pool::Ptr<T>(object, pa::Pool::Deleter<T>(this));
}

template <typename T>
void pa::Pool::release(T* object)
{
	auto objectAddress = reinterpret_cast<std::uint8_t*>(object);

	// Check if address is valid
	PA_ASSERTF(((objectAddress - &m_objects[0]) % m_maxObjectSize) == 0,
			   "Address released is in the pool but is misaligned");
	PA_ASSERTF((objectAddress >= &m_objects[0]) && (objectAddress <= &m_objects[m_maxObjectSize * (getCapacity() - 1)]),
			   "Address released is not from this pool");

	// Get index of object
	auto index = (objectAddress - &m_objects[0]) / m_maxObjectSize;

	// Call destructor
	object->~T();

	// Release the index
	m_indexBuffer.release(index);
}