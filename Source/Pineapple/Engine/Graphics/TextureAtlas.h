/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <memory>

namespace pa
{
	class Texture;
	struct Document;

	class TextureAtlas
	{
	public:
		TextureAtlas(std::shared_ptr<Texture> texture);
		~TextureAtlas();

		// Loads a JSON texture atlas file, returns true if successful
		bool load(const char* atlasFilename);

		// Creates a new texture from the atlas, returns nullptr if the provided filename was not found
		std::shared_ptr<Texture> createTexture(const char* filename);

	private:
		std::shared_ptr<Texture> m_texture;

		std::unique_ptr<Document> m_document;

		bool m_isLoaded;
	};
}
