/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Graphics/Sprite.h>
#include <Pineapple/Engine/Graphics/Texture.h>
#include <Pineapple/Engine/Util/Macro.h>
#include <vector>

namespace pa
{
	class AnimatedSprite : public Sprite
	{
	public:
		unsigned int getFrame();
		void setFrame(unsigned int frame);
		unsigned int getFrameCount();

		template <typename... TRest>
		PA_FORCE_INLINE AnimatedSprite(RenderSystem& renderSystem, Texture* texture, TRest&&... textures);

		~AnimatedSprite();

		virtual void render() override;

	private:
		template <typename... TRest>
		PA_FORCE_INLINE AnimatedSprite(RenderSystem& renderSystem, bool recurring, Texture* texture,
									   TRest&&... textures);

		AnimatedSprite(RenderSystem& renderSystem, bool recurring);

		std::vector<std::unique_ptr<Sprite>> m_frameList;

		unsigned int m_frame;
		unsigned int m_current;

		void hideAll();
	};
}

#include <Pineapple/Engine/Graphics/AnimatedSprite.inl>
