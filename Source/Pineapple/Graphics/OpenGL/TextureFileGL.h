/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Graphics/OpenGL/TextureGL.h>

namespace pa
{
	class TextureFileGL : public TextureGL
	{
	public:
		TextureFileGL(Graphics& graphics, const FilePath& path);
		~TextureFileGL();

		virtual bool onLoad() override;
		virtual bool onUnload() override;

	private:
	};
}
