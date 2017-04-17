/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Platform/Event.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace pa
{
	bool lookupWindowsKey(unsigned int key, LPARAM lParam, Key& keyOut);
}
