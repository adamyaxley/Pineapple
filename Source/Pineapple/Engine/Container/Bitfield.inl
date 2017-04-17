/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

template <typename T>
PA_FORCE_INLINE pa::Bitfield<T>::Bitfield() noexcept
	: m_bits(0x0)
{
	static_assert(std::is_enum<T>::value, "T must be an enum");
}

template <typename T>
PA_FORCE_INLINE void pa::Bitfield<T>::set(T flag) noexcept
{
	m_bits |= (Storage(0x1) << static_cast<Storage>(flag));
}

template <typename T>
PA_FORCE_INLINE void pa::Bitfield<T>::clear(T flag) noexcept
{
	m_bits &= ~(Storage(0x1) << static_cast<Storage>(flag));
}

template <typename T>
PA_FORCE_INLINE typename pa::Bitfield<T>::Storage pa::Bitfield<T>::get(T flag) const noexcept
{
	return m_bits & (Storage(0x1) << static_cast<Storage>(flag));
}

template <typename T>
PA_FORCE_INLINE bool pa::Bitfield<T>::getBool(T flag) const noexcept
{
	return (m_bits & (Storage(0x1) << static_cast<Storage>(flag))) != 0;
}

template <typename T>
PA_FORCE_INLINE void pa::Bitfield<T>::toggle(T flag) noexcept
{
	m_bits ^= (Storage(0x1) << static_cast<Storage>(flag));
}