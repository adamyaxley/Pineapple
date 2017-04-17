/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#ifdef PA_OPENGLES2

	#include <Pineapple/Engine/Platform/Platform.h>
	#include <Pineapple/Engine/Graphics/Shader.h>
	#include <Pineapple/Graphics/OpenGL/ProgramGL.h>

pa::ProgramGL::ProgramGL()
	: m_id(0)
	, m_vertex(nullptr)
	, m_fragment(nullptr)
	, m_isLinked(false)
{
	m_id = glCreateProgram();
	bindAttribute(pa::ProgramAttribute::POSITION, "pa_Position");
	bindAttribute(pa::ProgramAttribute::NORMAL, "pa_Normal");
	bindAttribute(pa::ProgramAttribute::UV, "pa_TexCoord");
}

pa::ProgramGL::~ProgramGL()
{
	if (m_id > 0)
	{
		glDeleteProgram(m_id);
	}
}

void pa::ProgramGL::bindAttribute(const pa::ProgramAttribute param, const char* name) const
{
	glBindAttribLocation(m_id, static_cast<GLuint>(param), name);
}

void pa::ProgramGL::use()
{
	PA_ASSERTF(isLinked(), "Cannot use a program which is not linked");
	glUseProgram(m_id);
}

bool pa::ProgramGL::isLinked()
{
	return m_isLinked;
}

void pa::ProgramGL::attachShader(pa::Shader* shader)
{
	switch (shader->getType())
	{
	case pa::ShaderType::VERTEX:
		PA_ASSERTF(m_vertex == nullptr, "Vertex shader already attached");
		m_vertex = shader;
		break;
	case pa::ShaderType::FRAGMENT:
		PA_ASSERTF(m_vertex == nullptr, "Fragment shader already attached");
		m_fragment = shader;
		break;
	}

	shader->addChildDependency(this);
	onDependencyNotify(shader);
}

void pa::ProgramGL::printLog() const
{
	int infoLogLen = 0;
	int charsWritten = 0;

	glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &infoLogLen);

	if (infoLogLen > 0)
	{
		auto infoLog = std::make_unique<GLchar[]>(infoLogLen);
		glGetProgramInfoLog(m_id, infoLogLen, &charsWritten, infoLog.get());
		pa::Log::info(infoLog.get());
	}
}

void pa::ProgramGL::setUniformInt(const char* name, int value)
{
	GLuint location = glGetUniformLocation(m_id, name);
	glUniform1i(location, value);
}

void pa::ProgramGL::setUniformFloat(const char* name, float value)
{
	GLuint location = glGetUniformLocation(m_id, name);
	glUniform1f(location, value);
}

void pa::ProgramGL::onDependencyNotify(pa::Dependency* parent)
{
	// One of the shaders changed (let's relink the program)
	if (parent == m_vertex)
	{
		if (m_vertex->isLoaded())
		{
			// vertex shader was loaded
			glAttachShader(m_id, m_vertex->getId());
		}
		else
		{
			// vertex shader was unloaded
			glDetachShader(m_id, m_vertex->getId());
		}
	}
	else if (parent == m_fragment)
	{
		if (m_fragment->isLoaded())
		{
			// fragment shader was loaded
			glAttachShader(m_id, m_fragment->getId());
		}
		else
		{
			// fragment shader was unloaded
			glDetachShader(m_id, m_fragment->getId());
		}
	}

	if (m_vertex != nullptr && m_fragment != nullptr && m_vertex->isLoaded() && m_fragment->isLoaded())
	{
		pa::Log::info("Linking program {} with fragment shader: '{}' and vertex shader: '{}'", m_id,
					  m_fragment->getPath(), m_vertex->getPath());
		link();

		if (isLinked())
		{
			pa::Log::info("Successfully linked program {}", m_id);
		}
	}
	else
	{
		m_isLinked = false;
	}
}

void pa::ProgramGL::link()
{
	glLinkProgram(m_id);

	GLint result;
	glGetProgramiv(m_id, GL_LINK_STATUS, &result);

	if (result == GL_TRUE)
	{
		m_isLinked = true;
	}
	else
	{
		printLog();
		m_isLinked = false;
	}
}

#endif