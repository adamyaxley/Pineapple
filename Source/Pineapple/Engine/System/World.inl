/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <type_traits>

PA_FORCE_INLINE std::shared_ptr<pa::Platform> pa::World::getPlatform()
{
	return m_platform;
}

template <typename T, typename... Args>
void pa::World::resetNextStep(Args&&... args)
{
	m_nextSceneLambda = [&]() { create<T, Args...>(std::forward<Args>(args)...); };
}

template <typename T, typename... Args>
std::shared_ptr<T> pa::World::create(Args&&... args)
{
	static_assert(std::is_base_of<pa::Object, T>::type::value, "object must be derived from pa::Object");

	auto object = m_objectStore.create<T, pa::World&, Args...>(*this, std::forward<Args>(args)...);

	object->onCreate();

	return object;
}

template <typename T>
void pa::World::registerChild(std::shared_ptr<T> child)
{
	m_objectStore.getChildList<T>().push_back(child);
}

template <typename T>
const pa::ObjectList<T>& pa::World::getList()
{
	return m_objectStore.getList<T>();
}

template <typename T>
const pa::ObjectList<T>& pa::World::getChildList()
{
	return m_objectStore.getChildList<T>();
}

template <typename T>
void pa::World::setPriority(int priority)
{
	m_objectStore.setPriority<T>(priority);
}

template <typename T>
int pa::World::getPriority()
{
	return m_objectStore.getPriority<T>();
}

template <typename T>
pa::World::CallbackIterator pa::World::registerPreStepInstancesCallback(T&& callback)
{
	m_preStepInstancesCallbacks.emplace_front(std::forward<T>(callback));
	return m_preStepInstancesCallbacks.begin();
}

template <typename T>
pa::World::CallbackIterator pa::World::registerPostStepInstancesCallback(T&& callback)
{
	m_postStepInstancesCallbacks.emplace_front(std::forward<T>(callback));
	return m_postStepInstancesCallbacks.begin();
}