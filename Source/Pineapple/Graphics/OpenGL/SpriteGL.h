/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Graphics/Sprite.h>
#include <Pineapple/Graphics/OpenGL/TextureGL.h>

namespace pa
{
	class SpriteGL : public Sprite
	{
	public:
		SpriteGL(Graphics& graphics, TextureGL& texture);
		~SpriteGL()
		{
		}

		virtual void render() override;

	private:
		const Graphics& m_graphics;
		const TextureGL& m_texture;
	};
}
