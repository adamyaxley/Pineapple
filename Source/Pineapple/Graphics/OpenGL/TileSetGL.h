/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Graphics/Graphics.h>
#include <Pineapple/Engine/Graphics/TileMap.h>
#include <Pineapple/Engine/Graphics/TileSet.h>
#include <Pineapple/Graphics/OpenGL/IncludeGL.h>

namespace pa
{
	class TileSetGL : public TileSet
	{
	public:
		TileSetGL(Graphics& graphics, int tileWidth, int tileHeight, const FilePath& path);
		~TileSetGL();

		virtual bool onLoad() override;
		virtual bool onUnload() override;

		// Create a map
		virtual std::unique_ptr<Map> createMap(std::shared_ptr<const pa::TileMap> tilemap, float x, float y, bool hWrap,
											   bool vWrap, int priority) override;

		// Gets the OpenGL texture object associated with this tile set
		GLuint getGLObject() const;

		Vect2<double>& getUtilisedSize();

	private:
		Graphics& m_graphics;

		GLuint m_id;

		Vect2<double> m_utilisedSize;
	};
}
