/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Util/Macro.h>

#include <cstdint>
#include <type_traits>

namespace
{
	template <int N>
	struct BitfieldType
	{
	};

	template <>
	struct BitfieldType<8>
	{
		using Type = std::uint8_t;
	};
	template <>
	struct BitfieldType<16>
	{
		using Type = std::uint16_t;
	};
	template <>
	struct BitfieldType<32>
	{
		using Type = std::uint32_t;
	};
	template <>
	struct BitfieldType<64>
	{
		using Type = std::uint64_t;
	};

	template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type,
			  typename = typename std::enable_if<std::is_unsigned<T>::value>::type>
	constexpr T roundUpToNextPowerOf2(T value, unsigned maxb = sizeof(T) * 8, unsigned curb = 1)
	{
		return maxb <= curb ? value : roundUpToNextPowerOf2(((value - 1) | ((value - 1) >> curb)) + 1, maxb, curb << 1);
	}

	template <typename T>
	constexpr T atLeast8(T a)
	{
		return a > 8 ? a : 8;
	}
}

namespace pa
{
	template <typename T>
	class Bitfield
	{
	public:
		using Storage =
			typename BitfieldType<roundUpToNextPowerOf2(atLeast8(static_cast<unsigned>(T::is_enum_bitfield)))>::Type;

		PA_FORCE_INLINE Bitfield() noexcept;

		PA_FORCE_INLINE void set(T flag) noexcept;
		PA_FORCE_INLINE void clear(T flag) noexcept;
		PA_FORCE_INLINE Storage get(T flag) const noexcept;
		PA_FORCE_INLINE bool getBool(T flag) const noexcept;
		PA_FORCE_INLINE void toggle(T flag) noexcept;

	private:
		Storage m_bits;
	};
}

#include <Pineapple/Engine/Container/Bitfield.inl>