/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Graphics/RenderSystem.h>

namespace pa
{
	class Render
	{
	public:
		enum class Type
		{
			Unordered,
			Ordered
		};

		Render(RenderSystem& renderSystem, pa::Render::Type renderType, int priority);
		~Render();

		int getPriority() const;
		void setPriority(int priority);

		virtual void render() = 0;

	private:
		RenderSystem& m_renderSystem;

		RenderSystem::Handle m_handle;

		const pa::Render::Type m_renderType;
		int m_priority;
	};
}
