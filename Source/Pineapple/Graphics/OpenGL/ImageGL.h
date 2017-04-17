/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Container/Vect2.h>
#include <Pineapple/Engine/Graphics/Texture.h>
#include <Pineapple/Graphics/OpenGL/IncludeGL.h>

namespace pa
{
	class ImageGL
	{
	public:
		ImageGL(const char* path);
		~ImageGL()
		{
		}

		// Load
		bool load();

		// Upload texture data to GPU and get OpenGL object
		GLuint createGLObject();

		// Clean up
		void unload();

		// Size
		const Vect2<int>& getSize() const;

		// Format
		Texture::Format getOriginalFormat() const;

	private:
		// Path to physical resource
		const char* m_path;

		// Size of image, in pixels
		Vect2<int> m_size;

		// Pointer to texture data
		unsigned char* m_data;

		// Format of original file
		Texture::Format m_format;
	};
}
