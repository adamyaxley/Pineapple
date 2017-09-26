/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Container/Bitfield.h>
#include <Pineapple/Engine/Container/Vect2.h>
#include <Pineapple/Engine/Graphics/Colour.h>
#include <Pineapple/Engine/Graphics/Render.h>
#include <Pineapple/Engine/Util/Format.h>

namespace pa
{
	class Sprite : public Render
	{
	public:
		Sprite(RenderSystem& renderSystem, int width, int height, Render::Type renderType, int depth = 0);
		virtual ~Sprite()
		{
		}

		// Attributes
		const Vect2<int>& getSize() const;

		PA_FORMAT_VECTOR_REAL(Position, m_position)
		PA_FORMAT_VECTOR_REAL(Origin, m_origin)
		PA_FORMAT_VECTOR_REAL(Scale, m_scale)

		void setScale(float scale);

		void setRotation(float radians);
		float getRotation() const;

		// Flags
		void setHFlip(bool hFlip);
		bool getHFlip() const;

		void setVFlip(bool vFlip);
		bool getVFlip() const;

		void setVisible(bool visible);
		bool getVisible() const;

		void setColour(const Colour& colour);
		Colour& getColour();

		// Pin this sprite on another sprite with the offset
		void pin(const Sprite* sprite, Vect2<float>& offset);

	protected:
		// Only derived classes can modify the sprites size directly
		void setSize(Vect2<int>& size);
		void setSize(const Vect2<int>& size);

	private:
		enum class Flags
		{
			HFlip,
			VFlip,
			Visible,
			is_enum_bitfield
		};

		// Attributes
		Vect2<int> m_size;
		float m_rotation; // radians clockwise

		// Flags
		Bitfield<Flags> m_flags;

		// Colour
		Colour m_colour;
	};
}
