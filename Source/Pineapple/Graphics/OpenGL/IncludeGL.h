/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#ifdef PA_OPENGLES1
	#if defined(_WINDOWS)
		#include <glad/glad.h> // GLES1
	#elif defined(__APPLE__)
		#include <OpenGLES/ES1/gl.h>
	#else
		#include <GLES/gl.h>
	#endif
#else
	#include <glad/glad.h>
#endif

#include <Pineapple/Graphics/OpenGL/UtilGL.h>
