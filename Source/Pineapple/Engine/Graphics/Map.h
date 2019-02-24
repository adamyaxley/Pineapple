/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Container/Bitfield.h>
#include <Pineapple/Engine/Container/Vect2.h>
#include <Pineapple/Engine/Graphics/Colour.h>
#include <Pineapple/Engine/Graphics/Render.h>
#include <Pineapple/Engine/Platform/Dependency.h>
#include <Pineapple/Engine/Util/Format.h>

namespace pa
{
	class Map : public Render, public Dependency
	{
	public:
		Map(RenderSystem& renderSystem, float x, float y, int w, int h, bool hWrap, bool vWrap, int priority,
			Render::Type renderType);
		virtual ~Map()
		{
		}

		// Sets up the map
		virtual bool setup() = 0;

		// Size
		const Vect2<int>& getSize() const;

		// Wrapping
		bool getVWrap() const;
		bool getHWrap() const;

		// Visible
		void setVisible(bool visible);
		bool getVisible() const;

		// Colour
		void setColour(const Colour& colour);
		Colour& getColour();

		// Position
		PA_FORMAT_VECTOR_REAL(Position, m_position);

		// Scroll: The relative velocity of the map
		PA_FORMAT_VECTOR_REAL(Scroll, m_scroll);

	private:
		enum class Flags
		{
			HWrap,
			VWrap,
			Invisible,
			is_enum_bitfield
		};

		// Flags
		Bitfield<Flags> m_flags;

		// Size of the map
		const Vect2<int> m_size;

		// Colour
		Colour m_colour;
	};
}
