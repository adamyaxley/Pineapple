/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Graphics/Graphics.h>
#include <Pineapple/Engine/Graphics/Map.h>
#include <Pineapple/Engine/Graphics/TileMap.h>
#include <Pineapple/Graphics/OpenGL/TileSetGL.h>
#include <Pineapple/Graphics/OpenGL/VertexBuffer2DGL.h>

namespace pa
{
	class MapGL : public Map
	{
	public:
		MapGL(Graphics& graphics, TileSetGL& tileSet, float x, float y, const TileMap map, bool hWrap, bool vWrap,
			  int priority);
		~MapGL();

		virtual void onDependencyNotify(Dependency* parent) override;

		void createVertexBuffer();

		bool setup();
		virtual void render() override;

	private:
		const Graphics& m_graphics;

		TileSetGL& m_tileSet;
		const TileMap m_tileMap;

		Vect2<int> m_scrollPos;

		VertexBuffer2DGL m_vertexBuffer;

		Dependency::Handle m_dependencyNode;

		void drawMap(Vect2<float> pos, const VertexBuffer2DGL& buffer) const;
		void drawHWrappedMap(Vect2<float> pos, const VertexBuffer2DGL& buffer) const;
		void drawVWrappedMap(Vect2<float> pos, const VertexBuffer2DGL& buffer) const;
		void drawHVWrappedMap(Vect2<float> pos, const VertexBuffer2DGL& buffer) const;
	};
}
