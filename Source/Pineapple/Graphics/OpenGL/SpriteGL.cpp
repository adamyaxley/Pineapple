/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Container/Rect.h>
#include <Pineapple/Graphics/OpenGL/DrawGL.h>
#include <Pineapple/Graphics/OpenGL/IncludeGL.h>
#include <Pineapple/Graphics/OpenGL/SpriteGL.h>

pa::SpriteGL::SpriteGL(pa::Graphics& graphics, pa::TextureGL& texture)
	: pa::Sprite(graphics.getRenderSystem(), texture.getSize().x, texture.getSize().y,
				 (texture.getFormat() == pa::Texture::Format::RGBA ||
				  texture.getFormat() == pa::Texture::Format::LuminanceAlpha)
					 ? pa::Render::Type::Ordered
					 : pa::Render::Type::Unordered)
	, m_graphics(graphics)
	, m_texture(texture)
{
}

void pa::SpriteGL::render()
{
	if (getVisible() && m_texture.isLoaded())
	{
		// Enable 2d textures
		glEnable(GL_TEXTURE_2D);

		// Use the texture
		GLint activeObject;
		glGetIntegerv(GL_TEXTURE_BINDING_2D, &activeObject);

		if (activeObject != m_texture.getGLObject())
		{
			glBindTexture(GL_TEXTURE_2D, m_texture.getGLObject());
		}

		// Load a new drawing matrix
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		// Alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		pa::DrawGL::transform2d(m_graphics.getSpriteView(), getOrigin(), getPosition(), getPriority(), getScale(),
								getRotation());

		// Set the drawing colour
		glColor4f((GLfloat)getColour().R, (GLfloat)getColour().G, (GLfloat)getColour().B, (GLfloat)getColour().A);

		// Scale the quad
		glScalef((GLfloat)getSize().x, (GLfloat)getSize().y, 1.f);

		// Draw quad
		pa::DrawGL::drawQuad(getHFlip(), getVFlip(), m_texture.getTextureCoords());

		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		// Refresh the drawing matrix
		glPopMatrix();

		// Disable 2d textures
		glDisable(GL_TEXTURE_2D);

		PA_GL_CHECK_ERROR();
	}
}
