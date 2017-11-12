/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Graphics/Graphics.h>
#include <Pineapple/Engine/Prefab/Asset/Asset.h>

namespace
{
	std::shared_ptr<pa::Texture> g_pixelTexture = nullptr;

	std::shared_ptr<pa::Shader> g_quadFradShader = nullptr;
	std::shared_ptr<pa::Shader> g_quadVertShader = nullptr;
	std::shared_ptr<pa::Shader> g_passVertShader = nullptr;
}

void pa::Asset::load(pa::Graphics& graphics)
{
	// Load textures TODO do this from atlas
	g_pixelTexture = graphics.createTexture("Pineapple/Textures/pixel.png", pa::FileStorage::EngineAsset);

	// Load shaders TODO quad shaders
	// g_quadFradShader = graphics.createShader(pa::ShaderType::FRAGMENT, "Pineapple/Shaders/quad.frag");
	// g_quadVertShader = graphics.createShader(pa::ShaderType::VERTEX, "Pineapple/Shaders/quad.vert");
	g_passVertShader = graphics.createShader(pa::ShaderType::VERTEX, "Pineapple/Shaders/pass.vert", pa::FileStorage::EngineAsset);
}

std::shared_ptr<pa::Texture> pa::Asset::Texture::getPixelTexture()
{
	return g_pixelTexture;
}

std::shared_ptr<pa::Shader> pa::Asset::Shader::getQuadFragShader()
{
	return g_quadFradShader;
}

std::shared_ptr<pa::Shader> pa::Asset::Shader::getQuadVertShader()
{
	return g_quadVertShader;
}

std::shared_ptr<pa::Shader> pa::Asset::Shader::getPassVertShader()
{
	return g_passVertShader;
}