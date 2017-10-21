/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Graphics/Texture.h>
#include <Pineapple/Engine/Graphics/TextureAtlas.h>
#include <Pineapple/Engine/Platform/File.h>
#include <Pineapple/Engine/Platform/Platform.h>
#include <rapidjson/document.h>
#include <rapidjson/rapidjson.h>

struct pa::Document
{
	rapidjson::Document json;
};

pa::TextureAtlas::TextureAtlas(std::shared_ptr<pa::Texture> texture)
	: m_texture(texture)
	, m_isLoaded(false)
{
	m_document = std::make_unique<pa::Document>();
}

pa::TextureAtlas::~TextureAtlas()
{
}

bool pa::TextureAtlas::load(const char* atlasFilename)
{
	std::string contents;
	pa::File::Result result = pa::File::readString(atlasFilename, contents);

	if (result != pa::File::Result::Success)
	{
		pa::Log::info("{}: {}", pa::File::getResultString(result), atlasFilename);
	}

	// Load json
	m_document->json.Parse<0>(contents.c_str());

	if (m_document->json.HasParseError())
	{
		pa::Log::info("Failed to parse {}, error was: {}", atlasFilename, m_document->json.GetParseError());
		m_isLoaded = false;
	}
	else
	{
		m_isLoaded = true;
	}

	return m_isLoaded;
}

std::shared_ptr<pa::Texture> pa::TextureAtlas::createTexture(const char* filename)
{
	PA_ASSERTF(m_isLoaded, "You must load a texture atlas first.");

	if (m_document->json.IsObject())
	{
		if (m_document->json.HasMember("frames"))
		{
			rapidjson::Value& frames = m_document->json["frames"];

			if (frames.IsArray())
			{
				// find path
				for (unsigned int i = 0; i < frames.Size(); i++)
				{
					rapidjson::Value& element = frames[i];
					if (element.HasMember("filename"))
					{
						const char* elementFilename = element["filename"].GetString();
						if (strcmp(elementFilename, filename) == 0)
						{
							// Same! Load this information
							rapidjson::Value& frame = element["frame"];

							int x = frame["x"].GetInt();
							int y = frame["y"].GetInt();
							int w = frame["w"].GetInt();
							int h = frame["h"].GetInt();

							return m_texture->createTexture(x, y, w, h);
						}
					}
				}
			}
		}
	}

	return nullptr;
}