/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Container/Rect.h>
#include <Pineapple/Engine/Graphics/Graphics.h>
#include <Pineapple/Engine/Platform/Platform.h>
#include <Pineapple/Graphics/OpenGL/DrawGL.h>
#include <Pineapple/Graphics/OpenGL/IncludeGL.h>
#include <Pineapple/Graphics/OpenGL/MapGL.h>

#include <math.h>

namespace
{
	using DrawFuncType = void (pa::MapGL::*)(pa::Vect2<float>, const pa::VertexBuffer2DGL&) const;

	DrawFuncType g_drawFuncArray[2][2];
}

pa::MapGL::MapGL(pa::Graphics& graphics, pa::TileSetGL& tileSet, std::shared_ptr<const pa::TileMap> tileMap, float x,
				 float y, bool hWrap, bool vWrap, int priority)
	: pa::Map(graphics.getRenderSystem(), x, y,
			  (tileMap ? tileSet.getTileSize().x * tileMap->getSizeConst().x : tileSet.getSize().x),
			  (tileMap ? tileSet.getTileSize().y * tileMap->getSizeConst().y : tileSet.getSize().y), hWrap, vWrap,
			  priority, (tileSet.getFormat() == pa::Texture::Format::RGBA ||
						 tileSet.getFormat() == pa::Texture::Format::LuminanceAlpha)
							? pa::Render::Type::Ordered
							: pa::Render::Type::Unordered)
	, m_graphics(graphics)
	, m_tileSet(tileSet)
	, m_tileMap(tileMap)
{
	m_dependencyNode = m_tileSet.addChildDependency(this);

	createVertexBuffer();

	// Fill draw function array
	g_drawFuncArray[0][0] = &pa::MapGL::drawMap;
	g_drawFuncArray[0][1] = &pa::MapGL::drawVWrappedMap;
	g_drawFuncArray[1][0] = &pa::MapGL::drawHWrappedMap;
	g_drawFuncArray[1][1] = &pa::MapGL::drawHVWrappedMap;
}

pa::MapGL::~MapGL()
{
	m_tileSet.removeChildDependency(m_dependencyNode);
}

void pa::MapGL::onDependencyNotify(pa::Dependency* parent)
{
	if (&m_tileSet == parent)
	{
		if (m_tileSet.isLoaded())
		{
			pa::Log::info("Creating vertex buffer");
			createVertexBuffer();
		}
		else
		{
			pa::Log::info("Cleaning vertex buffer");
			m_vertexBuffer.clean();
		}
	}
}

bool pa::MapGL::setup()
{
	return true;
}

void pa::MapGL::render()
{
	getPosition().x += getScroll().x;
	getPosition().y += getScroll().y;

	// Enable 2d textures
	glEnable(GL_TEXTURE_2D);

	// Use the tileset
	glBindTexture(GL_TEXTURE_2D, m_tileSet.getGLObject());

	glMatrixMode(GL_MODELVIEW);
	// Load a new drawing matrix
	glPushMatrix();
	glLoadIdentity();

	// Alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Move in front or behind sprites
	glTranslatef(0, 0, (GLfloat)getPriority());

	// Translate to the view
	glTranslatef(-static_cast<GLfloat>(m_graphics.getMapView().x), -static_cast<GLfloat>(m_graphics.getMapView().y),
				 0.0f);

	// Set the drawing colour
	glColor4f((GLfloat)getColour().R, (GLfloat)getColour().G, (GLfloat)getColour().B, (GLfloat)getColour().A);

	// Choose correct drawing function
	(this->*g_drawFuncArray[getHWrap()][getVWrap()])(getPosition(), m_vertexBuffer);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	// Refresh the drawing matrix
	glPopMatrix();

	// Disable 2d textures
	glDisable(GL_TEXTURE_2D);

	PA_GL_CHECK_ERROR();
}

void pa::MapGL::drawMap(pa::Vect2<float> pos, const pa::VertexBuffer2DGL& buffer) const
{
	glTranslatef(static_cast<GLfloat>(pos.x), static_cast<GLfloat>(pos.y), 0.0f);
	m_vertexBuffer.draw();
}

void pa::MapGL::drawHWrappedMap(pa::Vect2<float> pos, const pa::VertexBuffer2DGL& buffer) const
{
	// Get the position in the view frame
	pos.x -= m_graphics.getMapView().x;

	// Calculate start position
	pos.x = fmod(pos.x, (float)getSize().x);
	if (pos.x > 0)
	{
		pos.x -= getSize().x;
	}
	pos.x += m_graphics.getMapView().x;

	// Translate to start position
	glTranslatef(static_cast<GLfloat>(pos.x), static_cast<GLfloat>(pos.y), 0.f);

	// Draw tiled background
	for (float x = pos.x; x < m_graphics.getMapView().x + m_graphics.getSize().x; x += getSize().x)
	{
		m_vertexBuffer.draw();
		glTranslatef(static_cast<GLfloat>(getSize().x), 0.f, 0.f);
	}
}

void pa::MapGL::drawVWrappedMap(pa::Vect2<float> pos, const pa::VertexBuffer2DGL& buffer) const
{
	// Get the position in the view frame
	pos.y -= m_graphics.getMapView().y;

	// Calculate start position
	pos.y = fmod(pos.y, (float)getSize().y);
	if (pos.y > 0)
	{
		pos.y -= getSize().y;
	}
	pos.y += m_graphics.getMapView().y;

	// Translate to start position
	glTranslatef(static_cast<GLfloat>(pos.x), static_cast<GLfloat>(pos.y), 0.f);

	// Draw tiled background
	for (float y = pos.y; y < m_graphics.getMapView().y + m_graphics.getSize().y; y += getSize().y)
	{
		m_vertexBuffer.draw();
		glTranslatef(0.f, static_cast<GLfloat>(getSize().y), 0.f);
	}
}

void pa::MapGL::drawHVWrappedMap(pa::Vect2<float> pos, const pa::VertexBuffer2DGL& buffer) const
{
	// Get the Y position in the view frame
	pos.x -= m_graphics.getMapView().x;

	// Calculate start Y position
	pos.x = fmod(pos.x, (float)getSize().x);
	if (pos.x > 0)
	{
		pos.x -= getSize().x;
	}
	pos.x += m_graphics.getMapView().x;

	// Get the X position in the view frame
	pos.y -= m_graphics.getMapView().y;

	// Calculate start X position
	pos.y = fmod(pos.y, (float)getSize().y);
	if (pos.y > 0)
	{
		pos.y -= getSize().y;
	}
	pos.y += m_graphics.getMapView().y;

	// Draw tiled background
	for (float x = pos.x; x < m_graphics.getMapView().x + m_graphics.getSize().x; x += getSize().x)
	{
		for (float y = pos.y; y < m_graphics.getMapView().y + m_graphics.getSize().y; y += getSize().y)
		{
			glPushMatrix();
			glTranslatef(static_cast<GLfloat>(x), static_cast<GLfloat>(y), 0.0f);
			m_vertexBuffer.draw();
			glPopMatrix();
		}
	}
}

void pa::MapGL::createVertexBuffer()
{
	if (m_tileMap == nullptr)
	{
		m_vertexBuffer.createBuffers(4);
		m_vertexBuffer.setMode(GL_TRIANGLE_STRIP);

		// Simple texture draw
		m_vertexBuffer.addVertex(0, 0, 0, 0);
		m_vertexBuffer.addVertex(0, getSize().y, 0, 1);
		m_vertexBuffer.addVertex(getSize().x, 0, 1, 0);
		m_vertexBuffer.addVertex(getSize().x, getSize().y, 1, 1);
	}
	else
	{
		m_vertexBuffer.createBuffers(4 * m_tileMap->getSizeConst().y * m_tileMap->getSizeConst().x);
		m_vertexBuffer.setMode(GL_TRIANGLE_STRIP);

		int cols = m_tileSet.getSize().x / m_tileSet.getTileSize().x;
		int rows = m_tileSet.getSize().y / m_tileSet.getTileSize().y;

		const double texelBias = pa::DrawGL::getTexelBias();

		for (int ty = 0; ty < m_tileMap->getSizeConst().y; ty++)
		{
			for (int tx = 0; tx < m_tileMap->getSizeConst().x; tx++)
			{
				pa::Tile tile = m_tileMap->get(tx, ty);

				// If tile is not the transparent tile
				if ((tile & PA_TILE_INDEX) > 0)
				{
					// Move into 0-based tile indexing space
					tile--;

					// Find tile texture coordinates
					double ix = (double)((tile & PA_TILE_INDEX) % cols);
					double iy = (double)((tile & PA_TILE_INDEX) / cols); // x

					pa::Rect<double> texDouble(ix / cols, iy / rows, (ix + 1) / cols, (iy + 1) / rows);

					// Scale values to utilised size
					texDouble.x1 *= m_tileSet.getUtilisedSize().x;
					texDouble.y1 *= m_tileSet.getUtilisedSize().y;
					texDouble.x2 *= m_tileSet.getUtilisedSize().x;
					texDouble.y2 *= m_tileSet.getUtilisedSize().y;

					// Add bias the the texels so as to not sample neighboring tiles
					texDouble.x1 += texelBias;
					texDouble.x2 -= texelBias;
					texDouble.y1 += texelBias;
					texDouble.y2 -= texelBias;

					pa::Rect<GLfloat> tex((GLfloat)texDouble.x1, (GLfloat)texDouble.y1, (GLfloat)texDouble.x2,
										  (GLfloat)texDouble.y2);

					pa::Rect<GLfloat> vertex((GLfloat)(tx * m_tileSet.getTileSize().x),
											 (GLfloat)(ty * m_tileSet.getTileSize().y),
											 (GLfloat)((tx + 1) * m_tileSet.getTileSize().x),
											 (GLfloat)((ty + 1) * m_tileSet.getTileSize().y));

					// Tile flip
					if (tile & PA_TILE_HFLIP)
					{
						GLfloat temp = tex.x1;
						tex.x1 = tex.x2;
						tex.x2 = temp;
					}

					if (tile & PA_TILE_VFLIP)
					{
						GLfloat temp = tex.y1;
						tex.y1 = tex.y2;
						tex.y2 = temp;
					}

					// Make sure that the texels go right to the end so no tearing
					if (tx == m_tileMap->getSizeConst().x - 1)
					{
						vertex.x2 = (GLfloat)(texelBias + getSize().x);
					}

					if (ty == m_tileMap->getSizeConst().y - 1)
					{
						vertex.y2 = (GLfloat)(texelBias + getSize().y);
					}

					// Note that this generates two backwards facing triangles at the end of each row
					// to connect to the next row. This relies on GL_CULL_FACE being enabled.
					m_vertexBuffer.addVertex(vertex.x1, vertex.y1, tex.x1, tex.y1);
					m_vertexBuffer.addVertex(vertex.x1, vertex.y2, tex.x1, tex.y2);
					m_vertexBuffer.addVertex(vertex.x2, vertex.y1, tex.x2, tex.y1);
					m_vertexBuffer.addVertex(vertex.x2, vertex.y2, tex.x2, tex.y2);
				}
			}
		}
	}

	m_vertexBuffer.upload();
}
