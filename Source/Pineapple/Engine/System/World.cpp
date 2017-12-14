/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Platform/Platform.h>
#include <Pineapple/Engine/System/ObjectStore.h>
#include <Pineapple/Engine/System/World.h>

pa::World::World(std::shared_ptr<Platform> platform)
	: pa::World()
{
	m_platform = platform;
}

pa::World::World()
	: m_time(0)
	, m_ticks(0)
{
	m_flags.set(Flags::IsRunning);
}

pa::World::~World()
{
	// Delete the instances so that they de-register any callbacks with the world first
	m_objectStore.deleteAllInstances();
}

bool pa::World::step(Time deltaTime, const pa::Input& input)
{
	// Change screen
	changeScene();

	// Step instances
	preStepInstances(input);
	stepInstances(deltaTime);

	m_time += deltaTime;

	postStepInstances(input);

	removeDeadInstances();

	// Add one tick
	m_ticks++;

	// Has the game ended?
	return m_flags.getBool(Flags::IsRunning);
}

void pa::World::end()
{
	m_flags.clear(Flags::IsRunning);
}

int pa::World::getTicks() const
{
	return m_ticks;
}

pa::Time pa::World::getTime() const
{
	return m_time;
}

void pa::World::unregisterPreStepInstancesCallback(pa::World::CallbackIterator iterator)
{
	m_preStepInstancesCallbacks.erase(iterator);
}

void pa::World::unregisterPostStepInstancesCallback(pa::World::CallbackIterator iterator)
{
	m_postStepInstancesCallbacks.erase(iterator);
}

void pa::World::preStepInstances(const pa::Input& input)
{
	for (auto&& callback : m_preStepInstancesCallbacks)
	{
		callback(*this, input);
	}
}

void pa::World::postStepInstances(const pa::Input& input)
{
	for (auto&& callback : m_postStepInstancesCallbacks)
	{
		callback(*this, input);
	}
}

void pa::World::stepInstances(Time deltaTime)
{
	m_objectStore.stepInstances(deltaTime);
}

void pa::World::removeDeadInstances()
{
	m_objectStore.removeDeadInstances();
}

void pa::World::changeScene()
{
	// If the screen needs to be changed
	if (m_nextSceneLambda != nullptr)
	{
		m_objectStore.deleteAllInstances();
		m_nextSceneLambda();

		m_nextSceneLambda = nullptr;
	}
}