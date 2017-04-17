/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Graphics/OpenGL/SpriteGL.h>
#include <Pineapple/Graphics/OpenGL/TextureGL.h>
#include <Pineapple/Graphics/OpenGL/TextureSubGL.h>

pa::TextureGL::TextureGL(pa::Graphics& graphics, const char* path)
	: pa::Texture(path)
	, m_graphics(graphics)
	, m_id(0)
	, m_textureCoords(0.f, 0.f, 1.f, 1.f)
{
}

pa::TextureGL::~TextureGL()
{
}

std::unique_ptr<pa::Sprite> pa::TextureGL::createSprite()
{
	PA_ASSERTF(isLoaded(), "Texture is not loaded");
	return std::make_unique<pa::SpriteGL>(m_graphics, *this);
}

pa::Texture* pa::TextureGL::createTexture(int x, int y, int width, int height)
{
	auto texture = std::make_unique<pa::TextureSubGL>(m_graphics, *this, x, y, x + width, y + height);
	auto ptr = texture.get();
	addChildDependency(ptr);
	m_subTextures.push_back(std::move(texture));
	return ptr;
}

GLuint pa::TextureGL::getGLObject() const
{
	PA_ASSERTF(isLoaded(), "Texture is not loaded");
	return m_id;
}

const pa::TextureCoordsGL& pa::TextureGL::getTextureCoords() const
{
	return m_textureCoords;
}

void pa::TextureGL::setGLObject(GLuint id)
{
	m_id = id;
}

void pa::TextureGL::setTextureCoords(float x1, float y1, float x2, float y2)
{
	m_textureCoords.set(x1, y1, x2, y2);
}
