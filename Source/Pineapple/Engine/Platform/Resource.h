/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Platform/Dependency.h>
#include <Pineapple/Engine/Platform/FileSystem.h>
#include <chrono>
#include <memory>

namespace pa
{
	enum class ResourceLoadState
	{
		SuccessfullyLoaded,
		SuccessfullyUnloaded,
		FailedToLoad,
		FailedToUnload
	};

	// Defines a resource that is used in the system
	class Resource : public Dependency
	{
		friend struct std::default_delete<Resource>;

	public:
		Resource(const FilePath& path);

		// Make sure that the resource is loaded, and add a reference
		void load();

		// Release our reference of the resource
		void unload();

		// Reload the resource
		void reload();

		// Check if this resource is loaded in memory
		bool isLoaded() const;

		bool hasFailedToLoad() const;

		bool hasFailedToUnload() const;

		std::chrono::system_clock::time_point getLastLoadTime() const;

		// Get memory usage
		// int getMemory();

		const FilePath& getPath() const;

	protected:
		// Load this resource completely
		virtual bool onLoad() = 0;

		// Release all memory for this resource
		virtual bool onUnload() = 0;

		// Protected so only ResourceManager can delete it
		virtual ~Resource();

	private:
		ResourceLoadState m_loadState;

		// The last time load() was called
		std::chrono::system_clock::time_point m_lastLoadTime;

		// The path to this resource
		FilePath m_path;
	};
}
