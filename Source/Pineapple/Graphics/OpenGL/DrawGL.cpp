/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Graphics/OpenGL/DrawGL.h>
#include <Pineapple/Graphics/OpenGL/IncludeGL.h>
#include <Pineapple/Graphics/OpenGL/TextureCoordsGL.h>

namespace
{
	GLfloat g_vertexQuad[8] = {0.f, 1.f, 1.f, 1.f, 0.f, 0.f, 1.f, 0.f};
}

void pa::DrawGL::drawQuad(bool hFlip, bool vFlip, const pa::TextureCoordsGL& textureCoords)
{
	// Flip
	const GLfloat* texCoordArray = static_cast<const GLfloat*>(textureCoords.getPointer(hFlip, vFlip));

	// Enable arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Set arrays
	glVertexPointer(2, GL_FLOAT, 0, g_vertexQuad);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoordArray);

	// Draw
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	// Disable arrays
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void pa::DrawGL::transform2d(const pa::Vect2<float>& view, const pa::Vect2<float>& origin, const pa::Vect2<float>& position,
							 int depth, const pa::Vect2<float>& scale, float rotation)
{
	// Translate view
	glTranslatef(-(GLfloat)view.x, -(GLfloat)view.y, 0.f);

	// Translate to position
	glTranslatef((GLfloat)position.x, (GLfloat)position.y, (GLfloat)depth);

	// Rotate
	glRotatef((GLfloat)rotation * 180.f / PA_PI, 0.0f, 0.0f, 1.0f);

	// Scale
	glScalef(scale.x, scale.y, 1.f);

	// Translate origin
	glTranslatef(-(GLfloat)origin.x, -(GLfloat)origin.y, 0.f);
}

double pa::DrawGL::getTexelBias()
{
	return (1.0 / 4096.0);
}
