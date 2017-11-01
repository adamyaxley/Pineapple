/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <algorithm>

template <typename T, typename... Args>
std::shared_ptr<T> pa::ObjectStore::create(Args&&... args)
{
	auto object = std::make_shared<T>(std::forward<Args>(args)...);

	// Add to T instance list
	getObjectInfo<T>().getList().push_back(object);

	// Execute child registration functions
	object->getWorld().executePostConstructionObjectTransforms(object);

	return object;
}

template <typename T>
const pa::ObjectList<T>& pa::ObjectStore::getList()
{
	return getObjectInfo<T>().getList();
}

template <typename T>
pa::ObjectList<T>& pa::ObjectStore::getChildList()
{
	return getObjectInfo<T>().getChildList();
}

template <typename T>
void pa::ObjectStore::setPriority(int priority)
{
	auto& objectInfo = getObjectInfo<T>();

	if (priority != objectInfo.getPriority())
	{
		objectInfo.setPriority(priority);
		sortObjectIds();
	}
}

template <typename T>
int pa::ObjectStore::getPriority()
{
	return getObjectInfo<T>().getPriority();
}

template <typename T>
pa::ObjectInfo<T>& pa::ObjectStore::getObjectInfo()
{
	const unsigned int id = pa::ObjectInfo<T>::getId();

	if (m_objectInfos.size() <= static_cast<size_t>(id))
	{
		m_objectInfos.resize(id + 1);
	}

	if (m_objectInfos[id] == nullptr)
	{
		m_sortedObjectIds.push_back(id);
		m_objectInfos[id] = std::make_unique<pa::ObjectInfo<T>>();
		sortObjectIds();
	}

	return *static_cast<pa::ObjectInfo<T>*>(m_objectInfos[id].get());
}