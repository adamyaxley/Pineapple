/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

PA_FORCE_INLINE pa::Pointer::Pointer()
{
}

PA_FORCE_INLINE pa::Pointer::~Pointer()
{
}

PA_FORCE_INLINE const pa::Vect2<int>& pa::Pointer::getPosition() const
{
	return m_position;
}

PA_FORCE_INLINE void pa::Pointer::setPosition(int x, int y)
{
	m_position.set(x, y);
}

PA_FORCE_INLINE bool pa::Pointer::getDown() const
{
	return m_down;
}

PA_FORCE_INLINE void pa::Pointer::setDown(bool down)
{
	m_down = down;
}