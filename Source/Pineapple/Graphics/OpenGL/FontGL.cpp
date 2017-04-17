/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Platform/File.h>
#include <Pineapple/Engine/Platform/Memory.h>
#include <Pineapple/Engine/Platform/Platform.h>
#include <Pineapple/Graphics/OpenGL/FontGL.h>
#include <Pineapple/Graphics/OpenGL/TextGL.h>
#include <Pineapple/Graphics/OpenGL/UtilGL.h>
#include <fontstash.h>

pa::FontGL::FontGL(pa::Graphics& graphics, FONScontext* fonsContext, const char* path)
	: pa::Font(path)
	, m_graphics(graphics)
	, m_fonsContext(fonsContext)
	, m_buffer(nullptr)
	, m_faceSize(12)
	, m_fonsFont(FONS_INVALID)
{
}

pa::FontGL::~FontGL()
{
}

bool pa::FontGL::onLoad()
{
	unsigned int size;
	pa::File::Result result;

	// Get the file size
	result = pa::File::getSize(getPath(), &size);

	if (result != pa::File::Result::Success)
	{
		pa::Log::info("{}: {}", pa::File::getResultString(result), getPath());
		return false;
	}

	// Allocate our buffer
	m_buffer = (unsigned char*)pa::Memory::allocate(size);

	// Read in the data
	result = pa::File::read(getPath(), m_buffer);
	if (result != pa::File::Result::Success)
	{
		pa::Log::info("{}: {}", pa::File::getResultString(result), getPath());
		pa::Memory::deallocate(m_buffer);
		m_buffer = nullptr;

		return false;
	}

	m_fonsFont = fonsAddFontMem(m_fonsContext, getPath(), m_buffer, size, 0 /*do not free the data*/);

	pa::Log::info("Loaded Font: {}", getPath());

	return true;
}

bool pa::FontGL::onUnload()
{
	// Not sure what to do here
	// fons__freeFont(m_fonsFont);
	// m_fonsContext->nfonts--;

	pa::Memory::deallocate((void*)m_buffer);
	m_buffer = nullptr;

	return true;
}

std::unique_ptr<pa::Text> pa::FontGL::createText()
{
	// Create a new text object
	return std::make_unique<pa::TextGL>(m_graphics, *this);
}

void pa::FontGL::setSize(unsigned int size)
{
	m_faceSize = size;

	// should be re-loaded
}

unsigned int pa::FontGL::getSize()
{
	return m_faceSize;
}

FONScontext* pa::FontGL::getFonsContext()
{
	return m_fonsContext;
}

int pa::FontGL::getFonsFont()
{
	return m_fonsFont;
}