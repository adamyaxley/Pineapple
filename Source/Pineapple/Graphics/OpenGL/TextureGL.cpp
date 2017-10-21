/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Graphics/OpenGL/DrawGL.h>
#include <Pineapple/Graphics/OpenGL/TextureGL.h>
#include <Pineapple/Graphics/OpenGL/TextureSubGL.h>

pa::TextureGL::TextureGL(pa::Graphics& graphics, const char* path)
	: pa::Texture(path, graphics.getRenderSystem())
	, m_graphics(graphics)
	, m_id(0)
	, m_textureCoords(0.f, 0.f, 1.f, 1.f)
{
}

pa::TextureGL::~TextureGL()
{
}

std::shared_ptr<pa::Texture> pa::TextureGL::createTexture(int x, int y, int width, int height)
{
	auto texture = std::make_shared<pa::TextureSubGL>(m_graphics, *this, x, y, x + width, y + height);
	auto ptr = texture.get();
	addChildDependency(ptr);
	m_subTextures.push_back(texture);
	return texture;
}

GLuint pa::TextureGL::getGLObject() const
{
	PA_ASSERTF(isLoaded(), "Texture is not loaded");
	return m_id;
}

const pa::TextureCoordsGL& pa::TextureGL::getTextureCoords() const
{
	return m_textureCoords;
}

void pa::TextureGL::setGLObject(GLuint id)
{
	m_id = id;
}

void pa::TextureGL::setTextureCoords(float x1, float y1, float x2, float y2)
{
	m_textureCoords.set(x1, y1, x2, y2);
}

void pa::TextureGL::render(const pa::Sprite& sprite)
{
	if (sprite.getVisible() && isLoaded())
	{
		// Enable 2d textures
		glEnable(GL_TEXTURE_2D);

		// Use the texture
		GLint activeObject;
		glGetIntegerv(GL_TEXTURE_BINDING_2D, &activeObject);

		if (activeObject != getGLObject())
		{
			glBindTexture(GL_TEXTURE_2D, getGLObject());
		}

		// Load a new drawing matrix
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		// Alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		pa::DrawGL::transform2d(m_graphics.getSpriteView(), sprite.getOriginConst(), sprite.getPositionConst(), sprite.getPriority(), sprite.getScaleConst(),
			sprite.getRotation());

		// Set the drawing colour
		const auto& colour = sprite.getColour();
		glColor4f((GLfloat)colour.R, (GLfloat)colour.G, (GLfloat)colour.B, (GLfloat)colour.A);

		// Scale the quad
		glScalef((GLfloat)getSize().x, (GLfloat)getSize().y, 1.f);

		// Draw quad
		pa::DrawGL::drawQuad(sprite.getHFlip(), sprite.getVFlip(), getTextureCoords());

		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		// Refresh the drawing matrix
		glPopMatrix();

		// Disable 2d textures
		glDisable(GL_TEXTURE_2D);

		PA_GL_CHECK_ERROR();
	}
}
