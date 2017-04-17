/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Platform/ResourceState.h>
#include <memory>
#include <vector>

namespace pa
{
	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();

		void add(std::shared_ptr<Resource> resource);
		void addPlainDependency(std::shared_ptr<Dependency> dependency);
		void unloadAll();
		void loadAll();

		void saveState();
		void restoreState();

		void reloadModified();

		int getCount() const;

		// int getMemoryUsage();
		// void printResources();
	private:
		std::vector<ResourceState> m_resourceStates;
		std::vector<std::shared_ptr<Dependency>> m_plainDependencies;
	};
}
