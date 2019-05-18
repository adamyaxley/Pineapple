/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

PA_FORCE_INLINE pa::ObjectInfoBase::ObjectInfoBase()
	: m_priority(0)
{
}

PA_FORCE_INLINE void pa::ObjectInfoBase::setPriority(int priority)
{
	m_priority = priority;
}

PA_FORCE_INLINE int pa::ObjectInfoBase::getPriority() const
{
	return m_priority;
}

template <typename T>
pa::ObjectInfo<T>::ObjectInfo()
{
}

template <typename T>
void pa::ObjectInfo<T>::clearAllInstances()
{
	m_instanceList.clear();
	m_childList.clear();
}

template <typename T>
void pa::ObjectInfo<T>::clearDeadInstances()
{
	for (auto i = m_instanceList.size() - 1; i != std::numeric_limits<std::size_t>::max(); i--)
	{
		if (m_instanceList[i]->isDead())
		{
			m_instanceList[i] = std::move(m_instanceList.back());
			m_instanceList.resize(m_instanceList.size() - 1);
		}
	}

	for (auto i = m_childList.size() - 1; i != std::numeric_limits<std::size_t>::max(); i--)
	{
		if (m_childList[i]->isDead())
		{
			m_childList[i] = std::move(m_childList.back());
			m_childList.resize(m_childList.size() - 1);
		}
	}
}

template <typename T>
void pa::ObjectInfo<T>::stepInstances(Time deltaTime)
{
	for (std::size_t i = 0; i < m_objectListSize; i++)
	{
		m_instanceList[i]->step(deltaTime);
	}
}

template <typename T>
void pa::ObjectInfo<T>::cacheObjectListSize()
{
	m_objectListSize = m_instanceList.size();
}

template <typename T>
pa::ObjectList<T>& pa::ObjectInfo<T>::getList()
{
	return m_instanceList;
}

template <typename T>
pa::ObjectList<T>& pa::ObjectInfo<T>::getChildList()
{
	return m_childList;
}

template <typename T>
unsigned int pa::ObjectInfo<T>::getId() noexcept
{
	static const pa::Counter counter;
	return counter.getValue();
}