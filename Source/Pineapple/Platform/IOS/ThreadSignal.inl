template <int N>
pa::ThreadSignal<N>::ThreadSignal()
	: m_count(0)
{
	// Platform::print("ThreadSignal() (%d, %d)", m_count, N);
	// pthread_barrier_init(&m_barr, nullptr, N); // return is int, do some error handling...
	// PA_ASSERTF(sem_init(&m_mutex, 0, 1) != -1, "Mutex failed to init");
	// PA_ASSERTF(sem_init(&m_barrier, 0, 0) != -1, "Barrier failed to init");
	m_mutex = dispatch_semaphore_create(1);
	m_barrier = dispatch_semaphore_create(0);
	m_barrier2 = dispatch_semaphore_create(1);
}

template <int N>
pa::ThreadSignal<N>::~ThreadSignal()
{
	// pthread_barrier_destroy(&m_barr); // return is int, do some error handling...
	// sem_destroy(&m_mutex);
	// sem_destroy(&m_barrier);
    
	// release' is unavailable: not available in automatic reference counting mode
	//dispatch_release(m_mutex);
	//dispatch_release(m_barrier);
	//dispatch_release(m_barrier2);
}

template <int N>
void pa::ThreadSignal<N>::sync()
{
	/*Platform::print("sync() (%d, %d)", m_count, N);
	//pthread_barrier_wait(&m_barr); // return is int, do some error handling...
	sem_wait(&m_mutex);
	m_count = m_count + 1;
	sem_post(&m_mutex);

	if (m_count == N)
	{
		Platform::print("m_count == N (%d, %d)", m_count, N);
		sem_post(&m_barrier);
	}

	sem_wait(&m_barrier);
	sem_post(&m_barrier);*/

	// pthread_barrier_wait(&m_barr); // return is int, do some error handling...
	/*dispatch_semaphore_wait(m_mutex, DISPATCH_TIME_FOREVER);
	const int count = ++m_count;

	if (count == N)
	{
		m_count = 0;
	}
	//Platform::print("sync() (%d, %d)", count, N);
	dispatch_semaphore_signal(m_mutex);

	if (count == N)
	{
		dispatch_semaphore_signal(m_barrier);
	}

	dispatch_semaphore_wait(m_barrier, DISPATCH_TIME_FOREVER);
	dispatch_semaphore_signal(m_barrier);*/

	dispatch_semaphore_wait(m_mutex, DISPATCH_TIME_FOREVER);
	++m_count;
	if (m_count == N)
	{
		dispatch_semaphore_wait(m_barrier2, DISPATCH_TIME_FOREVER);
		dispatch_semaphore_signal(m_barrier);
	}
	dispatch_semaphore_signal(m_mutex);

	dispatch_semaphore_wait(m_barrier, DISPATCH_TIME_FOREVER);
	dispatch_semaphore_signal(m_barrier);

	dispatch_semaphore_wait(m_mutex, DISPATCH_TIME_FOREVER);

	--m_count;
	if (m_count == 0)
	{
		dispatch_semaphore_wait(m_barrier, DISPATCH_TIME_FOREVER);
		dispatch_semaphore_signal(m_barrier2);
	}

	dispatch_semaphore_signal(m_mutex);

	dispatch_semaphore_wait(m_barrier2, DISPATCH_TIME_FOREVER);
	dispatch_semaphore_signal(m_barrier2);
}
