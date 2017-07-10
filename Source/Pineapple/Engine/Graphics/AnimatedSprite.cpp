/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Graphics/AnimatedSprite.h>

#include <Pineapple/Engine/Graphics/Texture.h>
#include <Pineapple/Engine/Platform/Platform.h>
#include <Pineapple/Engine/Util/Macro.h>

#include <stdarg.h>

unsigned int pa::AnimatedSprite::getFrame()
{
	return m_current;
}

void pa::AnimatedSprite::setFrame(unsigned int frame)
{
	PA_ASSERTF(frame >= 0 && frame < m_frameList.size(), "Frame must be within range");
	m_frame = frame;
}

unsigned int pa::AnimatedSprite::getFrameCount()
{
	return m_frameList.size();
}

void pa::AnimatedSprite::hideAll()
{
	for (auto&& frame : m_frameList)
	{
		frame->setVisible(false);
	}
}

pa::AnimatedSprite::AnimatedSprite(pa::RenderSystem& renderSystem, bool recurring)
	: pa::Sprite(renderSystem, 0, 0, pa::Render::Type::Unordered)
	, m_frame(0)
	, m_current(0)
{
}

pa::AnimatedSprite::~AnimatedSprite()
{
}

void pa::AnimatedSprite::render()
{
	if (m_current != m_frame)
	{
		m_frameList[m_current]->setVisible(false);
		m_frameList[m_frame]->setVisible(getVisible());
		m_current = m_frame;

		// Update size?
		setSize(m_frameList[m_frame]->getSize());
	}

	pa::Sprite* m_sprite = m_frameList[m_frame].get();
	m_sprite->setPosition(getPosition());
	m_sprite->setScale(getScale());
	m_sprite->setRotation(getRotation());
	m_sprite->setHFlip(getHFlip());
	m_sprite->setVFlip(getVFlip());
	m_sprite->setColour(getColour());
	m_sprite->setOrigin(getOriginConst());
	m_sprite->setPriority(getPriority());
}
