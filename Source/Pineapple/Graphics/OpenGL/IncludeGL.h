/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#if defined(__ANDROID__) || defined(__APPLE__)
	//#define PA_OPENGLES2 already defined hard
#endif

#ifdef _MSC_VER
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
#endif

#ifdef PA_OPENGLES2
	#ifdef __APPLE__
		#include <OpenGLES/ES1/gl.h> // TODO wrong
	#else
		#include <GLES2/gl2.h>
	#endif
#elif defined (PA_OPENGLES1)
#	include <GLES/gl.h>
#else
	#include <glad/glad.h>
#endif

#include <Pineapple/Graphics/OpenGL/UtilGL.h>
