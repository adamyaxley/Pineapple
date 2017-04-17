/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Platform/Log.h>

#include <cstddef>

// Optimization Hints
#if defined(_MSC_VER)
	#define PA_FORCE_INLINE __forceinline
#elif defined(__GNUC__)
	#define PA_FORCE_INLINE inline __attribute__((always_inline))
#else
	#define PA_FORCE_INLINE inline
#endif

// Simple numerical
#define PA_CLAMP(floor, ceil, i) (i > ceil ? ceil : (i < floor ? floor : i))
#define PA_MAX(a, b) (a > b ? a : b)
#define PA_MIN(a, b) (a > b ? b : a)
#define PA_SIGN(a) (a > 0 ? 1 : (a == 0 ? 0 : -1))

// Common angles
const float PA_PI = 3.1415926535f;

// Bitfields
#define PA_BIT(bit) (1 << bit)
#define PA_BIT_SET(val, bit) val |= PA_BIT(bit)
#define PA_BIT_CLEAR(val, bit) val &= ~PA_BIT(bit)
#define PA_BIT_TOGGLE(val, bit) val ^= PA_BIT(bit)
#define PA_BIT_IS_SET(val, bit) (val & PA_BIT(bit))

#define PA_COUNT_OF(array) (sizeof(array) / sizeof(array[0]))

namespace pa
{
	struct SourceMeta
	{
		int line;
		const char* function;
		const char* file;

		SourceMeta(int line, const char* function, const char* file)
		{
			this->line = line;
			this->function = function;
			this->file = file;
		}
	};
}

#define PA_SOURCE_META pa::SourceMeta(__LINE__, __FUNCTION__, __FILE__)

// Debugging
#ifdef PA_DEBUG
	#if defined(_MSC_VER)
void __debugbreak();
		#define PA_BREAKPOINT __debugbreak();
	#else
		#define PA_BREAKPOINT reinterpret_cast<void (*)()>(0)();
	#endif

	#define PA_ASSERTF(cond, ...)           \
	{                                   \
		if (cond)                       \
		{                               \
		}                               \
		else                            \
		{                               \
			pa::Log::info(__VA_ARGS__); \
			PA_BREAKPOINT               \
		}                               \
	}
	#define PA_PRINT_META() Log::info("{}: {} ({})", __FILE__, __FUNCTION__, __LINE__)
#else
	#define PA_ASSERTF(cond, ...) \
	{                         \
	}
	#define PA_PRINT_META()
#endif
