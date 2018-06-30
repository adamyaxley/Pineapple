/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Container/Vect2.h>
#include <Pineapple/Engine/Graphics/Font.h>
#include <Pineapple/Engine/Graphics/Program.h>
#include <Pineapple/Engine/Graphics/Shader.h>
#include <Pineapple/Engine/Graphics/Texture.h>
#include <Pineapple/Engine/Graphics/TileSet.h>
#include <Pineapple/Engine/Platform/ResourceManager.h>
#include <Pineapple/Engine/Platform/FileSystem.h>
#include <memory>

namespace pa
{
	class Graphics;

	namespace MakeInternal
	{
		std::unique_ptr<Graphics> graphics(const PlatformSettings::Graphics& settings, const FileSystem& fileSystem);
	}

	class Graphics
	{
	public:
		enum class ResizeMode
		{
			Stretch,
			FillCenter,
			FillMin,
			FillMax,
			Fit
		};

		// Graphics engine start up and shut down
		Graphics(const pa::PlatformSettings::Graphics& settings, const FileSystem& fileSystem);
		virtual ~Graphics();

		// Get size
		PA_FORCE_INLINE const Vect2<int>& getProjectionPosition() const;
		PA_FORCE_INLINE const Vect2<int>& getSize() const;

		// Views
		PA_FORCE_INLINE Vect2<float>& getSpriteView();
		PA_FORCE_INLINE Vect2<float>& getMapView();
		PA_FORCE_INLINE Vect2<float>& getTextView();
		PA_FORCE_INLINE const Vect2<float>& getSpriteView() const;
		PA_FORCE_INLINE const Vect2<float>& getMapView() const;
		PA_FORCE_INLINE const Vect2<float>& getTextView() const;

		PA_FORCE_INLINE ResourceManager& getResourceManager();
		PA_FORCE_INLINE RenderSystem& getRenderSystem();

		PA_FORCE_INLINE void setDeferredProgram(Program* program);
		PA_FORCE_INLINE Program* getDeferredProgram();

		void resize(ResizeMode mode, const Vect2<int>& platformSize);
		void setProjection(int x, int y, int x2, int y2);

		// Resource loading
		virtual std::shared_ptr<Texture> createTexture(const char* path, FileStorage storage = FileStorage::UserAsset) = 0;
		virtual std::shared_ptr<TileSet> createTileSet(const char* path, int tileWidth, int tileHeight, FileStorage storage = FileStorage::UserAsset) = 0;
		virtual std::shared_ptr<Font> createFont(const char* path, FileStorage storage = FileStorage::UserAsset) = 0;
		std::unique_ptr<Sprite> createSprite(std::vector<std::shared_ptr<Texture>>& frames);

		// Creates a fragment shader
		virtual std::shared_ptr<Shader> createShader(ShaderType type, const char* path, FileStorage storage = FileStorage::UserAsset) = 0;
		virtual std::shared_ptr<Program> createProgram() = 0;

		virtual void render() = 0;

		// Viewport
		virtual void setViewport(int x, int y, int width, int height) = 0;

	protected:
		Vect2<int> m_projectionPosition;
		Vect2<int> m_size;
		const PlatformSettings::Graphics m_settings;

		ResourceManager m_resourceManager;

		RenderSystem m_renderSystem;

		Program* m_deferredProgram = nullptr;

		const FileSystem& m_fileSystem;

	private:
		Vect2<float> m_spriteView;
		Vect2<float> m_mapView;
		Vect2<float> m_textView;
	};
}

#include <Pineapple/Engine/Graphics/Graphics.inl>
