/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Graphics/Render.h>
#include <Pineapple/Engine/Util/Macro.h>

pa::Render::Render(pa::RenderSystem& renderSystem, pa::Render::Type renderType, int priority)
	: m_renderSystem(renderSystem)
	, m_renderType(renderType)
	, m_priority(priority)
{
	switch (m_renderType)
	{
	case pa::Render::Type::Unordered: m_handle = m_renderSystem.registerUnordered(this); break;
	case pa::Render::Type::Ordered: m_handle = m_renderSystem.registerOrdered(this); break;
	default: break;
	}
}

pa::Render::~Render()
{
	switch (m_renderType)
	{
	case pa::Render::Type::Unordered: m_renderSystem.unregisterUnordered(m_handle); break;
	case pa::Render::Type::Ordered: m_renderSystem.unregisterOrdered(m_handle); break;
	default: break;
	}
}

int pa::Render::getPriority() const
{
	return m_priority;
}

void pa::Render::setPriority(int priority)
{
	m_priority = priority;

	if (pa::Render::Type::Ordered == m_renderType)
	{
		m_renderSystem.unregisterOrdered(m_handle);
		m_handle = m_renderSystem.registerOrdered(this);
	}
}