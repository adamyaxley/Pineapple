/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <list>

namespace pa
{
	class Render;

	class RenderSystem
	{
	public:

		friend Render;

		using Handle = std::list<Render*>::const_iterator;

		void renderUnordered();
		void renderOrdered();

	private:

		Handle registerOrdered(Render* renderable);
		void unregisterOrdered(const Handle handle);

		Handle registerUnordered(Render* renderable);
		void unregisterUnordered(const Handle handle);

		std::list<Render*> m_unorderedList;
		std::list<Render*> m_orderedList;
	};
}
