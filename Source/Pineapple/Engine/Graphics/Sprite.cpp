/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Graphics/Sprite.h>
#include <Pineapple/Engine/Util/Macro.h>

pa::Sprite::Sprite(pa::RenderSystem& renderSystem, int width, int height, pa::Render::Type renderType, int depth)
	: pa::Render(renderSystem, renderType, depth)
	, m_position(0.f, 0.f)
	, m_origin((float)(width / 2), (float)(height / 2))
	, m_scale(1.0f, 1.0f)
	, m_size(width, height)
	, m_rotation(0.f)
	, m_colour(pa::ColourSet::White)
{
	setVisible(true);
}

const pa::Vect2<int>& pa::Sprite::getSize() const
{
	return m_size;
}

void pa::Sprite::setScale(float scale)
{
	m_scale.x = scale;
	m_scale.y = scale;
}

void pa::Sprite::setRotation(float radians)
{
	m_rotation = radians;
}

float pa::Sprite::getRotation() const
{
	return m_rotation;
}

void pa::Sprite::setHFlip(bool hFlip)
{
	hFlip ? m_flags.set(Flags::HFlip) : m_flags.clear(Flags::HFlip);
}

bool pa::Sprite::getHFlip() const
{
	return m_flags.getBool(Flags::HFlip);
}

void pa::Sprite::setVFlip(bool vFlip)
{
	vFlip ? m_flags.set(Flags::VFlip) : m_flags.clear(Flags::VFlip);
}

bool pa::Sprite::getVFlip() const
{
	return m_flags.getBool(Flags::VFlip);
}

void pa::Sprite::setVisible(bool visible)
{
	visible ? m_flags.set(Flags::Visible) : m_flags.clear(Flags::Visible);
}

bool pa::Sprite::getVisible() const
{
	return m_flags.getBool(Flags::Visible);
}

void pa::Sprite::setSize(pa::Vect2<int>& size)
{
	m_size = size;
}

void pa::Sprite::setSize(const pa::Vect2<int>& size)
{
	m_size = size;
}

void pa::Sprite::setColour(const pa::Colour& colour)
{
	m_colour = colour;
}

pa::Colour& pa::Sprite::getColour()
{
	return m_colour;
}

void pa::Sprite::pin(const pa::Sprite* sprite, pa::Vect2<float>& offset)
{
	offset.scale(sprite->getScaleConst());
	offset.rotate(sprite->getRotation());
	offset += sprite->getPositionConst();
	setPosition(offset);
}
