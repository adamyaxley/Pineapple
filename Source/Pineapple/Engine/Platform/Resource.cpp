/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Platform/Resource.h>
#include <Pineapple/Engine/Util/Macro.h>

pa::Resource::Resource(const char* path)
	: m_loadState(pa::ResourceLoadState::SuccessfullyUnloaded)
	, m_path(path)
{
}

pa::Resource::~Resource()
{
	PA_ASSERTF(!isLoaded(), "This resource is still loaded: {}", getPath())
}

void pa::Resource::reload()
{
	if (isLoaded())
	{
		unload();
	}

	load();
}

void pa::Resource::load()
{
	// can do reference counting here in the future
	PA_ASSERTF(!isLoaded(), "This resource cannot be acquired twice: {}", getPath());

	m_lastLoadTime = std::chrono::system_clock::now();

	if (onLoad())
	{
		m_loadState = pa::ResourceLoadState::SuccessfullyLoaded;
		notifyChildDependencies();
	}
	else
	{
		m_loadState = pa::ResourceLoadState::FailedToLoad;
		pa::Log::info("Failed to load {}", getPath());
	}
}

void pa::Resource::unload()
{
	// can do reference counting here in the future
	PA_ASSERTF(isLoaded(), "This resource has already been unloaded: {}", getPath());
	if (onUnload())
	{
		m_loadState = pa::ResourceLoadState::SuccessfullyUnloaded;
		notifyChildDependencies();
	}
	else
	{
		m_loadState = pa::ResourceLoadState::FailedToUnload;
		pa::Log::info("Failed to unload {}", getPath());
	}
}

bool pa::Resource::isLoaded() const
{
	return (m_loadState == pa::ResourceLoadState::SuccessfullyLoaded);
}

bool pa::Resource::hasFailedToLoad() const
{
	return (m_loadState == pa::ResourceLoadState::FailedToLoad);
}

bool pa::Resource::hasFailedToUnload() const
{
	return (m_loadState == pa::ResourceLoadState::FailedToUnload);
}

std::chrono::system_clock::time_point pa::Resource::getLastLoadTime() const
{
	return m_lastLoadTime;
}

const char* pa::Resource::getPath() const
{
	return m_path;
}
