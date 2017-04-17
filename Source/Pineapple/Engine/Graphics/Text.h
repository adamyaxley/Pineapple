/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Container/Vect2.h>
#include <Pineapple/Engine/Graphics/Sprite.h>

namespace pa
{
	class Text : public Sprite
	{
	public:
		Text(RenderSystem& renderSystem);
		virtual ~Text();

		void setText(const char* format, ...);
		const char* getText() const;

		void setOutline(int outline);
		int getOutline() const;

		void setOutlineColour(const Colour& colour);
		Colour& getOutlineColour();

	protected:
		virtual void onTextChange() = 0;

	private:
		char* m_text;
		int m_textSize;

		int m_outline;
		Colour m_outlineColour;
	};
}
