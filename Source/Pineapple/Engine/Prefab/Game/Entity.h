/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Graphics/Sprite.h>
#include <Pineapple/Engine/Physics/AABB.h>
#include <Pineapple/Engine/Physics/Particle.h>
#include <Pineapple/Engine/System/Object.h>
#include <memory>

namespace pa
{
	class Entity : public Object, public Particle
	{
	public:
		Entity(World& world);

		void updatePhysics(Time deltaTime);
		void updateSprite();

		std::shared_ptr<Sprite> getSprite();
		const std::shared_ptr<Sprite> getSprite() const;
		void setSprite(std::shared_ptr<Sprite> sprite);

		const AABB& getAABB() const;
		AABB& getAABB();

		void setAABBSizeFromSprite();

#ifdef PA_DEBUG
		void enableDebugAABB();
		void disableDebugAABB();
#endif

		virtual void onStep(Time deltaTime) override;

	private:
		AABB m_aabb;

		std::shared_ptr<Sprite> m_sprite;

#ifdef PA_DEBUG
		std::unique_ptr<Sprite> m_aabbDebug;
#endif
	};
}
