/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

namespace pa
{
	typedef float ColourType;

	struct Colour
	{
		Colour()
			: R(1.f)
			, G(1.f)
			, B(1.f)
			, A(1.f)
		{
		}
		Colour(ColourType red, ColourType green, ColourType blue, ColourType alpha = 1.0f)
			: R(red)
			, G(green)
			, B(blue)
			, A(alpha)
		{
		}

		ColourType R, G, B, A;
	};

	namespace ColourSet
	{
		const Colour Transparent(1.0f, 1.0f, 1.0f, 0.f);
		const Colour White(1.0f, 1.0f, 1.0f);
		const Colour LightGray(0.95f, 0.95f, 0.95f);
		const Colour Gray(0.8f, 0.8f, 0.8f);
		const Colour DarkGray(0.4f, 0.4f, 0.4f);
		const Colour Red(1.0f, 0.f, 0.f);
		const Colour DarkRed(0.5f, 0.f, 0.f);
		const Colour Yellow(1.f, 1.0f, 0.0f);
		const Colour Orange(1.0f, 106.f / 255.f, 0.f);
		const Colour Green(0.f, 1.f, 0.f);
		const Colour DarkGreen(0.f, 0.5f, 0.f);
		const Colour SkyBlue(0.f, 1.f, 1.f);
		const Colour Blue(0.f, 0.f, 1.f);
		const Colour DarkBlue(0.f, 0.f, 0.5f);
		const Colour Pink(1.f, 0.f, 220.f / 255.f);
		const Colour Purple(0.5f, 0.f, 0.5f);
		const Colour Brown(150.f / 255.f, 75.f / 255.f, 0.f);
		const Colour Black(0.f, 0.f, 0.f);
	};
}
