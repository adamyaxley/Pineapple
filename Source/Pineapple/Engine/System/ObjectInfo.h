/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/System/Counter.h>
#include <Pineapple/Engine/System/Time.h>
#include <Pineapple/Engine/Util/Macro.h>
#include <vector>
#include <memory>

namespace pa
{
	template <typename T>
	using ObjectList = std::vector<std::shared_ptr<T>>;

	class ObjectInfoBase
	{
	public:
		virtual ~ObjectInfoBase()
		{
		}

		PA_FORCE_INLINE void setPriority(int priority);

		PA_FORCE_INLINE int getPriority() const;

		virtual void clearAllInstances() = 0;
		virtual void clearDeadInstances() = 0;
		virtual void stepInstances(Time deltaTime) = 0;
		virtual void cacheObjectListSize() = 0;

	protected:
		PA_FORCE_INLINE ObjectInfoBase();

	private:
		int m_priority;
	};

	template <typename T>
	class ObjectInfo : public ObjectInfoBase
	{
	public:
		ObjectInfo();

		void clearAllInstances() override;
		void clearDeadInstances() override;
		void stepInstances(Time deltaTime) override;
		void cacheObjectListSize() override;

		pa::ObjectList<T>& getList();

		pa::ObjectList<T>& getChildList();

		static unsigned int getId() noexcept;

	private:
		pa::ObjectList<T> m_instanceList;

		pa::ObjectList<T> m_childList;

		std::size_t m_objectListSize;
	};
}

#include <Pineapple/Engine/System/ObjectInfo.inl>
