/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Graphics/OpenGL/IncludeGL.h>

namespace pa
{
	class TextureCoordsGL
	{
	public:
		TextureCoordsGL(float x1, float y1, float x2, float y2);
		~TextureCoordsGL();

		void set(float x1, float y1, float x2, float y2);

		const GLfloat* getPointer(bool hFlip, bool vFlip) const;

	private:
		GLfloat m_value[8];
		GLfloat m_valueHFlip[8];
		GLfloat m_valueVFlip[8];
		GLfloat m_valueHVFlip[8];
	};
}
