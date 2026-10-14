/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Platform/Platform.h>

pa::Platform::Platform(const pa::PlatformSettings& settings)
	: m_settings(settings)
{
}

const pa::Vect2<int>& pa::Platform::getSize() const
{
	return m_size;
}

bool pa::Platform::isFullScreen() const
{
	return m_isFullScreen;
}

const pa::Input& pa::Platform::getInput() const
{
	return m_input;
}

const pa::Pointer& pa::Platform::getPointer() const
{
	return m_pointer;
}

pa::Graphics* pa::Platform::getGraphics()
{
	return m_graphics.get();
}

pa::Sound* pa::Platform::getSound()
{
	return m_sound.get();
}

const pa::FileSystem& pa::Platform::getFileSystem() const
{
	return *m_fileSystem.get();
}