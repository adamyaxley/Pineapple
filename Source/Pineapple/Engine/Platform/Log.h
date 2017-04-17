/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <spdlog/fmt/fmt.h>

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
