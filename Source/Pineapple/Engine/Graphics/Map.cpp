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
		m_flags.set(Flags::PA_MAP_HWRAP);
	}

	if (vWrap)
	{
		m_flags.set(Flags::PA_MAP_VWRAP);
	}
}

const pa::Vect2<int>& pa::Map::getSize() const
{
	return m_size;
}

bool pa::Map::getVWrap() const
{
	return m_flags.getBool(Flags::PA_MAP_VWRAP);
}

bool pa::Map::getHWrap() const
{
	return m_flags.getBool(Flags::PA_MAP_HWRAP);
}

void pa::Map::setColour(const pa::Colour& colour)
{
	m_colour = colour;
}

pa::Colour& pa::Map::getColour()
{
	return m_colour;
}