/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/System/ObjectStore.h>

pa::ObjectStore::ObjectStore()
{
}

pa::ObjectStore::~ObjectStore()
{
	deleteAllInstances();
}

std::vector<int> pa::ObjectStore::getObjectIds() const
{
	return m_sortedObjectIds;
}

pa::ObjectInfoBase& pa::ObjectStore::getObjectInfo(int id)
{
	return *m_objectInfos[id].get();
}

void pa::ObjectStore::deleteAllInstances()
{
	for (auto&& id : getObjectIds())
	{
		getObjectInfo(id).clearAllInstances();
	}
}

void pa::ObjectStore::removeDeadInstances()
{
	for (auto&& id : getObjectIds())
	{
		getObjectInfo(id).clearDeadInstances();
	}
}

void pa::ObjectStore::stepInstances(Time deltaTime)
{
	auto objectIds = getObjectIds();
	for (auto&& id : objectIds)
	{
		getObjectInfo(id).cacheObjectListSize();
	}

	for (auto&& id : objectIds)
	{
		getObjectInfo(id).stepInstances(deltaTime);
	}
}

void pa::ObjectStore::sortObjectIds()
{
	std::sort(m_sortedObjectIds.begin(), m_sortedObjectIds.end(), [this](const int& a, const int& b) {
		return m_objectInfos[a]->getPriority() < m_objectInfos[b]->getPriority();
	});
}