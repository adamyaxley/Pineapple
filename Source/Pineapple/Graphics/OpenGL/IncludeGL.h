/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#ifdef _MSC_VER
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
#endif

#ifdef PA_OPENGLES1
	#ifdef __APPLE__
		#include <OpenGLES/ES1/gl.h>
	#else
		#include <GLES/gl.h>
	#endif
#else
	#include <glad/glad.h>
#endif

#include <Pineapple/Graphics/OpenGL/UtilGL.h>
