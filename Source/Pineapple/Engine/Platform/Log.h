/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#if defined(__clang__)
	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wexpansion-to-defined"
#endif
#include <spdlog/fmt/fmt.h>
#if defined(__clang__ )
	#pragma clang diagnostic pop
#endif

namespace _paInternal
{
	void logInfoString(std::string&& str);
}

namespace pa
{
	namespace Log
	{
		template <typename... Args>
		void info(Args&&... args)
		{
			_paInternal::logInfoString(fmt::format(std::forward<Args>(args)...));
		}
	}
}
