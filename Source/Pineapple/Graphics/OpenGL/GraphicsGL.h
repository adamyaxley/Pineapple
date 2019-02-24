/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Graphics/Graphics.h>
#include <Pineapple/Graphics/OpenGL/IncludeGL.h>

struct FONScontext;

namespace pa
{
	class GraphicsGL : public Graphics
	{
	public:
		GraphicsGL(const PlatformSettings::Graphics& settings, const FileSystem& fileSystem);
		virtual ~GraphicsGL();

		virtual void resume() override;

		// Resource loading
		virtual std::shared_ptr<Texture> createTexture(const char* path, FileStorage storage) override;
		virtual std::shared_ptr<TileSet> createTileSet(const char* path, int tileWidth, int tileHeight, FileStorage storage) override;
		virtual std::shared_ptr<Font> createFont(const char* path, FileStorage storage) override;

		// Creates a fragment shader
		virtual std::shared_ptr<Shader> createShader(ShaderType type, const char* path, FileStorage storage) override;
		virtual std::shared_ptr<Program> createProgram() override;

		virtual void render() override;

		// Viewport
		virtual void setViewport(int x, int y, int width, int height) override;

		FONScontext* getFonsContext()
		{
			return m_fonsContext;
		};

	private:
#ifndef PA_OPENGLES1
		void ensureDeferredFrameBufferIsCreated();
		void ensureDeferredTextureIsCreated();
		void ensureDeferredResourcesAreCreated();
		void ensureDeferredResourcesAreDestroyed();
		void setupDeferredFrameBufferForRendering();
		void drawDeferredTexture();

		GLuint m_deferredFrameBuffer = 0;
		GLuint m_deferredTexture = 0;
#endif
		void initGL();

		void ensureFonsContextIsCreated();
		void ensureFonsContextIsDestroyed();
		void resetFonsContext();
		FONScontext* m_fonsContext;
	};
}
