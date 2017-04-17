/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Platform/Dependency.h>

void pa::Dependency::notifyDependency(pa::Dependency* parent)
{
	onDependencyNotify(parent);

	notifyChildDependencies();
}

pa::Dependency::Handle pa::Dependency::addChildDependency(pa::Dependency* dependency)
{
	return m_dependencies.insert(m_dependencies.cend(), dependency);
}

void pa::Dependency::removeChildDependency(Handle& childNode)
{
	m_dependencies.erase(childNode);
}

void pa::Dependency::notifyChildDependencies()
{
	for (auto&& dependency : m_dependencies)
	{
		dependency->notifyDependency(this);
	}
}
