/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Util/Macro.h>

namespace pa
{
	// Obscures integers from memory attacks
	class Obscure
	{
	public:
		PA_FORCE_INLINE Obscure(const int& value);
		PA_FORCE_INLINE Obscure(const Obscure& copy);
		PA_FORCE_INLINE Obscure& operator=(const Obscure& copy);

		PA_FORCE_INLINE Obscure();
		PA_FORCE_INLINE ~Obscure();

		// Setter
		PA_FORCE_INLINE Obscure& operator=(const int& value);

		// Getter
		PA_FORCE_INLINE operator int() const;

#ifdef PA_DEBUG
		// Simulate memory hack
		PA_FORCE_INLINE void simulatePointerHack();
		PA_FORCE_INLINE void simulateHashHack();
#endif

	private:
		PA_FORCE_INLINE int get() const;
		PA_FORCE_INLINE void store(int value) const;

		PA_FORCE_INLINE std::uintptr_t hash(int value) const;

		mutable std::unique_ptr<int> fraglist[32]; // pointers
		mutable int key; // xor
		mutable std::uintptr_t checksum; // checksum
	};
}

#include <Pineapple/Engine/Util/Obscure.inl>
