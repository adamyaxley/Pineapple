/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Container/Vect2.h>
#include <Pineapple/Graphics/OpenGL/TextureCoordsGL.h>

namespace pa
{
	namespace DrawGL
	{
		// Draws a 1 by 1 quad centered at (0.5, 0.5)
		void drawQuad(bool hFlip, bool vFlip, const TextureCoordsGL& textureCoords);

		// Transforms the current drawing matrix
		void transform2d(const Vect2<float>& view, const Vect2<float>& origin, const Vect2<float>& position, int depth,
						 const Vect2<float>& scale, float rotation);

		// This will get the bias that will be used when clamping texture regions so as to not sample neighboring
		// regions
		double getTexelBias();
	}
}
