/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Platform/Platform.h>
#include <Pineapple/Engine/System/Input.h>
#include <Pineapple/Engine/System/ObjectStore.h>
#include <Pineapple/Engine/System/Time.h>
#include <functional>

namespace pa
{
	template <typename T>
	class EnableChildList;

	/// \brief A World manages the lifetime and interaction of all objects that have been created inside it. 
	class World
	{
	public:
		using Callback = std::function<void(World&, const Input& input)>;
		using CallbackContainer = std::list<Callback>;
		using CallbackIterator = CallbackContainer::const_iterator;

		template <typename T>
		friend class EnableChildList;

		friend ObjectStore;

		/// \brief Basic constructor to create a fresh new World.
		World();

		/// \brief Creates a World
		/// \param platform The Platform to store inside the world
		/// \notes The World doesn't actually use the Platform in any way, it is only provided so that it can be accessed conveniently by calling getPlatform()
		World(std::shared_ptr<Platform> platform);

		/// \brief Do not allow copy construction
		World(const World& copy) = delete;

		/// \brief Allow move construction
		World(World&& move) = default;

		/// \brief Do not allow copy assignment
		World& operator=(const World& copy) = delete;

		/// \brief Allow move assignment
		World& operator=(World&& move) = default;

		/// \brief When the world is deconstructed all objects contained within it will also be deconstructed.
		~World();

		/// \returns A std::shared_ptr to the Platform that is registered to this world.
		/// \notes The world doesn't actually use the Platform object in any way, it is only provided as a convenience function so that objects created in the world
		/// can access the current Platform.
		PA_FORCE_INLINE std::shared_ptr<Platform> getPlatform();

		/// \brief Steps the world one step into the future, stepping all objects. 
		/// \returns true if the world hasn't ended this step
		/// \notes Different types of objects will be processed according to their priority, and objects of the same type will be processed in an unspecified order, which may change between between calls to step()
		/// \param deltaTime How much to increment the World's time by.
		/// \param input The input to the World this step, this is normally provided by pa::Platform::getInput() but could also be generated via other methods.
		bool step(Time deltaTime, const Input& input = Input());

		/// \brief End the world, destroying all objects.
		/// \notes This is usually called when the simulation has finished and the application is closing.
		void end();

		/// \brief Resets the World by destroying all existing objects and then creating a single instance of `T`.
		/// \param args Additional arguments to forward to the constructor of `T` (a reference to the World is already passed as a first argument to `T`)
		template <typename T, typename... Args>
		void resetNextStep(Args&&... args);

		/// \brief Creates a new instance of `T` and adds it to the world
		/// \returns A std::shared_ptr to `T`
		/// \param args Additional arguments to forward to the constructor of `T` (a reference to the World is already passed as a first argument to `T`)
		template <typename T, typename... Args>
		std::shared_ptr<T> create(Args&&... args);

		/// \returns A constant reference to a list of `T`.
		template <typename T>
		const pa::ObjectList<T>& getList();

		/// \returns A constant reference to the list of all children of `T`. Children are defined as instances of `T` or instances of objects that derive from	`T`. To track children of `T`, `T` must inherit from EnableChildList<T>.
		template <typename T>
		const pa::ObjectList<T>& getChildList();

		/// \brief Set the priority of `T`.
		/// \notes Objects with lower priority will have their instances stepped first.
		template <typename T>
		void setPriority(int priority);

		/// \returns The priority of `T`
		/// \notes Objects with lower priority will have their instances stepped first.
		template <typename T>
		int getPriority();

		/// \returns The cumulative time that the has passed since the World was created
		Time getTime() const;

		/// \returns The number of ticks (number of times step() has been completely processed) since the World was created.
		int getTicks() const;

		/// \brief Registers a callback that will be fired before the instances are stepped.
		/// \returns A CallbackIterator that must be passed into unregisterPreStepInstancesCallback when un-registering the callback.
		template <typename T>
		World::CallbackIterator registerPreStepInstancesCallback(T&& callback);

		/// \brief Un-registers an existing callback that was registered by registerPreStepInstancesCallback.
		/// \remarks after calling this function `iterator` will be invalidated.
		void unregisterPreStepInstancesCallback(World::CallbackIterator iterator);

		/// \brief Registers a callback that will be fired after the instances are stepped.
		/// \returns A CallbackIterator that must be passed into unregisterPostStepInstancesCallback when un-registering the callback.
		template <typename T>
		World::CallbackIterator registerPostStepInstancesCallback(T&& callback);

		/// \brief Un-registers an existing callback that was registered by registerPostStepInstancesCallback.
		/// \remarks after calling this function `iterator` will be invalidated.
		void unregisterPostStepInstancesCallback(World::CallbackIterator iterator);

	private:
		enum class Flags
		{
			IsRunning,
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
