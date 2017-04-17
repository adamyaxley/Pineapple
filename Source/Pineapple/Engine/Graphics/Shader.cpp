/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Graphics/Shader.h>

pa::Shader::Shader(const pa::ShaderType shaderType, const char* path)
	: pa::Resource(path)
	, m_type(shaderType)
{
}

pa::Shader::~Shader()
{
}