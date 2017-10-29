/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Graphics/Text.h>
#include <Pineapple/Engine/Platform/Memory.h>
#include <Pineapple/Engine/Util/Macro.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

pa::Text::Text(pa::RenderSystem& renderSystem)
	: pa::Render(renderSystem, pa::Render::Type::Ordered, 1)
	, pa::SpriteAttributes({0, 0})
	, m_text(nullptr)
	, m_textSize(0)
	, m_outline(0)
	, m_outlineColour(pa::ColourSet::Black)
	, m_visible(true)
{
}

pa::Text::~Text()
{
	if (m_text != nullptr)
	{
		pa::Memory::deallocate(m_text);
	}
}

void pa::Text::setText(const char* format, ...)
{
	if (format != nullptr)
	{
		va_list va_count;
		va_start(va_count, format);
#ifdef _MSC_VER
		int textSize = _vscprintf(format, va_count) + 1;
#else
		int textSize = vsnprintf(nullptr, 0, format, va_count) + 1;
#endif
		va_end(va_count);

		if (m_textSize < textSize)
		{
			if (m_text != NULL)
			{
				m_text = (char*)pa::Memory::reallocate(m_text, textSize);
			}
			else
			{
				m_text = (char*)pa::Memory::allocate(textSize);
			}
		}

		m_textSize = textSize;

		va_list va_print;
		va_start(va_print, format);
#ifdef _MSC_VER
		vsprintf_s(m_text, m_textSize, format, va_print);
#else
		vsprintf(m_text, format, va_print);
#endif
		va_end(va_print);

		onTextChange();
	}
}

const char* pa::Text::getText() const
{
	return m_text;
}

void pa::Text::setOutline(int outline)
{
	m_outline = outline;
}

int pa::Text::getOutline() const
{
	return m_outline;
}

void pa::Text::setOutlineColour(const pa::Colour& colour)
{
	m_outlineColour = colour;
}

pa::Colour& pa::Text::getOutlineColour()
{
	return m_outlineColour;
}

void pa::Text::setVisible(bool visible)
{
	m_visible = visible;
}

bool pa::Text::getVisible() const
{
	return m_visible;
}