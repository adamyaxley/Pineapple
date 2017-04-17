/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Prefab/Asset/Asset.h>
#include <Pineapple/Engine/Prefab/Game/Entity.h>

pa::Entity::Entity(pa::World& world)
	: pa::Object(world)
{
}

void pa::Entity::updatePhysics(Time deltaTime)
{
	// Remember the last position to calculate displacement
	pa::Vect2<float> lastPosition = getPosition();

	// Step the particle
	stepMotion(deltaTime);

	// Set AABB properties
	getAABB().setPosition(lastPosition - getAABB().getSize() / 2);
	getAABB().setDisplacement(getPosition() - lastPosition);

#ifdef PA_DEBUG
	if (m_aabbDebug)
	{
		m_aabbDebug->setScale(getAABB().calculateSweptAABB().getSizeConst());
		m_aabbDebug->setPosition(getAABB().getPositionConst());
	}
#endif
}

void pa::Entity::updateSprite()
{
	// Update sprite
	m_sprite->setPosition(getPosition());
}

const pa::AABB& pa::Entity::getAABB() const
{
	return m_aabb;
}

pa::AABB& pa::Entity::getAABB()
{
	return m_aabb;
}

std::shared_ptr<pa::Sprite> pa::Entity::getSprite()
{
	return m_sprite;
}

const std::shared_ptr<pa::Sprite> pa::Entity::getSprite() const
{
	return m_sprite;
}

void pa::Entity::setSprite(std::shared_ptr<pa::Sprite> sprite)
{
	m_sprite = sprite;

	setAABBSizeFromSprite();
	updateSprite();
}

void pa::Entity::setAABBSizeFromSprite()
{
	pa::Vect2<float> size = m_sprite->getSize();
	size.scale(m_sprite->getScale());
	m_aabb.setSize(size);
}

#ifdef PA_DEBUG
void pa::Entity::enableDebugAABB()
{
	m_aabbDebug = pa::Asset::Texture::getPixelTexture()->createSprite();
	m_aabbDebug->setColour(pa::ColourSet::Red);
	m_aabbDebug->getColour().A = 0.5;
}

void pa::Entity::disableDebugAABB()
{
	m_aabbDebug.reset();
}
#endif

void pa::Entity::onStep(Time deltaTime)
{
	// default implementation
	updatePhysics(deltaTime);
	updateSprite();
}
