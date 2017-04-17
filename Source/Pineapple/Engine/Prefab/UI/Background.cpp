/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Graphics/Graphics.h>
#include <Pineapple/Engine/Prefab/Asset/Asset.h>
#include <Pineapple/Engine/Prefab/UI/Background.h>

pa::Background::Background(pa::World& world, int priority)
	: pa::Object(world)
	, m_sprite(nullptr)
{
	m_sprite = pa::Asset::Texture::getPixelTexture()->createSprite();
	m_sprite->setPriority(priority);
	m_sprite->getColour().A = 0;
	m_sprite->setOrigin(0.5f, 0.5f);
	m_sprite->setPosition(getWorld().getPlatform()->getGraphics()->getSpriteView() +
						  getWorld().getPlatform()->getGraphics()->getSize() / 2);
	m_sprite->setScale(getWorld().getPlatform()->getGraphics()->getSize() * 2);
}

void pa::Background::onStep(Time deltaTime)
{
	m_sprite->setPosition(getWorld().getPlatform()->getGraphics()->getSpriteView() +
						  getWorld().getPlatform()->getGraphics()->getSize() / 2);
}

void pa::Background::setColour(const pa::Colour& colour)
{
	m_sprite->setColour(colour);
}

pa::Colour& pa::Background::getColour()
{
	return m_sprite->getColour();
}
