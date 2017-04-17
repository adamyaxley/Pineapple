/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Platform/Memory.h>
#include <Pineapple/Engine/Platform/Platform.h>
#include <Pineapple/Graphics/OpenGL/UtilGL.h>
#include <Pineapple/Graphics/OpenGL/VertexBuffer2DGL.h>

#define PA_VERT_DIMENSION 2

pa::VertexBuffer2DGL::VertexBuffer2DGL()
	: m_vertexBuffer(nullptr)
	, m_textureCoordBuffer(nullptr)
	, m_vertexBufferId(0)
	, m_textureCoordBufferId(0)
	, m_mode(GL_TRIANGLES)
	, m_size(0)
	, m_num(0)
{
}

pa::VertexBuffer2DGL::~VertexBuffer2DGL()
{
	clean();
}

void pa::VertexBuffer2DGL::createBuffers(const int vertexCount)
{
	m_vertexBuffer = (GLfloat*)pa::Memory::allocate(vertexCount * PA_VERT_DIMENSION * sizeof(GLfloat));
	m_textureCoordBuffer = (GLfloat*)pa::Memory::allocate(vertexCount * 2 * sizeof(GLfloat));

	m_size = vertexCount;
}

void pa::VertexBuffer2DGL::clean()
{
	m_num = 0;
	m_size = 0;
	m_mode = GL_TRIANGLES;

	if (m_vertexBuffer != nullptr)
	{
		pa::Memory::deallocate(m_vertexBuffer);
		m_vertexBuffer = nullptr;
	}

	if (m_textureCoordBuffer != nullptr)
	{
		pa::Memory::deallocate(m_textureCoordBuffer);
		m_textureCoordBuffer = nullptr;
	}

	if (glIsBuffer(m_vertexBufferId))
	{
		glDeleteBuffers(1, &m_vertexBufferId);
		PA_GL_CHECK_ERROR();
		m_vertexBufferId = 0;
	}
	PA_ASSERTF(m_vertexBufferId == 0, "VertexBufferId is not 0");

	if (glIsBuffer(m_textureCoordBufferId))
	{
		glDeleteBuffers(1, &m_textureCoordBufferId);
		PA_GL_CHECK_ERROR();
		m_textureCoordBufferId = 0;
	}
	PA_ASSERTF(m_vertexBufferId == 0, "TextureBufferId is not 0");
}

void pa::VertexBuffer2DGL::setMode(GLuint mode)
{
	m_mode = mode;
}

void pa::VertexBuffer2DGL::addVertex(GLfloat x, GLfloat y, GLfloat u, GLfloat v)
{
	PA_ASSERTF(m_num < m_size, "Vertex limit of {} reached", m_size);

	GLfloat* vertex = &m_vertexBuffer[m_num * PA_VERT_DIMENSION];
	vertex[0] = x;
	vertex[1] = y;
#if (PA_VERT_DIMENSION > 2)
	vertex[2] = 0.f;
#endif

	GLfloat* textureCoord = &m_textureCoordBuffer[m_num * 2];
	textureCoord[0] = u;
	textureCoord[1] = v;

	m_num++;
}

void pa::VertexBuffer2DGL::upload()
{
	glGenBuffers(1, &m_vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, m_num * PA_VERT_DIMENSION * sizeof(GLfloat), &m_vertexBuffer[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_textureCoordBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_textureCoordBufferId);
	glBufferData(GL_ARRAY_BUFFER, m_num * 2 * sizeof(GLfloat), &m_textureCoordBuffer[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Free old memory
	pa::Memory::deallocate(m_vertexBuffer);
	pa::Memory::deallocate(m_textureCoordBuffer);
	m_vertexBuffer = nullptr;
	m_textureCoordBuffer = nullptr;
}

void pa::VertexBuffer2DGL::draw() const
{
	// Establish array contains vertices (not normals, colours, texture coords etc)
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	// Make the new VBO active. Repeat here incase changed since initialisation
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glVertexPointer(PA_VERT_DIMENSION, GL_FLOAT, PA_VERT_DIMENSION * sizeof(GLfloat), NULL);
	glBindBuffer(GL_ARRAY_BUFFER, m_textureCoordBufferId);
	glTexCoordPointer(2, GL_FLOAT, 2 * sizeof(GLfloat), NULL);

	glDrawArrays(m_mode, 0, m_num);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
