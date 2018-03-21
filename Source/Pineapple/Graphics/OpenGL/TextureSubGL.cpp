/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Graphics/OpenGL/TextureSubGL.h>

pa::TextureSubGL::TextureSubGL(pa::Graphics& graphics, pa::TextureGL& texture, const Vect2<int>& from, const Vect2<int>& to)
	: pa::TextureGL(graphics, texture.getPath())
	, m_texture(texture)
	, m_rect(from.x, from.y, to.x, to.y)
{
	setSize(to - from);

	if (m_texture.isLoaded())
	{
		load();
	}
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
		m_textureCoords.set((float)m_rect.x1 / (float)m_texture.getSize().x,
						 (float)m_rect.y1 / (float)m_texture.getSize().y,
						 (float)m_rect.x2 / (float)m_texture.getSize().x,
						 (float)m_rect.y2 / (float)m_texture.getSize().y);

		m_id = m_texture.getGLObject();

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
