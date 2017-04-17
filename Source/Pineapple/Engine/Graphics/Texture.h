/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Graphics/Sprite.h>
#include <Pineapple/Engine/Platform/Resource.h>
#include <memory>

namespace pa
{
	class Texture : public Resource
	{
	public:
		enum class Format
		{
			Luminance,
			LuminanceAlpha,
			RGB,
			RGBA,
			Colour16,
			Colour256
		};

		Texture(const char* path);
		virtual ~Texture()
		{
		}

		// Returns nullptr if unsuccessful, a pointer to the created sprite otherwise
		virtual std::unique_ptr<Sprite> createSprite() = 0;

		virtual Texture* createTexture(int x, int y, int width, int height) = 0;

		// Gets the size of the texture, in pixels
		const Vect2<int>& getSize() const;

		// Gets the texture format
		Format getFormat() const;

	protected:
		void setSize(const Vect2<int>& size);
		void setFormat(Format format);

	private:
		Vect2<int> m_size;

		Format m_format;
	};
}
