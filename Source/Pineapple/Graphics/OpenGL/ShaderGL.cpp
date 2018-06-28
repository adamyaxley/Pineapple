/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#ifndef PA_OPENGLES1

	#include <Pineapple/Engine/Platform/Platform.h>
	#include <Pineapple/Graphics/OpenGL/ShaderGL.h>

pa::ShaderGL::ShaderGL(const pa::ShaderType shaderType, const pa::FilePath& path)
	: pa::Shader(shaderType, path)
	, m_id(0)
{
}

pa::ShaderGL::~ShaderGL()
{
}

bool pa::ShaderGL::onLoad()
{
	switch (m_type)
	{
	case pa::ShaderType::VERTEX: m_id = glCreateShader(GL_VERTEX_SHADER); break;

	case pa::ShaderType::FRAGMENT: m_id = glCreateShader(GL_FRAGMENT_SHADER); break;

	default: break;
	}

	// Load from file into buff
	std::string contents;
	{
		pa::FileBuffer fileBuffer;
		pa::FileResult result = getPath().read(fileBuffer);

		if (result != pa::FileResult::Success)
		{
			pa::Log::info("{}: {}", pa::FileSystem::getResultString(result), getPath().asString());
		}
		contents = fileBuffer.createString();
	}

	const char* buffer = contents.c_str();
	glShaderSource(m_id, 1, &buffer, nullptr);
	glCompileShader(m_id);

	GLint result;
	glGetShaderiv(m_id, GL_COMPILE_STATUS, &result);

	if (result == GL_TRUE)
	{
		return true;
	}
	else
	{
		printLog();
		return false;
	}
}

bool pa::ShaderGL::onUnload()
{
	// unload shader
	if (m_id > 0)
	{
		glDeleteShader(m_id);
	}

	return true;
}

int pa::ShaderGL::getId() const
{
	return m_id;
}

void pa::ShaderGL::printLog() const
{
	int infoLogLen = 0;
	int charsWritten = 0;

	glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &infoLogLen);

	if (infoLogLen > 0)
	{
		auto infoLog = std::make_unique<GLchar[]>(infoLogLen);
		glGetShaderInfoLog(m_id, infoLogLen, &charsWritten, infoLog.get());
		pa::Log::info(infoLog.get());
	}
}

#endif