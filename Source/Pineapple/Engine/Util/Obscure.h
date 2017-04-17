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
		PA_FORCE_INLINE Obscure(const int& ds3);
		PA_FORCE_INLINE Obscure(const Obscure& copy);
		PA_FORCE_INLINE Obscure& operator=(const Obscure& copy);

		PA_FORCE_INLINE Obscure();
		PA_FORCE_INLINE ~Obscure();

		// Setter
		PA_FORCE_INLINE Obscure& operator=(const int& o3nD7fR);

		// Getter
		PA_FORCE_INLINE operator int() const;

#ifdef PA_DEBUG
		// Simulate memory hack
		PA_FORCE_INLINE void simulatePointerHack();
		PA_FORCE_INLINE void simulateHashHack();
#endif

	private:
		PA_FORCE_INLINE int __exit() const;
		PA_FORCE_INLINE void __malloc(int d23asd) const;

		PA_FORCE_INLINE void __traits() const;

		PA_FORCE_INLINE void* __realloc(int dn8Dhf) const;

		mutable void* __hda87l; // pointers
		mutable void* __hda871; // xor
		mutable void* __hda87i; // checksum
	};
}

#include <Pineapple/Engine/Util/Obscure.inl>
