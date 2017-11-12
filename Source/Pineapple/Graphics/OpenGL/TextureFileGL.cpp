/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Graphics/OpenGL/ImageGL.h>
#include <Pineapple/Graphics/OpenGL/TextureFileGL.h>

pa::TextureFileGL::TextureFileGL(pa::Graphics& graphics, const pa::FilePath& path)
	: pa::TextureGL(graphics, path)
{
}

pa::TextureFileGL::~TextureFileGL()
{
}

bool pa::TextureFileGL::onLoad()
{
	pa::ImageGL image(*this);

	bool loaded = false;

	// Try to load the image
	if (image.load())
	{
		int id = image.createGLObject();

		if (glIsTexture(id) == GL_TRUE)
		{
			loaded = true;

			setSize(image.getSize());
			setFormat(image.getOriginalFormat());
			m_id = id;

			pa::Log::info("Loaded Texture: {}", getPath().asString());
		}
		else
		{
			pa::Log::info("Error, GL texture could not be generated for: {}", getPath().asString());
		}
	}

	image.unload();

	return loaded;
}

bool pa::TextureFileGL::onUnload()
{
	if (glIsTexture(m_id))
	{
		glDeleteTextures(1, &m_id);
		m_id = 0;
	}
	return true;
}