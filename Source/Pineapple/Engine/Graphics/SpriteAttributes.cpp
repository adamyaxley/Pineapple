/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Graphics/SpriteAttributes.h>

pa::SpriteAttributes::SpriteAttributes(const Vect2<int>& size)
	: m_position(0.f, 0.f)
	, m_origin(Vect2<float>(size) / 2)
	, m_scale(1.0f, 1.0f)
	, m_size(size)
	, m_rotation(0.f)
	, m_colour(pa::ColourSet::White)
{
}

const pa::Vect2<int>& pa::SpriteAttributes::getSize() const
{
	return m_size;
}

void pa::SpriteAttributes::setScale(float scale)
{
	m_scale.x = scale;
	m_scale.y = scale;
}

void pa::SpriteAttributes::setRotation(float radians)
{
	m_rotation = radians;
}

float pa::SpriteAttributes::getRotation() const
{
	return m_rotation;
}

void pa::SpriteAttributes::setColour(const pa::Colour& colour)
{
	m_colour = colour;
}

pa::Colour& pa::SpriteAttributes::getColour()
{
	return m_colour;
}

const pa::Colour& pa::SpriteAttributes::getColour() const
{
	return m_colour;
}

void pa::SpriteAttributes::setSize(const pa::Vect2<int>& size)
{
	m_size = size;
}