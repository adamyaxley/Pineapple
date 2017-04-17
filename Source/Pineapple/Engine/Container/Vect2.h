/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

//#include <Pineapple/Engine/Util/Macro.h>
#include <math.h>

namespace pa
{
	template <class T>
	struct Vect2
	{
		T x, y;

		Vect2()
			: x(0)
			, y(0)
		{
		}

		Vect2(const Vect2<T>& copy)
		{
			operator=(copy);
		}

		Vect2(T _x, T _y)
			: x(_x)
			, y(_y)
		{
		}
		~Vect2()
		{
		}

		// Cartesian set
		void cart(const T& x, const T& y)
		{
			this->x = x;
			this->y = y;
		}

		template <typename U>
		void polar(const U& r, const float radians)
		{
			x = r * cos(radians);
			y = r * sin(radians);
		}

		// Get the angle of this vector in radians
		float angle() const
		{
			return atan2(y, x);
		}

		void unit()
		{
			operator/=(length());
		}

		T length() const
		{
			return sqrt(lengthSquared());
		}

		T lengthSquared() const
		{
			return (x * x + y * y);
		}

		// Dot product
		template <typename U>
		T dot(const Vect2<U>& other) const
		{
			return (x * other.x + y * other.y);
		}

		// Scale the vector
		template <typename U>
		void scale(const Vect2<U>& other)
		{
			x *= other.x;
			y *= other.y;
		}

		// Rotate the vector
		void rotate(float radians)
		{
			T xCache = x;
			x = x * cos(radians) - y * sin(radians);
			y = xCache * sin(radians) + y * cos(radians);
		}

		// Assignment
		template <typename U>
		Vect2<T>& operator=(const Vect2<U>& rhs)
		{
			// dependency issue... PA_ASSERTF(this != &rhs, "Cannot assign to self");
			x = rhs.x;
			y = rhs.y;
			return *this;
		}

		// Compound assignment (addition)
		template <typename U>
		Vect2<T>& operator+=(const Vect2<U>& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			return *this;
		}

		// Compound assignment (subtraction)
		template <typename U>
		Vect2<T>& operator-=(const Vect2<U>& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}

		// Compound assignment (scale)
		template <typename U>
		Vect2<T>& operator*=(const U& rhs)
		{
			x *= rhs;
			y *= rhs;
			return *this;
		}

		// Compound assignment (inverse scale)
		template <typename U>
		Vect2<T>& operator/=(const U& rhs)
		{
			x /= rhs;
			y /= rhs;
			return *this;
		}

		// Addition
		template <typename U>
		const Vect2<T> operator+(const Vect2<U>& other) const
		{
			Vect2<T> result = *this;
			result += other;
			return result;
		}

		// Subtraction
		template <typename U>
		const Vect2<T> operator-(const Vect2<U>& other) const
		{
			Vect2<T> result = *this;
			result -= other;
			return result;
		}

		// Scale
		template <typename U>
		const Vect2<T> operator*(const U& other) const
		{
			Vect2<T> result = *this;
			result *= other;
			return result;
		}

		// Inverse scale
		template <typename U>
		const Vect2<T> operator/(const U& other) const
		{
			Vect2<T> result = *this;
			result /= other;
			return result;
		}

		// Equality
		bool operator==(const Vect2<T>& other) const
		{
			return (!(*this != other));
		}

		// Inequality
		bool operator!=(const Vect2<T>& other) const
		{
			return (x != other.x || y != other.y);
		}

		template <typename U>
		operator Vect2<U>() const
		{
			Vect2<U> temp;
			temp.x = x;
			temp.y = y;

			return temp;
		}
	};
}
