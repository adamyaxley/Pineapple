/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Platform/Platform.h>
#include <Pineapple/Graphics/OpenGL/UtilGL.h>

void pa::UtilGL::checkGLError(pa::SourceMeta sourceMeta)
{
	GLenum error = glGetError();

	if (GL_NO_ERROR != error)
	{
		pa::Log::info("{} {} {}: {} ({})", sourceMeta.file, sourceMeta.function, sourceMeta.line, "GL Error",
					  getGLErrorString(error));
	}
}

const char* pa::UtilGL::getGLErrorString(GLenum error)
{
	switch (error)
	{
	case GL_NO_ERROR: return "No Error";
	case GL_INVALID_ENUM: return "GL_INVALID_ENUM"; break;
	case GL_INVALID_VALUE: return "GL_INVALID_VALUE"; break;
	case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION"; break;
	case GL_STACK_OVERFLOW: return "GL_STACK_OVERFLOW"; break;
	case GL_STACK_UNDERFLOW: return "GL_STACK_UNDERFLOW"; break;
	case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY"; break;
	default: return "Unknown Error";
	}
}
