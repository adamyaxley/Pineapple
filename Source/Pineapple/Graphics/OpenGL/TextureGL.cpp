/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Graphics/OpenGL/DrawGL.h>
#include <Pineapple/Graphics/OpenGL/TextureGL.h>
#include <Pineapple/Graphics/OpenGL/TextureSubGL.h>

pa::TextureGL::TextureGL(pa::Graphics& graphics, const pa::FilePath& path)
	: pa::Texture(path, graphics.getRenderSystem())
	, m_graphics(graphics)
	, m_id(0)
	, m_textureCoords(0.f, 0.f, 1.f, 1.f)
{
}

pa::TextureGL::~TextureGL()
{
}

std::shared_ptr<pa::Texture> pa::TextureGL::createTexture(const Vect2<int>& pos, const Vect2<int>& size)
{
	auto texture = std::make_shared<pa::TextureSubGL>(m_graphics, *this, pos, pos + size);
	auto ptr = texture.get();
	addChildDependency(ptr);
	m_subTextures.push_back(texture);
	return texture;
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

		if (activeObject != m_id)
		{
			glBindTexture(GL_TEXTURE_2D, m_id);
		}

		// Load a new drawing matrix
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		// Alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		pa::DrawGL::transform2d(m_graphics.getSpriteView(), sprite.getOriginConst(), sprite.getPositionConst(),
								sprite.getPriority(), sprite.getScaleConst(), sprite.getRotation());

		// Set the drawing colour
		const auto& colour = sprite.getColour();
		glColor4f((GLfloat)colour.R, (GLfloat)colour.G, (GLfloat)colour.B, (GLfloat)colour.A);

		// Scale the quad
		glScalef((GLfloat)getSize().x, (GLfloat)getSize().y, 1.f);

		// Draw quad
		pa::DrawGL::drawQuad(sprite.getHFlip(), sprite.getVFlip(), m_textureCoords);

		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		// Refresh the drawing matrix
		glPopMatrix();

		// Disable 2d textures
		glDisable(GL_TEXTURE_2D);

		PA_GL_CHECK_ERROR();
	}
}

GLuint pa::TextureGL::getGLObject() const
{
	return m_id;
}