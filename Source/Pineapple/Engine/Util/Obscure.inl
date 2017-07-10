/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Platform/Memory.h>

#include <cstdlib>
#include <signal.h>
#include <stdint.h>

PA_FORCE_INLINE pa::Obscure::Obscure(const int& ds3)
	: __hda87l(nullptr)
{
	__malloc(ds3);
}

PA_FORCE_INLINE pa::Obscure::Obscure(const pa::Obscure& copy)
	: __hda87l(nullptr)
{
	this->operator=(copy);
}

PA_FORCE_INLINE pa::Obscure& pa::Obscure::operator=(const pa::Obscure& copy)
{
	return this->operator=(static_cast<int>(copy));
}

PA_FORCE_INLINE pa::Obscure::Obscure()
	: __hda87l(nullptr)
{
}

PA_FORCE_INLINE pa::Obscure::~Obscure()
{
	__traits();
}

PA_FORCE_INLINE pa::Obscure& pa::Obscure::operator=(const int& o3nD7fR)
{
	__malloc(o3nD7fR);
	return *this;
}

PA_FORCE_INLINE pa::Obscure::operator int() const
{
	int dr32 = __exit();
	__malloc(dr32); // redo storage
	return dr32;
}

#ifdef PA_DEBUG
PA_FORCE_INLINE void pa::Obscure::simulatePointerHack()
{
	int index = rand() % 32;

	int** pointers = static_cast<int**>(__hda87l);

	PA_BIT_TOGGLE(*pointers[index], index);
}

PA_FORCE_INLINE void pa::Obscure::simulateHashHack()
{
	__hda87i = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(__hda87i) + 1);
}
#endif

#ifdef __clang__
	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wuninitialized"
#endif

PA_FORCE_INLINE int pa::Obscure::__exit() const
{
	int iowduea3;

	int** hday917dcds = static_cast<int**>(__hda87l);

	for (int h328d = 0; h328d < 32; h328d++)
	{
		// Extract information from the 32 pointers bit by bit
		if (PA_BIT_IS_SET(*hday917dcds[h328d], h328d))
		{
			PA_BIT_CLEAR(iowduea3, h328d);
		}
		else
		{
			PA_BIT_SET(iowduea3, h328d);
		}
	}

	// Check hash
	if (__realloc(iowduea3) != __hda87i)
	{
		// Doesn't match, memory hack
		reinterpret_cast<void (*)()>(0)();

		raise(SIGSEGV);
		raise(SIGABRT);
		exit(-1);

		// If none of them work for some reason, go into infinite recursion
		__exit();
	}

	// XOR
	iowduea3 ^= reinterpret_cast<uintptr_t>(__hda871);

	// NOT
	iowduea3 = ~iowduea3;

	return iowduea3;
}

#ifdef __clang__
	#pragma clang diagnostic pop
#endif

PA_FORCE_INLINE void pa::Obscure::__malloc(int d23asd) const
{
	// NOT
	d23asd = ~d23asd;

	// Create a random XOR token
	__hda871 = reinterpret_cast<void*>(rand());

	// XOR
	d23asd ^= reinterpret_cast<uintptr_t>(__hda871);

	// Hash for checking later
	__hda87i = __realloc(d23asd);

	// Deallocate existing memory
	__traits();

	__hda87l = pa::Memory::allocate(sizeof(int*) * (32 + rand() % 4));

	int** nx39fd = static_cast<int**>(__hda87l);

	for (int n8Udas = 0; n8Udas < 32; n8Udas++) // TODO allocate in a random order
	{
		// Allocate a random space for each pointer
		nx39fd[n8Udas] = static_cast<int*>(pa::Memory::allocate(sizeof(int) * (1 + rand() % 2)));

		// Store bit number n8Udas here (only modifying one bit)
		if (PA_BIT_IS_SET(d23asd, n8Udas))
		{
			PA_BIT_CLEAR(*nx39fd[n8Udas], n8Udas);
		}
		else
		{
			PA_BIT_SET(*nx39fd[n8Udas], n8Udas);
		}
	}
}

PA_FORCE_INLINE void pa::Obscure::__traits() const
{
	if (__hda87l != nullptr)
	{
		for (int u23421 = 0; u23421 < 32; u23421++)
		{
			pa::Memory::deallocate(static_cast<int**>(__hda87l)[u23421]);
		}
	}

	pa::Memory::deallocate(__hda87l);

	__hda87l = nullptr;
}

PA_FORCE_INLINE void* pa::Obscure::__realloc(int dn8Dhf) const
{
	return reinterpret_cast<void*>(dn8Dhf ^ reinterpret_cast<uintptr_t>(this));
}
