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

	class Texture : public Resource, public std::enable_shared_from_this<Texture>
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
			return (format == Format::RGBA || format == Format::LuminanceAlpha) ? Render::Type::Ordered
																				: Render::Type::Unordered;
		}

		Texture(const FilePath& path, RenderSystem& renderSystem);
		virtual ~Texture()
		{
		}

		std::unique_ptr<Sprite> createSprite();

		/// \brief Creates an animated sprite by splitting up the texture into a uniform grid of frames of equal
		/// size. The frames are numbered from 0 to N from right to left, top to bottom.
		/// \param frameSize The size of each frame.
		/// \returns A std::shared_ptr to the created sprite.
		std::unique_ptr<Sprite> createSprite(const Vect2<int>& frameSize);

		virtual void render(const Sprite& sprite) = 0;

		virtual std::shared_ptr<Texture> createTexture(const Vect2<int>& pos, const Vect2<int>& size) = 0;

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
