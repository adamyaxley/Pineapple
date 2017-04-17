/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Container/Rect.h>
#include <Pineapple/Graphics/OpenGL/TextureGL.h>

namespace pa
{
	class TextureSubGL : public TextureGL
	{
	public:
		TextureSubGL(Graphics& graphics, TextureGL& texture, int x1, int y1, int x2, int y2);
		~TextureSubGL();

		virtual bool onLoad() override;
		virtual bool onUnload() override;

	protected:
		virtual void onDependencyNotify(Dependency* parent) override;

	private:
		TextureGL& m_texture;

		Rect<int> m_rect;
	};
}
