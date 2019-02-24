/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Platform/Memory.h>

#include <cstdlib>
#include <signal.h>
#include <stdint.h>

PA_FORCE_INLINE pa::Obscure::Obscure(const int& value)
{
	store(value);
}

PA_FORCE_INLINE pa::Obscure::Obscure(const pa::Obscure& copy)
{
	this->operator=(copy);
}

PA_FORCE_INLINE pa::Obscure& pa::Obscure::operator=(const pa::Obscure& copy)
{
	return this->operator=(static_cast<int>(copy));
}

PA_FORCE_INLINE pa::Obscure::Obscure()
{
}

PA_FORCE_INLINE pa::Obscure::~Obscure()
{
}

PA_FORCE_INLINE pa::Obscure& pa::Obscure::operator=(const int& value)
{
	store(value);
	return *this;
}

PA_FORCE_INLINE pa::Obscure::operator int() const
{
	int value = get();
	store(value); // redo storage
	return value;
}

#ifdef PA_DEBUG
PA_FORCE_INLINE void pa::Obscure::simulatePointerHack()
{
	int index = rand() % 32;

	PA_BIT_TOGGLE(*fraglist[index], index);
}

PA_FORCE_INLINE void pa::Obscure::simulateHashHack()
{
	checksum++;
}
#endif

#ifdef __clang__
	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wuninitialized"
#endif

PA_FORCE_INLINE int pa::Obscure::get() const
{
	int result;

	for (int i = 0; i < 32; i++)
	{
		// Extract information from the 32 pointers bit by bit
		if (PA_BIT_IS_SET(*fraglist[i], i))
		{
			PA_BIT_CLEAR(result, i);
		}
		else
		{
			PA_BIT_SET(result, i);
		}
	}

	// Check hash
	if (hash(result) != checksum)
	{
		// Doesn't match, memory hack
		reinterpret_cast<void (*)()>(0)();

		raise(SIGSEGV);
		raise(SIGABRT);
		exit(-1);

		// If none of them work for some reason, go into infinite recursion
		get();
	}

	// XOR
	result ^= key;

	// NOT
	result = ~result;

	return result;
}

#ifdef __clang__
	#pragma clang diagnostic pop
#endif

PA_FORCE_INLINE void pa::Obscure::store(int value) const
{
	// NOT
	value = ~value;

	// Create a random XOR token
	key = rand();

	// XOR
	value ^= key;

	// Hash for checking later
	checksum = hash(value);

	for (int i = 0; i < 32; i++) // TODO allocate in a random order
	{
		// Allocate a random space for each pointer
		fraglist[i] = std::make_unique<int>();

		// Store bit number i here (only modifying one bit)
		if (PA_BIT_IS_SET(value, i))
		{
			PA_BIT_CLEAR(*fraglist[i], i);
		}
		else
		{
			PA_BIT_SET(*fraglist[i], i);
		}
	}
}

PA_FORCE_INLINE std::uintptr_t pa::Obscure::hash(int value) const
{
	return static_cast<std::uintptr_t>(value) ^ reinterpret_cast<std::uintptr_t>(this);
}
