/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Graphics/OpenGL/ImageGL.h>
#include <Pineapple/Graphics/OpenGL/MapGL.h>
#include <Pineapple/Graphics/OpenGL/TileSetGL.h>

pa::TileSetGL::TileSetGL(pa::Graphics& graphics, int tileWidth, int tileHeight, const char* path)
	: pa::TileSet(tileWidth, tileHeight, path)
	, m_graphics(graphics)
	, m_id(0)
{
}

pa::TileSetGL::~TileSetGL()
{
}

bool pa::TileSetGL::onLoad()
{
	pa::ImageGL image(getPath());

	bool loaded = false;

	// Try to load the image
	if (image.load())
	{
		m_id = image.createGLObject();

		if (glIsTexture(m_id) == GL_TRUE)
		{
			loaded = true;

			setFormat(image.getOriginalFormat());

			pa::Vect2<int> size(image.getSize().x, image.getSize().y);
			setSize(size);

			m_utilisedSize.cart((double)(size.x - (size.x % getTileSize().x)) / size.x,
								(double)(size.y - (size.y % getTileSize().y)) / size.y);

			pa::Log::info("Loaded TileSet: {}", getPath());
		}
		else
		{
			pa::Log::info("Error, GL texture could not be generated for: {}", getPath());
		}
	}

	image.unload();

	return loaded;
}

bool pa::TileSetGL::onUnload()
{
	if (glIsTexture(m_id))
	{
		glDeleteTextures(1, &m_id);
		m_id = 0;
	}

	return true;
}

std::unique_ptr<pa::Map> pa::TileSetGL::createMap(std::shared_ptr<const pa::TileMap> tilemap, float x, float y, bool hWrap, bool vWrap,
												  int priority)
{
	PA_ASSERTF(isLoaded(), "Tileset is not loaded");
	return std::make_unique<pa::MapGL>(m_graphics, *this, tilemap, x, y, hWrap, vWrap, priority);
}

GLuint pa::TileSetGL::getGLObject() const
{
	PA_ASSERTF(isLoaded(), "Tileset is not loaded");
	return m_id;
}

pa::Vect2<double>& pa::TileSetGL::getUtilisedSize()
{
	return m_utilisedSize;
}
