/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Graphics/Program.h>
#include <Pineapple/Engine/Util/Macro.h>
#include <Pineapple/Graphics/OpenGL/IncludeGL.h>

namespace pa
{
	class ProgramGL : public Program
	{
	public:
		ProgramGL();
		virtual ~ProgramGL();

		virtual void bindAttribute(const ProgramAttribute param, const char* name) const override;
		virtual void use() override;
		virtual bool isLinked() override;

		virtual void attachShader(Shader* shader) override;

		// virtual void setUniform(const char* name, float value);

		void printLog() const;

		virtual void setUniformInt(const char* name, int value) override;
		virtual void setUniformFloat(const char* name, float value) override;

		virtual void onDependencyNotify(Dependency* parent) override;

	private:
		void link();

		bool m_isLinked;

		Shader* m_vertex;
		Shader* m_fragment;

		GLuint m_id;
	};
}
