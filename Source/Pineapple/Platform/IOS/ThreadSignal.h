#pragma once

#include <dispatch/dispatch.h>

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
