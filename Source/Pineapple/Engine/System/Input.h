/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Platform/Event.h>

#include <vector>

namespace pa
{
	struct Input
	{
		bool wantsQuit() const
		{
			for (const Event& event : events)
			{
				if (event.type == pa::Event::Type::Quit)
				{
					return true;
				}
			}
			return false;
		}

		std::vector<Event> events;
	};
}
