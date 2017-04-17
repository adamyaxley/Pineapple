/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Graphics/Shader.h>
#include <Pineapple/Graphics/OpenGL/IncludeGL.h>

namespace pa
{
	class ShaderGL : public Shader
	{
	public:
		ShaderGL(const ShaderType shaderType, const char* path);
		~ShaderGL();

		virtual bool onLoad() override;
		virtual bool onUnload() override;

		virtual int getId() const override;

	private:
		void printLog() const;

		GLuint m_id;
	};
}
