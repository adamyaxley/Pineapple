/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Platform/Dependency.h>
#include <Pineapple/Engine/Util/Macro.h>

namespace pa
{
	class Shader;

	// Structure to track the numbers attributes are bound to
	enum class ProgramAttribute
	{
		POSITION,
		NORMAL,
		UV
	};

	class Program : public Dependency
	{
	public:
		Program();
		virtual ~Program();

		virtual void bindAttribute(const ProgramAttribute param, const char* name) const = 0;
		virtual void use() = 0;
		virtual bool isLinked() = 0;

		virtual void attachShader(Shader* shader) = 0;

		virtual void setUniformInt(const char* name, int value) = 0;
		virtual void setUniformFloat(const char* name, float value) = 0;
	};
}
