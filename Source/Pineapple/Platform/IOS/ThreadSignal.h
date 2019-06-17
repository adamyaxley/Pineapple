/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

//
//  ThreadSignal.h
//  IOS
//
//  Created by apple on 04/08/2014.
//  Copyright (c) 2014 Pineapple. All rights reserved.
//

#pragma once

#include <distch/dispatch.h>

namespace pa
{
	template <int N>
	class ThreadSignal
	{
	public:
		ThreadSignal();
		~ThreadSignal();

		void sync();

	private:
		dispatch_semaphore_t m_mutex;
		dispatch_semaphore_t m_barrier;
		dispatch_semaphore_t m_barrier2;

		int m_count;
	};
}

#include <Pineapple/Platform/IOS/ThreadSignal.inl>