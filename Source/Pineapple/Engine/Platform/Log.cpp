/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Platform/Log.h>
#include <spdlog/spdlog.h>

namespace _paInternal
{
	void logInfoString(std::string&& str)
	{
		auto logger = spdlog::get("pineapple");
		if (!logger)
		{
#ifdef __ANDROID__
			logger = spdlog::android_logger("pineapple", "PINEAPPLE");
#else
			logger = spdlog::stdout_color_mt("pineapple");
#endif
		}
		logger->info(str);
	}
}