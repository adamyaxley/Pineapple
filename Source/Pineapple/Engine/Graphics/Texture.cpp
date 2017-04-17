/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Graphics/Texture.h>
#include <Pineapple/Engine/Util/Macro.h>

pa::Texture::Texture(const char* path)
	: pa::Resource(path)
{
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
