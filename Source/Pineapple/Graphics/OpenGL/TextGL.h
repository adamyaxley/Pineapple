/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Graphics/Text.h>
#include <Pineapple/Graphics/OpenGL/FontGL.h>

namespace pa
{
	class TextGL : public Text
	{
	public:
		TextGL(Graphics& graphics, FontGL& font);
		~TextGL();

		virtual void render() override;

	protected:
		virtual void onTextChange() override;

	private:
		const Graphics& m_graphics;
		FontGL& m_font;
	};
}
