/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Graphics/Graphics.h>
#include <Pineapple/Engine/Graphics/Shader.h>
#include <Pineapple/Engine/Graphics/Texture.h>

namespace pa
{
	namespace Asset
	{
		void load(Graphics& graphics);

		namespace Texture
		{
			std::shared_ptr<pa::Texture> getPixelTexture();
		}

		namespace Font
		{
		}

		namespace Shader
		{
			std::shared_ptr<pa::Shader> getQuadFragShader();
			std::shared_ptr<pa::Shader> getQuadVertShader();
			std::shared_ptr<pa::Shader> getPassVertShader();
		}
	}
}
