/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Graphics/Sprite.h>
#include <Pineapple/Engine/Util/Macro.h>
#include <algorithm>

namespace
{
	pa::Render::Type getRenderTypeFromFrames(const std::vector<std::shared_ptr<pa::Texture>>& frames)
	{
		auto it = std::find_if(std::begin(frames), std::end(frames), [](auto frame) {
			return pa::Render::Type::Ordered == pa::Texture::getRenderTypeFromTextureFormat(frame->getFormat());
		});

		if (it != std::end(frames))
		{
			return pa::Render::Type::Ordered;
		}
		else
		{
			return pa::Render::Type::Unordered;
		}
	}

	pa::Vect2<int> getSizeFromFrames(const std::vector<std::shared_ptr<pa::Texture>>& frames)
	{
		PA_ASSERTF(frames.size() > 0, "A sprite must have at least one frame");

		const auto& size = frames[0]->getSize();
		auto it = std::find_if(std::begin(frames), std::end(frames),
							   [&size](auto frame) { return size != frame->getSize(); });

		PA_ASSERTF(it == std::end(frames), "Size of all frames of a Sprite must be the same");
		return size;
	}
}

pa::Sprite::Sprite(pa::RenderSystem& renderSystem, std::vector<std::shared_ptr<Texture>>& frames, int priority)
	: pa::Render(renderSystem, getRenderTypeFromFrames(frames), priority)
	, pa::SpriteAttributes(getSizeFromFrames(frames))
	, m_frames(frames)
	, m_currentFrame(0)
{
	PA_ASSERTF(m_frames.size() > 0, "A sprite must have at least one frame");
}

void pa::Sprite::setHFlip(bool hFlip)
{
	hFlip ? m_flags.set(Flags::HFlip) : m_flags.clear(Flags::HFlip);
}

bool pa::Sprite::getHFlip() const
{
	return m_flags.getBool(Flags::HFlip);
}

void pa::Sprite::setVFlip(bool vFlip)
{
	vFlip ? m_flags.set(Flags::VFlip) : m_flags.clear(Flags::VFlip);
}

bool pa::Sprite::getVFlip() const
{
	return m_flags.getBool(Flags::VFlip);
}

void pa::Sprite::setVisible(bool visible)
{
	visible ? m_flags.clear(Flags::Invisible) : m_flags.set(Flags::Invisible);
}

bool pa::Sprite::getVisible() const
{
	return !m_flags.getBool(Flags::Invisible);
}

void pa::Sprite::setFrame(unsigned int frame)
{
	m_currentFrame = frame % getNumberOfFrames();
}

unsigned int pa::Sprite::getFrame() const
{
	return m_currentFrame;
}

unsigned int pa::Sprite::getNumberOfFrames() const
{
	return m_frames.size();
}

void pa::Sprite::setPlaybackEnabled(bool enabled)
{
	enabled ? m_flags.set(Flags::EnablePlayback) : m_flags.clear(Flags::EnablePlayback);
}

bool pa::Sprite::getPlaybackEnabled() const
{
	return m_flags.getBool(Flags::EnablePlayback);
}

void pa::Sprite::setPlaybackMode(PlaybackMode mode)
{
	mode == PlaybackMode::Backward ? m_flags.set(Flags::BackwardPlayback) : m_flags.clear(Flags::BackwardPlayback);
}

pa::Sprite::PlaybackMode pa::Sprite::getPlaybackMode() const
{
	return m_flags.get(Flags::BackwardPlayback) ? PlaybackMode::Backward : PlaybackMode::Forward;
}

void pa::Sprite::pin(const pa::Sprite* sprite, pa::Vect2<float>& offset)
{
	offset.scale(sprite->getScaleConst());
	offset.rotate(sprite->getRotation());
	offset += sprite->getPositionConst();
	setPosition(offset);
}

void pa::Sprite::render()
{
	auto& texture = m_frames[getFrame()];

	texture->render(*this);

	if (getPlaybackEnabled())
	{
		// Advance animation
		if (getPlaybackMode() == pa::Sprite::PlaybackMode::Forward)
		{
			m_currentFrame = (m_currentFrame + 1) % m_frames.size();
		}
		else
		{
			if (m_currentFrame > 0)
			{
				m_currentFrame -= 1;
			}
			else
			{
				m_currentFrame = m_frames.size() - 1;
			}
		}
	}
}