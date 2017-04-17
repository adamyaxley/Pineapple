/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

template <typename T>
PA_FORCE_INLINE void pa::Program::setUniform(const char* name, T value)
{
	// There is no implementation for this type
	static_assert(false, "No implementation for this uniform type");
}

template <>
PA_FORCE_INLINE void pa::Program::setUniform<int>(const char* name, int value)
{
	setUniformInt(name, value);
}

template <>
PA_FORCE_INLINE void pa::Program::setUniform<float>(const char* name, float value)
{
	setUniformFloat(name, value);
}
