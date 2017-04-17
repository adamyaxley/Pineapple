/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Platform/Platform.h>
#include <Pineapple/Sound/FMOD/UtilFMOD.h>

bool pa::UtilFMOD::checkResult(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		pa::Log::info("FMOD Error: {}", FMOD_ErrorString(result));
		return false;
	}
	else
	{
		return true;
	}
}
