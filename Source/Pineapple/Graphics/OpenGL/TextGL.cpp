/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Util/Macro.h>
#include <Pineapple/Graphics/OpenGL/DrawGL.h>
#include <Pineapple/Graphics/OpenGL/IncludeGL.h>
#include <Pineapple/Graphics/OpenGL/TextGL.h>
#include <Pineapple/Graphics/OpenGL/UtilGL.h>
#include <fontstash.h>
#ifdef PA_OPENGLES1
#	include <glfontstash.h>
#	define FONS_RGBA glfonsRGBA
#else
#	include <gl3fontstash.h>
#	define FONS_RGBA gl3fonsRGBA
#endif
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

pa::TextGL::TextGL(pa::Graphics& graphics, pa::FontGL& font)
	: pa::Text(graphics.getRenderSystem())
	, m_graphics(graphics)
	, m_font(font)
{
}

pa::TextGL::~TextGL()
{
}

void pa::TextGL::render()
{
	if ((getText() != nullptr) && getVisible() && m_font.isLoaded())
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		unsigned int colour = FONS_RGBA((unsigned char)(getColour().R * 255), (unsigned char)(getColour().G * 255),
										  (unsigned char)(getColour().B * 255), (unsigned char)(getColour().A * 255));
		unsigned int outlineColour =
			FONS_RGBA((unsigned char)(getOutlineColour().R * 255), (unsigned char)(getOutlineColour().G * 255),
						(unsigned char)(getOutlineColour().B * 255), (unsigned char)(getOutlineColour().A * 255));

		auto fs = m_font.getFonsContext();

		fonsClearState(fs);
		fonsSetFont(fs, m_font.getFonsFont());
		fonsSetSize(fs, (float)m_font.getSize());
		fonsSetAlign(fs, FONS_ALIGN_TOP);

#ifndef PA_OPENGLES1
		// Set the projection matrix
		glm::mat4 proj =
			glm::translate(glm::mat4(1.f), glm::vec3(-1.f, 1.f, -1.f)) *
			glm::scale(glm::mat4(1.f), glm::vec3(2.f / m_graphics.getSize().x, -2.f / m_graphics.getSize().y, 2.f));

		// Build the entire transform
		glm::mat4 transform = proj * glm::translate(glm::mat4(1.f), glm::vec3(getPosition().x - m_graphics.getTextView().x, getPosition().y - m_graphics.getTextView().y,
																			  0)) * // <todo> getPriority()))// *
							  glm::scale(glm::mat4(1.f), glm::vec3(getScale().x, getScale().y, 1.f)) *
							  glm::rotate(glm::mat4(1.f), getRotation(), glm::vec3(0.f, 0.f, 1.f)) *
							  glm::translate(glm::mat4(1.f), glm::vec3(-getOrigin().x, -getOrigin().y, 0));
#else
		const auto position = getPosition() - getOrigin();
#endif

		fonsSetColor(fs, outlineColour);

		gl3fonsDepth(fs, -((float)getPriority() - 1000.f) / 2000.f);

		// Outline <todo> do this in a shader
		for (int i = -getOutline(); i <= getOutline(); i++)
		{
			for (int j = -getOutline(); j <= getOutline(); j++)
			{
				if (0 == i && 0 == j)
				{
					continue;
				}

#ifndef PA_OPENGLES1
				glm::mat4 outlineTransform = glm::translate(transform, glm::vec3(i, j, 0.f));
				gl3fonsProjection(fs, glm::value_ptr(outlineTransform));
				fonsDrawText(fs, 0, 0, getText(), nullptr);
#else
				fonsDrawText(fs, position.x + i, position.y + j, getText(), nullptr);
#endif
			}
		}

		fonsSetColor(fs, colour);

#ifndef PA_OPENGLES1
		gl3fonsProjection(fs, glm::value_ptr(transform));
		fonsDrawText(fs, 0, 0, getText(), nullptr);
#else
		fonsDrawText(fs, position.x, position.y, getText(), nullptr);
#endif

		PA_GL_CHECK_ERROR();
	}
}

void pa::TextGL::onTextChange()
{
	PA_ASSERTF(m_font.isLoaded(), "Cannot change text in unloaded font");

	auto fs = m_font.getFonsContext();
	fonsClearState(fs);
	fonsSetFont(fs, m_font.getFonsFont());
	fonsSetSize(fs, (float)m_font.getSize());

	float bounds[4];
	fonsTextBounds(fs, 0, 0, getText(), nullptr, bounds);
	pa::Vect2<int> size(static_cast<int>(bounds[2] - bounds[0]), static_cast<int>(bounds[3] - bounds[1]));
	setSize(size);
}
