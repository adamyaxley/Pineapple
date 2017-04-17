/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/System/Time.h>
#include <functional>

namespace pa
{
	struct Timer
	{
		Time duration;
		Time alarm;
		bool repeat;
		std::function<void()> callback;

		template <typename T>
		Timer(Time duration, Time alarm, bool repeat, T&& callback)
			: duration(duration)
			, alarm(alarm)
			, repeat(repeat)
			, callback(std::forward<T>(callback))
		{
		}

		bool operator>(const Timer& rhs) const
		{
			return alarm > rhs.alarm;
		}
	};
}