/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#define PA_FORMAT_VECTOR_VAR(type, name, variable) Vect2<type> variable;

#define PA_FORMAT_VECTOR_GET(type, name, variable) \
	Vect2<type>& get##name()                       \
	{                                              \
		return variable;                           \
	}

#define PA_FORMAT_VECTOR_GET_CONST(type, name, variable) \
	const Vect2<type>& get##name##Const() const          \
	{                                                    \
		return variable;                                 \
	}

#define PA_FORMAT_VECTOR_SET(type, name, variable) \
	void set##name(Vect2<type>& value)             \
	{                                              \
		variable = value;                          \
	}

#define PA_FORMAT_VECTOR_SET_CONST(type, name, variable) \
	void set##name(const Vect2<type>& value)             \
	{                                                    \
		variable = value;                                \
	}

#define PA_FORMAT_VECTOR_SET_ELEMENTS(type, name, variable) \
	void set##name(type x, type y)                          \
	{                                                       \
		variable.cart(x, y);                                \
	}

#define PA_FORMAT_VECTOR_SET_ALL(type, name, variable) \
	PA_FORMAT_VECTOR_SET(type, name, variable)         \
	PA_FORMAT_VECTOR_SET_CONST(type, name, variable)   \
	PA_FORMAT_VECTOR_SET_ELEMENTS(type, name, variable)

#define PA_FORMAT_VECTOR(type, name, variable)       \
	PA_FORMAT_VECTOR_VAR(type, name, variable)       \
	PA_FORMAT_VECTOR_GET(type, name, variable)       \
	PA_FORMAT_VECTOR_GET_CONST(type, name, variable) \
	PA_FORMAT_VECTOR_SET_ALL(type, name, variable)

#define PA_FORMAT_VECTOR_REAL(name, variable) PA_FORMAT_VECTOR(float, name, variable)

#define PA_FORMAT_VECTOR_INT(name, variable) PA_FORMAT_VECTOR(int, name, variable)
