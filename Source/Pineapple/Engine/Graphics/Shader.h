/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Platform/Resource.h>
#include <Pineapple/Engine/Util/Macro.h>

namespace pa
{
	enum class ShaderType
	{
		VERTEX,
		FRAGMENT,
	};

	class Shader : public Resource
	{
	public:
		Shader(const ShaderType shaderType, const FilePath& path);
		virtual ~Shader();

		PA_FORCE_INLINE ShaderType getType();

		virtual int getId() const = 0;

	protected:
		const ShaderType m_type;
	};
}

#include <Pineapple/Engine/Graphics/Shader.inl>
