/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Graphics/OpenGL/ImageGL.h>
#include <Pineapple/Graphics/OpenGL/TextureFileGL.h>

pa::TextureFileGL::TextureFileGL(pa::Graphics& graphics, const char* path)
	: pa::TextureGL(graphics, path)
{
}

pa::TextureFileGL::~TextureFileGL()
{
}

bool pa::TextureFileGL::onLoad()
{
	pa::ImageGL image(getPath());

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
			setGLObject(id);

			pa::Log::info("Loaded Texture: {}", getPath());
		}
		else
		{
			pa::Log::info("Error, GL texture could not be generated for: {}", getPath());
		}
	}

	image.unload();

	return loaded;
}

bool pa::TextureFileGL::onUnload()
{
	GLuint id = getGLObject();

	if (glIsTexture(id))
	{
		glDeleteTextures(1, &id);
		setGLObject(0);
	}

	return true;
}