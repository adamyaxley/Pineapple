#pragma once

#include <Pineapple/Engine/Graphics/Colour.h>
#include <Pineapple/Engine/Util/Format.h>
#include <Pineapple/Engine/Container/Vect2.h>

namespace pa
{
	class SpriteAttributes
	{
	public:
		SpriteAttributes(const Vect2<int>& size);

		// Attributes
		const Vect2<int>& getSize() const;

		PA_FORMAT_VECTOR_REAL(Position, m_position)
		PA_FORMAT_VECTOR_REAL(Origin, m_origin)
		PA_FORMAT_VECTOR_REAL(Scale, m_scale)

		void setScale(float scale);

		void setRotation(float radians);
		float getRotation() const;

		void setColour(const Colour& colour);
		Colour& getColour();
		const Colour& getColour() const;

	protected:
		void setSize(const Vect2<int>& size);

	private:

		// Size
		Vect2<int> m_size;

		// Rotation clockwise in radians
		float m_rotation;

		// Colour
		Colour m_colour;
	};
}