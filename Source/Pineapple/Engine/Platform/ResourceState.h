/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Platform/Resource.h>
#include <chrono>
#include <memory>

namespace pa
{
	struct ResourceState
	{
		std::shared_ptr<Resource> resource;
		bool isLoaded;
		bool isMonitored;
		std::chrono::system_clock::time_point modificationTime;
	};
}
