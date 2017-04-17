/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Graphics/OpenGL/TextureSubGL.h>

pa::TextureSubGL::TextureSubGL(pa::Graphics& graphics, pa::TextureGL& texture, int x1, int y1, int x2, int y2)
	: pa::TextureGL(graphics, texture.getPath())
	, m_texture(texture)
	, m_rect(x1, y1, x2, y2)
{
	pa::Vect2<int> size(x2 - x1, y2 - y1);
	setSize(size);
}

pa::TextureSubGL::~TextureSubGL()
{
}

bool pa::TextureSubGL::onLoad()
{
	if (m_texture.isLoaded())
	{
		setFormat(m_texture.getFormat());

		// Note that if the texture changes size the original rect will be invalidated if the rect has trasnformed in
		// the new texture
		setTextureCoords((float)m_rect.x1 / (float)m_texture.getSize().x,
						 (float)m_rect.y1 / (float)m_texture.getSize().y,
						 (float)m_rect.x2 / (float)m_texture.getSize().x,
						 (float)m_rect.y2 / (float)m_texture.getSize().y);

		setGLObject(m_texture.getGLObject());

		return true;
	}
	else
	{
		m_texture.load();
		return m_texture.isLoaded();
	}
}

bool pa::TextureSubGL::onUnload()
{
	return true;
}

void pa::TextureSubGL::onDependencyNotify(pa::Dependency* parent)
{
	if (&m_texture == parent)
	{
		if (m_texture.isLoaded())
		{
			load();
		}
		else
		{
			unload();
		}
	}
}
