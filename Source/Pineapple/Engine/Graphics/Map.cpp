/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Graphics/Map.h>

pa::Map::Map(pa::RenderSystem& renderSystem, float x, float y, int w, int h, bool hWrap, bool vWrap, int priority,
			 pa::Render::Type render)
	: pa::Render(renderSystem, render, priority)
	, m_position(x, y)
	, m_scroll(0.f, 0.f)
	, m_size(w, h)
{
	if (hWrap)
	{
		m_flags.set(Flags::HWrap);
	}

	if (vWrap)
	{
		m_flags.set(Flags::VWrap);
	}
}

const pa::Vect2<int>& pa::Map::getSize() const
{
	return m_size;
}

bool pa::Map::getVWrap() const
{
	return m_flags.getBool(Flags::VWrap);
}

bool pa::Map::getHWrap() const
{
	return m_flags.getBool(Flags::HWrap);
}

void pa::Map::setVisible(bool visible)
{
	visible ? m_flags.clear(Flags::Invisible) : m_flags.set(Flags::Invisible);
}

bool pa::Map::getVisible() const
{
	return !m_flags.getBool(Flags::Invisible);
}

void pa::Map::setColour(const pa::Colour& colour)
{
	m_colour = colour;
}

pa::Colour& pa::Map::getColour()
{
	return m_colour;
}