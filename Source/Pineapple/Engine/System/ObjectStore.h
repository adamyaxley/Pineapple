/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/System/Object.h>
#include <Pineapple/Engine/System/ObjectInfo.h>
#include <Pineapple/Engine/System/Time.h>
#include <vector>

namespace pa
{
	class ObjectStore
	{
	public:
		ObjectStore();
		~ObjectStore();

		template <typename T, typename... Args>
		std::shared_ptr<T> create(Args&&... args);

		template <typename T>
		const pa::ObjectList<T>& getList();

		template <typename T>
		pa::ObjectList<T>& getChildList();

		template <typename T>
		void setPriority(int priority);

		template <typename T>
		int getPriority();

		std::vector<int> getObjectIds() const;
		ObjectInfoBase& ObjectStore::getObjectInfo(int id);

		void deleteAllInstances();

		void removeDeadInstances();

		void stepInstances(Time deltaTime);

	private:
		template <typename T>
		ObjectInfo<T>& getObjectInfo();

		void sortObjectIds();

		std::vector<int> m_sortedObjectIds;

		std::vector<std::unique_ptr<ObjectInfoBase>> m_objectInfos;
	};
}

#include <Pineapple/Engine/System/ObjectStore.inl>
