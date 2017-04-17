/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once
#include <Pineapple/Graphics/OpenGL/IncludeGL.h>

namespace pa
{
	class VertexBuffer2DGL
	{
	public:
		VertexBuffer2DGL();
		~VertexBuffer2DGL();

		void createBuffers(const int vertexCount);
		void clean();

		void setMode(GLuint mode);
		void addVertex(GLfloat x, GLfloat y, GLfloat u, GLfloat v);

		void upload();
		void draw() const;

	private:
		GLfloat* m_vertexBuffer;
		GLfloat* m_textureCoordBuffer;

		GLuint m_vertexBufferId;
		GLuint m_textureCoordBufferId;

		GLuint m_mode;
		int m_size;
		int m_num;
	};
}
