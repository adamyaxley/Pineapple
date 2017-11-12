/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Graphics/Font.h>
#include <Pineapple/Engine/Graphics/Graphics.h>
#include <Pineapple/Graphics/OpenGL/IncludeGL.h>

struct FONScontext;

namespace pa
{
	class FontGL : public Font
	{
	public:
		FontGL(Graphics& graphics, FONScontext* fonsContext, const FilePath& path);
		~FontGL();

		virtual bool onLoad() override;
		virtual bool onUnload() override;

		virtual std::unique_ptr<Text> createText() override;

		virtual void setSize(unsigned int size) override;

		virtual unsigned int getSize() override;

		int getFonsFont();

		FONScontext* getFonsContext();

	private:
		Graphics& m_graphics;

		GLuint m_texture;

		std::unique_ptr<unsigned char[]> m_buffer;

		unsigned int m_faceSize;

		FONScontext* m_fonsContext;

		int m_fonsFont;
	};
}
