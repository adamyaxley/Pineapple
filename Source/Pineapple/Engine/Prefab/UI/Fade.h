/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Graphics/Sprite.h>
#include <Pineapple/Engine/Graphics/Texture.h>
#include <Pineapple/Engine/Prefab/UI/Background.h>
#include <Pineapple/Engine/System/Object.h>
#include <Pineapple/Engine/Util/Macro.h>

namespace pa
{
	class Fade : public Object
	{
	public:
		Fade(World& world, int priority);
		~Fade();

		void fade(float from, float to, Time time);
		bool isFading() const;

		virtual void onDestroy() override;

		virtual void onStep(Time deltaTime) override;

		void setColour(const Colour& colour);
		Colour& getColour();

	private:
		std::shared_ptr<Background> m_background;

		float m_delta;
		float m_target;
	};
}
