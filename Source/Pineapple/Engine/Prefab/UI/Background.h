/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Graphics/Texture.h>
#include <Pineapple/Engine/System/World.h>

namespace pa
{
	class Background : public Object
	{
	public:
		Background(World& world, int priority);

		virtual void onStep(Time deltaTime) override;

		void setColour(const Colour& colour);
		Colour& getColour();

	private:
		std::unique_ptr<Sprite> m_sprite;
	};
}
