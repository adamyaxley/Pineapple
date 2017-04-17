/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

//#include <ft2build.h>
//#include FT_TYPES_H

#include <Pineapple/Engine/Util/Macro.h>
#include <Pineapple/Graphics/OpenGL/IncludeGL.h>

#define PA_GL_CHECK_ERROR() pa::UtilGL::checkGLError(PA_SOURCE_META)

namespace pa
{
	namespace UtilGL
	{
		void checkGLError(SourceMeta sourceMeta);
		const char* getGLErrorString(GLenum error);
	}
}
