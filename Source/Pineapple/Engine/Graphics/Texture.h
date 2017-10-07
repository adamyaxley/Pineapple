/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Container/Vect2.h>
#include <Pineapple/Engine/Graphics/Render.h>
#include <Pineapple/Engine/Platform/Resource.h>
#include <memory>

namespace pa
{
	class Sprite;

	class Texture : public Resource, std::enable_shared_from_this<Texture>
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

		static Render::Type getRenderTypeFromTextureFormat(Format format)
		{
			return (format == Format::RGBA ||
				format == Format::LuminanceAlpha)
				? Render::Type::Ordered
				: Render::Type::Unordered;
		}

		Texture(const char* path, RenderSystem& renderSystem);
		virtual ~Texture()
		{
		}

		std::unique_ptr<Sprite> createSprite();

		virtual void render(const Sprite& sprite) = 0;

		virtual Texture* createTexture(int x, int y, int width, int height) = 0;

		// Gets the size of the texture, in pixels
		const Vect2<int>& getSize() const;

		// Gets the texture format
		Format getFormat() const;

	protected:
		void setSize(const Vect2<int>& size);
		void setFormat(Format format);

	private:
		RenderSystem& m_renderSystem;

		Vect2<int> m_size;

		Format m_format;
	};
}
