/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Sound/Music.h>

pa::Music::Music(pa::Sound& sound, const char* path)
	: pa::Resource(path)
	, m_sound(sound)
{
	m_handle = m_sound.registerMusic(this);
}

pa::Music::~Music()
{
	m_sound.unregisterMusic(m_handle);
}
