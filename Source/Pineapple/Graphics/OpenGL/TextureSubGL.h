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
		TextureSubGL(Graphics& graphics, TextureGL& texture, const Vect2<int>& from, const Vect2<int>& to);
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
