/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Container/Vect2.h>
#include <Pineapple/Engine/Graphics/Graphics.h>
#include <Pineapple/Engine/Graphics/Texture.h>
#include <Pineapple/Graphics/OpenGL/IncludeGL.h>
#include <Pineapple/Graphics/OpenGL/TextureCoordsGL.h>

namespace pa
{
	class TextureGL : public Texture
	{
	public:
		TextureGL(Graphics& graphics, const char* path);
		~TextureGL();

		// Creates a new OpenGL sprite from this texture
		virtual std::unique_ptr<Sprite> createSprite() override;

		virtual Texture* createTexture(int x, int y, int width, int height) override;

		// Gets the OpenGL texture object associated with this tile set
		GLuint getGLObject() const;

		const TextureCoordsGL& getTextureCoords() const;

	protected:
		void setGLObject(GLuint id);

		void setTextureCoords(float x1, float y1, float x2, float y2);

	private:
		Graphics& m_graphics;

		GLuint m_id;

		TextureCoordsGL m_textureCoords;

		std::vector<std::unique_ptr<pa::Texture>> m_subTextures;
	};
}
