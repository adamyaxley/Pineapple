/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Prefab/UI/Fade.h>

namespace pa
{
	class Flash : public Object
	{
	public:
		Flash(World& world, int priority);
		~Flash();

		void flash(Time time, float intensity, Colour colour);

		virtual void onDestroy() override;
		virtual void onStep(Time deltaTime) override;

	private:
		enum class State
		{
			Idle,
			FadeIn,
			FadeOut
		};

		State m_state;

		Time m_time;
		float m_intensity;

		std::shared_ptr<Fade> m_fade;
	};
}
