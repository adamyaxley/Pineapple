/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Container/Bitfield.h>
#include <Pineapple/Engine/Container/Vect2.h>
#include <Pineapple/Engine/Graphics/Colour.h>
#include <Pineapple/Engine/Graphics/Render.h>
#include <Pineapple/Engine/Graphics/SpriteAttributes.h>
#include <Pineapple/Engine/Graphics/Texture.h>
#include <Pineapple/Engine/Util/Format.h>

namespace pa
{
	class Sprite : public Render, public SpriteAttributes
	{
	public:
		enum class PlaybackMode
		{
			Forward,
			Backward
		};

		Sprite(RenderSystem& renderSystem, std::vector<std::shared_ptr<Texture>>& frames, int priority);
		Sprite(const Sprite& copy) = delete;
		Sprite& operator=(const Sprite& assignment) = delete;

		virtual ~Sprite()
		{
		}

		// Flags
		void setHFlip(bool hFlip);
		bool getHFlip() const;

		void setVFlip(bool vFlip);
		bool getVFlip() const;

		void setVisible(bool visible);
		bool getVisible() const;

		void setFrame(std::size_t frame);
		std::size_t getFrame() const;
		std::size_t getNumberOfFrames() const;

		void setPlaybackEnabled(bool enabled);
		bool getPlaybackEnabled() const;

		void setPlaybackMode(PlaybackMode mode);
		PlaybackMode getPlaybackMode() const;

		// Pin this sprite on another sprite with the offset
		void pin(const Sprite& sprite, const Vect2<float>& offset);

		virtual void render() override;

	private:
		enum class Flags
		{
			HFlip,
			VFlip,
			Invisible,
			EnablePlayback,
			BackwardPlayback,
			is_enum_bitfield
		};

		// Flags
		Bitfield<Flags> m_flags;

		// Current frame
		std::size_t m_currentFrame;

		// Frame list
		const std::vector<std::shared_ptr<Texture>> m_frames;
	};
}
