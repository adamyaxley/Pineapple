/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Graphics/OpenGL/FontGL.h>
#include <Pineapple/Graphics/OpenGL/GraphicsGL.h>
#include <Pineapple/Graphics/OpenGL/ProgramGL.h>
#include <Pineapple/Graphics/OpenGL/ShaderGL.h>
#include <Pineapple/Graphics/OpenGL/TextureFileGL.h>
#include <Pineapple/Graphics/OpenGL/TileSetGL.h>
#include <stdio.h>
#include <string.h>

// Fontstash
#define FONTSTASH_IMPLEMENTATION
#define FONS_SCRATCH_BUF_SIZE 128000
#define FONS_MAX_STATES 1
#include <Pineapple/Engine/Platform/Memory.h>
namespace
{
	void* fonsScratchFullBackup(size_t size, void* uptr)
	{
		pa::Log::info("Fons Scratch buffer full, allocating {} from the heap", size);
		return pa::Memory::allocate(size);
	}
}
#define FONS_SCRATCH_FULL_BACKUP(x, u) fonsScratchFullBackup(x, u)
#include <fontstash.h>
#define GLFONTSTASH_IMPLEMENTATION
#ifdef PA_OPENGLES1
#	include <glfontstash.h>
#else
#	include <gl3fontstash.h>
#endif

std::unique_ptr<pa::Graphics> pa::MakeInternal::graphics(const pa::PlatformSettings::Graphics& settings, const pa::FileSystem& fileSystem)
{
	return std::make_unique<pa::GraphicsGL>(settings, fileSystem);
}

namespace
{
	void handleFontstashError(void* uptr, int error, int val)
	{
		auto fs = (FONScontext*)uptr;

		pa::Log::info("Fontstash error: {}, val: {}", error, val);

		switch (error)
		{
		// Font atlas is full.
		case FONS_ATLAS_FULL:
		{
			int width, height;
			fonsGetAtlasSize(fs, &width, &height);
			if (width <= 1024 && height <= 1024)
			{
				width *= 2;
				height *= 2;
				pa::Log::info("Expanding atlas to {}*{}", width, height);
				fonsExpandAtlas(fs, width, height);
			}
			else
			{
				pa::Log::info("Atlas couldn't expand more than 1024*1024");
			}
			break;
		}
		// Scratch memory used to render glyphs is full, requested size reported in 'val', you may need to bump up
		// FONS_SCRATCH_BUF_SIZE.
		case FONS_SCRATCH_FULL:
		{
			PA_ASSERTF(false,
					   "Scratch buffer is full and the backup wasn't used for some reason, requested size is: {}, max "
					   "size is: {}",
					   val, FONS_SCRATCH_BUF_SIZE);
			break;
		}
		// Calls to fonsPushState has created too large stack, if you need deep state stack bump up FONS_MAX_STATES.
		case FONS_STATES_OVERFLOW:
		{
			PA_ASSERTF(false, "Calls to fonsPushState has created too large stack");
			break;
		}
		// Trying to pop too many states fonsPopState().
		case FONS_STATES_UNDERFLOW:
		{
			PA_ASSERTF(false, "Trying to pop too many states fonsPopState()");
			break;
		}
		default: break;
		}
	}
}

#ifdef GLAD_DEBUG
namespace
{
	void pa_glad_post_callback(const char *name, void *funcptr, int len_args, ...) {
		GLenum error_code;
		error_code = glad_glGetError();

		if (error_code != GL_NO_ERROR) {
			pa::Log::info("ERROR {} in {}", (int)error_code, name);
		}
	}
}
#endif

pa::GraphicsGL::GraphicsGL(const pa::PlatformSettings::Graphics& settings, const pa::FileSystem& fileSystem)
	: pa::Graphics(settings, fileSystem)
	, m_fonsContext(nullptr)
{
	pa::Log::info("Starting up graphics size: {} * {}", m_size.x, m_size.y);

#if !defined(PA_OPENGLES1)
	if (!gladLoadGL())
	{
		pa::Log::info("Failed to init GLAD");
		throw std::exception();
	}
	else
	{
		pa::Log::info("Successfully inited GLAD");
	}

	#ifdef GLAD_DEBUG
		glad_set_post_callback(pa_glad_post_callback);
	#endif
#endif

	initGL();
	ensureFonsContextIsCreated();
}

pa::GraphicsGL::~GraphicsGL()
{
#ifndef PA_OPENGLES1
	ensureDeferredResourcesAreDestroyed();
#endif
	ensureFonsContextIsDestroyed();
}

void pa::GraphicsGL::resume()
{
	initGL();
	resetFonsContext();
}

std::shared_ptr<pa::Texture> pa::GraphicsGL::createTexture(const char* path, pa::FileStorage storage)
{
	auto texture = std::make_shared<pa::TextureFileGL>(*this, pa::FilePath(m_fileSystem, storage, path));
	getResourceManager().add(texture);
	return texture;
}

std::shared_ptr<pa::TileSet> pa::GraphicsGL::createTileSet(const char* path, int tileWidth, int tileHeight, pa::FileStorage storage)
{
	auto tileSet = std::make_shared<pa::TileSetGL>(*this, tileWidth, tileHeight, pa::FilePath(m_fileSystem, storage, path));
	getResourceManager().add(tileSet);
	return tileSet;
}

std::shared_ptr<pa::Font> pa::GraphicsGL::createFont(const char* path, pa::FileStorage storage)
{
	auto font = std::make_shared<pa::FontGL>(*this, m_fonsContext, pa::FilePath(m_fileSystem, storage, path));
	getResourceManager().add(font);
	return font;
}

std::shared_ptr<pa::Shader> pa::GraphicsGL::createShader(pa::ShaderType type, const char* path, pa::FileStorage storage)
{
#ifndef PA_OPENGLES1
	auto shader = std::make_shared<pa::ShaderGL>(type, pa::FilePath(m_fileSystem, storage, path));
	getResourceManager().add(shader);
	return shader;
#else
	return nullptr;
#endif
}

std::shared_ptr<pa::Program> pa::GraphicsGL::createProgram()
{
#ifndef PA_OPENGLES1
	auto program = std::make_shared<pa::ProgramGL>();
	getResourceManager().addPlainDependency(program);
	return program;
#else
	return nullptr;
#endif
}

void pa::GraphicsGL::render()
{
// pa::Log::info("pa::Graphics begin");
#ifndef PA_OPENGLES1
	glUseProgram(0);
#endif

// Depth Buffer
#ifdef PA_OPENGLES1
	glClearDepthf(1.0f);
#else
	glClearDepth(1.0f);
#endif
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);

	// Clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	PA_GL_CHECK_ERROR();

#ifndef PA_OPENGLES1
	setupDeferredFrameBufferForRendering();
#endif

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

#ifdef PA_OPENGLES1
	glOrthof((GLfloat)m_projectionPosition.x, (GLfloat)m_size.x, (GLfloat)m_size.y, (GLfloat)m_projectionPosition.y,
			 -1000.0f, 1000.0f);
#else
	glOrtho((GLdouble)m_projectionPosition.x, (GLdouble)m_size.x, (GLdouble)m_size.y, (GLdouble)m_projectionPosition.y,
			-1000.0, 1000.0);
#endif

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	PA_GL_CHECK_ERROR();

	// Render all renderable items
	m_renderSystem.renderUnordered();
	m_renderSystem.renderOrdered();

#ifndef PA_OPENGLES1
	drawDeferredTexture();
#endif
}

void pa::GraphicsGL::setViewport(int x, int y, int width, int height)
{
	glViewport((GLint)x, (GLint)y, (GLint)width, (GLint)height);
}

#ifndef PA_OPENGLES1
void pa::GraphicsGL::ensureDeferredFrameBufferIsCreated()
{
	if (m_deferredFrameBuffer == 0)
	{
		glGenFramebuffers(1, &m_deferredFrameBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, m_deferredFrameBuffer);
		glViewport(0, 0, (GLsizei)m_size.x, (GLsizei)m_size.y);
	}
}

void pa::GraphicsGL::ensureDeferredTextureIsCreated()
{
	if (m_deferredTexture == 0)
	{
		// The texture we're going to render to
		glGenTextures(1, &m_deferredTexture);

		// "Bind" the newly created texture : all future texture functions will modify this texture
		glBindTexture(GL_TEXTURE_2D, m_deferredTexture);

		// Give an empty image to OpenGL ( the last "0" )
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_size.x, m_size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

		// Poor filtering. Needed !
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
}

void pa::GraphicsGL::ensureDeferredResourcesAreCreated()
{
	ensureDeferredFrameBufferIsCreated();
	ensureDeferredTextureIsCreated();
}

void pa::GraphicsGL::ensureDeferredResourcesAreDestroyed()
{
	if (m_deferredFrameBuffer != 0)
	{
		glDeleteBuffers(1, &m_deferredFrameBuffer);
	}

	if (m_deferredTexture != 0)
	{
		glDeleteTextures(1, &m_deferredTexture);
	}
}

void pa::GraphicsGL::setupDeferredFrameBufferForRendering()
{
	if (getDeferredProgram() != nullptr && getDeferredProgram()->isLinked())
	{
		ensureDeferredResourcesAreCreated();

		// Bind our buffer and set our deferred frame buffer as our colour attachement #0
		glBindFramebuffer(GL_FRAMEBUFFER, m_deferredFrameBuffer);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_deferredTexture, 0);
		PA_GL_CHECK_ERROR();

		// Set the list of draw buffers.
		GLenum drawBuffers[1] = {GL_COLOR_ATTACHMENT0};
		glDrawBuffers(1, drawBuffers);
		PA_GL_CHECK_ERROR();

		// Always check that our framebuffer is ok
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			pa::Log::info("Framebuffer status not complete: {}", glCheckFramebufferStatus(GL_FRAMEBUFFER));
			PA_ASSERTF(false, "");
		}
	}
}

void pa::GraphicsGL::drawDeferredTexture()
{
	if (getDeferredProgram() != nullptr && getDeferredProgram()->isLinked())
	{
		// Render buffered texture (happens in fragment shader)
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, (GLsizei)m_size.x, (GLsizei)m_size.y);

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		getDeferredProgram()->use();

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_deferredTexture);

		// Set our "pa_FrameTexture" sampler to user Texture Unit 0
		getDeferredProgram()->setUniformInt("pa_FrameTexture", 0);

		// The fullscreen quad's FBO
		const GLfloat g_quad_vertex_buffer_data[] = {
			// <todo> may need to be static
			-1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, -1.0f, 1.0f, 0.0f,
			-1.0f, 1.0f,  0.0f, 1.0f, -1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
		};

		GLuint quad_vertexbuffer;
		glGenBuffers(1, &quad_vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);
		PA_GL_CHECK_ERROR();

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
		glVertexAttribPointer(0, // attribute 0. No particular reason for 0, but must match the layout in the shader.
							  3, // size
							  GL_FLOAT, // type
							  GL_FALSE, // normalized?
							  0,		// stride
							  (void*)0  // array buffer offset
							  );

		// Draw the triangles !
		glDrawArrays(GL_TRIANGLES, 0, 6); // 2*3 indices starting at 0 -> 2 triangles

		glDisableVertexAttribArray(0);

		glUseProgram(0);
		PA_GL_CHECK_ERROR();
	}
}
#endif

void pa::GraphicsGL::initGL()
{
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);

	// Maps use Triangle Strips, so this is needed to remove 2 backwards triangles at the end of each row of a map
	glEnable(GL_CULL_FACE);

	glShadeModel(GL_SMOOTH);
	glClearColor((GLclampf)0.0, (GLclampf)0.0, (GLclampf)0.0, (GLclampf)1.0);
	setViewport(0, 0, (GLfloat)m_settings.size.x * (GLfloat)m_settings.zoom, (GLfloat)m_settings.size.y * (GLfloat)m_settings.zoom);
	PA_GL_CHECK_ERROR();
}

void pa::GraphicsGL::ensureFonsContextIsCreated()
{
	if (!m_fonsContext)
	{
#ifdef PA_OPENGLES1
		m_fonsContext = glfonsCreate(128, 128, FONS_ZERO_TOPLEFT);
#else
		m_fonsContext = gl3fonsCreate(128, 128, FONS_ZERO_TOPLEFT);
#endif
		fonsSetErrorCallback(m_fonsContext, handleFontstashError, m_fonsContext);
	}
}

void pa::GraphicsGL::ensureFonsContextIsDestroyed()
{
	if (m_fonsContext)
	{
#ifdef PA_OPENGLES1
		glfonsDelete(m_fonsContext);
#else
		gl3fonsDelete(m_fonsContext);
#endif
		m_fonsContext = nullptr;
	}
}

void pa::GraphicsGL::resetFonsContext()
{
	fonsResetAtlas(m_fonsContext, 128, 128);
}