/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Graphics/RenderSystem.h>
#include <Pineapple/Engine/Graphics/Sprite.h>
#include <Pineapple/Engine/Graphics/Texture.h>
#include <Pineapple/Engine/Util/Macro.h>
#include <memory>

pa::Texture::Texture(const char* path, pa::RenderSystem& renderSystem)
	: pa::Resource(path)
	, m_renderSystem(renderSystem)
{
}

std::unique_ptr<pa::Sprite> pa::Texture::createSprite()
{
	std::vector<std::shared_ptr<pa::Texture>> frames{shared_from_this()};
	return std::make_unique<pa::Sprite>(m_renderSystem, frames, 0);
}

const pa::Vect2<int>& pa::Texture::getSize() const
{
	PA_ASSERTF(isLoaded(), "Texture is not loaded");
	return m_size;
}

pa::Texture::Format pa::Texture::getFormat() const
{
	PA_ASSERTF(isLoaded(), "Texture is not loaded");
	return m_format;
}

void pa::Texture::setSize(const pa::Vect2<int>& size)
{
	m_size = size;
}

void pa::Texture::setFormat(pa::Texture::Format format)
{
	m_format = format;
}
