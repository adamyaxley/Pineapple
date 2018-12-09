/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Platform/Memory.h>
#include <Pineapple/Engine/Platform/Platform.h>
#include <Pineapple/Graphics/OpenGL/FontGL.h>
#include <Pineapple/Graphics/OpenGL/TextGL.h>
#include <Pineapple/Graphics/OpenGL/UtilGL.h>
#include <fontstash.h>
#include <memory>

pa::FontGL::FontGL(pa::Graphics& graphics, FONScontext* fonsContext, const pa::FilePath& path)
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
	pa::FileBuffer buffer;
	auto result = getPath().read(buffer);
	if (result != pa::FileResult::Success)
	{
		pa::Log::info("{}: {}", pa::FileSystem::getResultString(result), getPath().asString());
		return false;
	}
	m_buffer = std::move(buffer.getBuffer());
	m_fonsFont = fonsAddFontMem(m_fonsContext, getPath().asString().c_str(), m_buffer.get(), static_cast<int>(buffer.getSize()), 0 /*do not free the data*/);
	pa::Log::info("Loaded Font: {}", getPath().asString());
	return true;
}

bool pa::FontGL::onUnload()
{
	// <todo> We can't unload individual fonts at the moment using fontstash
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