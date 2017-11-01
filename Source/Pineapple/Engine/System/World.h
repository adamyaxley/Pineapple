/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Platform/Platform.h>
#include <Pineapple/Engine/System/Input.h>
#include <Pineapple/Engine/System/ObjectStore.h>
#include <Pineapple/Engine/System/Time.h>
#include <Pineapple/Engine/System/EnableChildList.h>
#include <functional>

namespace pa
{
	class World
	{
	public:
		using Callback = std::function<void(World&, const Input& input)>;
		using CallbackContainer = std::list<Callback>;
		using CallbackIterator = CallbackContainer::const_iterator;

		template <typename T>
		friend class EnableChildList;

		friend ObjectStore;

		World(std::shared_ptr<Platform> platform);

		// A world without a platform
		World();
		World(const World& copy) = delete;

		~World();

		PA_FORCE_INLINE std::shared_ptr<Platform> getPlatform();

		// Steps the world one step into the future, processing all objects and events, this returns true if the world
		// hasn't ended this step
		bool step(Time deltaTime, const Input& input = Input());

		// End the world, destroying all objects
		void end();

		// Specify an object to use for the next scene, which will destroy all objects and create a single instance of
		// the specified object on the next step
		template <typename T, typename... Args>
		void resetNextStep(Args&&... args);

		// Creates a new instance and adds it to the world
		template <typename T, typename... Args>
		std::shared_ptr<T> create(Args&&... args);

		// Get the instance list of an object
		template <typename T>
		const pa::ObjectList<T>& getList();

		// Get the list of children of an object (not including instances of that object)
		template <typename T>
		const pa::ObjectList<T>& getChildList();

		// Set the priority of an objects instances, lower priorities will be processed first
		template <typename T>
		void setPriority(int priority);

		// Get the priority of an objects instances
		template <typename T>
		int getPriority();

		// Get the time since the world was created
		Time getTime() const;

		// Get the ticks (number of times step() has been completely processed) since the world began
		int getTicks() const;

		// Returns true if the world is currently stepping (inside the body of step())
		bool isStepping() const;

		template <typename T>
		World::CallbackIterator registerPreStepInstancesCallback(T&& callback);

		void unregisterPreStepInstancesCallback(World::CallbackIterator iterator);

		template <typename T>
		World::CallbackIterator registerPostStepInstancesCallback(T&& callback);

		void unregisterPostStepInstancesCallback(World::CallbackIterator iterator);

	private:
		enum class Flags
		{
			IsRunning,
			IsStepping,
			is_enum_bitfield
		};

		void preStepInstances(const Input& input);

		void stepInstances(Time deltaTime);

		void removeDeadInstances();

		void postStepInstances(const Input& input);

		void changeScene();

		// Register a child of T
		template <typename T>
		void registerChild(std::shared_ptr<T> child);

		template <typename T>
		PA_FORCE_INLINE void registerPostConstructionObjectTransform(T&& functor);

		PA_FORCE_INLINE void executePostConstructionObjectTransforms(std::shared_ptr<Object> object);

		std::list<std::function<void(std::shared_ptr<Object>)>> m_postConstructionObjectTransforms;

		std::shared_ptr<Platform> m_platform;

		ObjectStore m_objectStore;

		Time m_time;
		int m_ticks;

		Bitfield<Flags> m_flags;

		std::function<void()> m_nextSceneLambda;

		CallbackContainer m_preStepInstancesCallbacks;
		CallbackContainer m_postStepInstancesCallbacks;
	};
}

#include <Pineapple/Engine/System/World.inl>
