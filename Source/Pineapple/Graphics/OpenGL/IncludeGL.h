/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#if defined(__ANDROID__) || defined(__APPLE__)
	#define PA_OPENGLES
#endif

#ifdef _MSC_VER
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
#endif

#ifdef PA_OPENGLES
	#ifdef __APPLE__
		#include <OpenGLES/ES1/gl.h>
	#else
		#ifdef PA_OPENGLES2
			#include <GLES2/gl2.h>
		#else
			#include <GLES/gl.h>
		#endif
	#endif
	#ifndef PA_NO_UTIL_GL_FTGL
		#pragma clang diagnostic push
		#pragma clang diagnostic ignored "-Wdeprecated-register"
		#include <FTGL/ftgles.h>
		#pragma clang diagnostic pop
	#endif
#else
	#include <glad/glad.h>
#endif

#include <Pineapple/Graphics/OpenGL/UtilGL.h>
