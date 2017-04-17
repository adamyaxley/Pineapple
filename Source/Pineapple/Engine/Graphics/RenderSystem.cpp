/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Graphics/Render.h>
#include <Pineapple/Engine/Graphics/RenderSystem.h>

#include <algorithm>

void pa::RenderSystem::renderUnordered()
{
	for (auto&& render : m_unorderedList)
	{
		render->render();
	}
}

void pa::RenderSystem::renderOrdered()
{
	for (auto&& render : m_orderedList)
	{
		render->render();
	}
}

pa::RenderSystem::Handle pa::RenderSystem::registerOrdered(pa::Render* renderable)
{
	// Find the first node which is greater than the current object
	auto upper =
		std::upper_bound(m_orderedList.cbegin(), m_orderedList.cend(), renderable,
						 [](const pa::Render* a, const pa::Render* b) { return a->getPriority() < b->getPriority(); });

	// Insert this new object before that node
	return m_orderedList.insert(upper, renderable);
}

void pa::RenderSystem::unregisterOrdered(const pa::RenderSystem::Handle handle)
{
	m_orderedList.erase(handle);
}

pa::RenderSystem::Handle pa::RenderSystem::registerUnordered(pa::Render* renderable)
{
	return m_unorderedList.insert(m_unorderedList.cend(), renderable);
}

void pa::RenderSystem::unregisterUnordered(const pa::RenderSystem::Handle handle)
{
	m_unorderedList.erase(handle);
}