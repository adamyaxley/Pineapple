/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Platform/ResourceManager.h>
#include <Pineapple/Engine/Util/Macro.h>

pa::ResourceManager::ResourceManager()
{
}

pa::ResourceManager::~ResourceManager()
{
	unloadAll();
}

void pa::ResourceManager::add(std::shared_ptr<pa::Resource> resource)
{
	pa::ResourceState state;
	state.isLoaded = false;
	state.isMonitored = true;

	if (resource->getPath().getModificationTime(state.modificationTime) != pa::FileResult::Success)
	{
		pa::Log::info("Failed to get the modification time for {}, Not added to resource monitoring.",
					  resource->getPath().asString());
		state.isMonitored = false;
	}

	state.resource = resource;
	m_resourceStates.push_back(std::move(state)); // <todo> why was this originally addToHead
}

void pa::ResourceManager::addPlainDependency(std::shared_ptr<pa::Dependency> dependency)
{
	m_plainDependencies.push_back(dependency);
}

void pa::ResourceManager::unloadAll()
{
	for (auto&& state : m_resourceStates)
	{
		pa::Resource* resource = state.resource.get();

		if (resource->isLoaded())
		{
			resource->unload();
		}
	}
}

void pa::ResourceManager::loadAll()
{
	for (auto&& state : m_resourceStates)
	{
		pa::Resource* resource = state.resource.get();

		if (!resource->isLoaded())
		{
			resource->load();
		}
	}
}

int pa::ResourceManager::getCount() const
{
	int count = 0;

	for (auto&& state : m_resourceStates)
	{
		pa::Resource* resource = state.resource.get();

		if (resource->isLoaded())
		{
			count++; // <todo> use std algo
		}
	}

	return count;
}

void pa::ResourceManager::saveState()
{
	for (auto&& state : m_resourceStates)
	{
		state.isLoaded = state.resource->isLoaded();
	}
}

void pa::ResourceManager::restoreState()
{
	for (auto&& state : m_resourceStates)
	{
		pa::Resource* resource = state.resource.get();

		if (state.isLoaded && !resource->isLoaded())
		{
			resource->load();
		}
		else if (!state.isLoaded && resource->isLoaded())
		{
			resource->unload();
		}
	}
}

void pa::ResourceManager::reloadModified()
{
	for (auto&& state : m_resourceStates)
	{
		pa::Resource* resource = state.resource.get();

		if (state.isMonitored && (resource->isLoaded() || resource->hasFailedToLoad()))
		{
			std::chrono::system_clock::time_point modificationTime;

			pa::FileResult result = resource->getPath().getModificationTime(modificationTime);

			if (result != pa::FileResult::Success)
			{
				pa::Log::info("{}: {}", pa::FileSystem::getResultString(result), resource->getPath().asString());
			}
			else
			{
				if (modificationTime > state.modificationTime)
				{
					pa::Log::info("Reloading modified: {}", resource->getPath().asString());

					// The file has changed, reload it
					state.modificationTime = modificationTime;
					resource->reload();
				}
				else if (resource->hasFailedToLoad() &&
						 std::chrono::duration<float>(std::chrono::system_clock::now() - resource->getLastLoadTime())
								 .count() > 1.0f)
				{
					pa::Log::info("Retrying to load: {}", resource->getPath().asString());

					// Try loading again
					resource->load();
				}
			}
		}
	}
}
