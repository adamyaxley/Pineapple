/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Platform/Memory.h>
#include <Pineapple/Engine/Platform/Platform.h>
#include <Pineapple/Graphics/OpenGL/ImageGL.h>

#include <stb_image.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

pa::ImageGL::ImageGL(const pa::Resource& resource)
	: m_size(0, 0)
	, m_data(nullptr)
	, m_resource(resource)
{
}

bool pa::ImageGL::load()
{
	pa::FileBuffer buffer;
	auto result = m_resource.getPath().read(buffer);
	if (result != pa::FileResult::Success)
	{
		pa::Log::info("{}: {}", pa::FileSystem::getResultString(result), m_resource.getPath().asString());
		return false;
	}

	// Use stb_image.c to load the file
	int comp;
	m_data = stbi_load_from_memory(buffer.getBuffer().get(), (int)buffer.getSize(), &m_size.x, &m_size.y, &comp, 4);

	if (m_data == nullptr)
	{
		pa::Log::info("STBI error: {}", stbi_failure_reason());
		return false;
	}

	// Get original file format
	switch (comp)
	{
	case 1: m_format = pa::Texture::Format::Luminance; break;
	case 2: m_format = pa::Texture::Format::LuminanceAlpha; break;
	case 3: m_format = pa::Texture::Format::RGB; break;
	case 4: m_format = pa::Texture::Format::RGBA; break;
	}

	return true;
}

GLuint pa::ImageGL::createGLObject()
{
	GLuint texture = 0;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Need to put texparameters before teximage2d in linux...
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	unsigned int format = GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0, format, m_size.x, m_size.y, 0, format, GL_UNSIGNED_BYTE, (GLvoid*)m_data);
	PA_GL_CHECK_ERROR();

	return texture;
}

void pa::ImageGL::unload()
{
	if (m_data != nullptr)
	{
		stbi_image_free(m_data);
	}
}

const pa::Vect2<int>& pa::ImageGL::getSize() const
{
	return m_size;
}

pa::Texture::Format pa::ImageGL::getOriginalFormat() const
{
	return m_format;
}