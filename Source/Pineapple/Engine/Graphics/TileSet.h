/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Container/Vect2.h>
#include <Pineapple/Engine/Graphics/Map.h>
#include <Pineapple/Engine/Graphics/Texture.h>
#include <Pineapple/Engine/Graphics/TileMap.h>
#include <Pineapple/Engine/Platform/Resource.h>
#include <memory>

namespace pa
{
	class TileSet : public Resource
	{
	public:
		TileSet(int tileWidth, int tileHeight, const char* path);
		~TileSet()
		{
		}

		// Gets the tile size of this tile set
		const Vect2<int>& getTileSize() const;

		// Gets the width and height measured in pixels
		const Vect2<int>& getSize() const;

		// Sets the width and height measured in pixels
		void setSize(const Vect2<int>& size);

		// Creates a map from this tile set
		virtual std::unique_ptr<Map> createMap(std::shared_ptr<const pa::TileMap> tilemap, float x, float y, bool hWrap,
											   bool vWrap, int priority) = 0;

		// Get underlying texture format
		Texture::Format getFormat() const;

	protected:
		void setFormat(Texture::Format format);

	private:
		// Tile size
		const Vect2<int> m_tileSize;

		// Number of tiles
		Vect2<int> m_size;

		// Get underlying texture format
		Texture::Format m_format;
	};
}
