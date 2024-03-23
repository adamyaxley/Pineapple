#include <Pineapple/Platform/Android/AndroidEngine.h>
#include <Pineapple/Engine/Platform/Log.h>

#ifdef PA_ANDROID_SWAPPY
#    include <swappy/swappyGL.h>
#endif

pa::AndroidEngine::AndroidEngine() :
	m_app(NULL),
	//m_sensorManager(NULL),
	//m_accelerometerSensor(NULL),
	//m_sensorEventQueue(NULL),
	m_hasWindow(false),
	m_hasFocus(false),
	m_surfaceSize(0, 0),
	m_hasInitialised(false),
	m_display(EGL_NO_DISPLAY),
	m_surface(EGL_NO_SURFACE),
	m_context(EGL_NO_CONTEXT),
	m_config(NULL)
{}

pa::AndroidEngine::~AndroidEngine()
{}

void pa::AndroidEngine::setApp(android_app* state)
{
	// TODO do I need to re-initialise here?
	m_app = state;
}

bool pa::AndroidEngine::createDisplay()
{
	if (EGL_NO_DISPLAY == m_display)
	{
		// initialize OpenGL ES and EGL

		/*
		* Here specify the attributes of the desired configuration.
		* Below, we select an EGLConfig with at least 8 bits per color
		* component compatible with on-screen windows
		*/
		pa::Log::info("Creating display");

		const EGLint attribs[] =
		{
			EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
			EGL_BLUE_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_RED_SIZE, 8,
			EGL_DEPTH_SIZE, 16,
			EGL_NONE
		};

		m_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

		if (EGL_NO_DISPLAY == m_display)
		{
			pa::Log::info("Failed to get display");
			return false;
		}

		EGLint major = 0, minor = 0;

		if (eglInitialize(m_display, &major, &minor) == EGL_TRUE)
		{
			pa::Log::info("Initialized EGL {}.{}", major, minor);
		}
		else
		{
			pa::Log::info("Failed to initialize EGL {}.{}", major, minor);
			return false;
		}

		/* Here, the application chooses the configuration it desires. In this
		* sample, we have a very simplified selection process, where we pick
		* the first EGLConfig that matches our criteria */
		EGLint numConfigs;
		if (eglChooseConfig(m_display, attribs, &m_config, 1, &numConfigs) == EGL_TRUE)
		{
			EGLint red, green, blue, alpha, depth, samples, sampleBuffers;

			// Read the config we got
			eglGetConfigAttrib(m_display, m_config, EGL_RED_SIZE, &red);
			eglGetConfigAttrib(m_display, m_config, EGL_BLUE_SIZE, &blue);
			eglGetConfigAttrib(m_display, m_config, EGL_GREEN_SIZE, &green);
			eglGetConfigAttrib(m_display, m_config, EGL_ALPHA_SIZE, &alpha);
			eglGetConfigAttrib(m_display, m_config, EGL_DEPTH_SIZE, &depth);
			eglGetConfigAttrib(m_display, m_config, EGL_SAMPLES, &samples);
			eglGetConfigAttrib(m_display, m_config, EGL_SAMPLE_BUFFERS, &sampleBuffers);

			pa::Log::info("Chosen EGL config: (RGBA: {} {} {} {} Z: {} AA: {} ({} buffers)", red, green, blue, alpha, depth, samples, sampleBuffers);
		}
		else
		{
			pa::Log::info("Failed to choose EGL config");
			return false;
		}

		/* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
		* guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
		* As soon as we picked a EGLConfig, we can safely reconfigure the
		* ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
		EGLint format;
		if (eglGetConfigAttrib(m_display, m_config, EGL_NATIVE_VISUAL_ID, &format) == EGL_TRUE)
		{
			pa::Log::info("Acquired config attribute EGL_NATIVE_VISUAL_ID successfully");
		}
		else
		{
			pa::Log::info("Failed to get config attribute EGL_NATIVE_VISUAL_ID");
			return false;
		}

		// Leave this commented out for now so it crashes and restarts (otherwise will just crash later and not restart)
		/*if (m_app->window == nullptr)
		{
		pa::Log::info("Error: window is NULL");
		return false;
		}*/

		if (ANativeWindow_setBuffersGeometry(m_app->window, 0, 0, format) >= 0)
		{
			pa::Log::info("Set the buffers geometry");
		}
		else
		{
			pa::Log::info("Failed to set the buffers geometry");
			return false;
		}
	}

	return true;
}

bool pa::AndroidEngine::createSurface()
{
	if (EGL_NO_SURFACE == m_surface)
	{
		pa::Log::info("Creating surface");
		m_surface = eglCreateWindowSurface(m_display, m_config, m_app->window, NULL);

#ifdef PA_ANDROID_SWAPPY
		SwappyGL_setWindow(m_app->window);
#endif

		if (eglQuerySurface(m_display, m_surface, EGL_WIDTH, &m_surfaceSize.x) == EGL_TRUE &&
			eglQuerySurface(m_display, m_surface, EGL_HEIGHT, &m_surfaceSize.y) == EGL_TRUE)
		{
			pa::Log::info("Surface size: {} * {}", m_surfaceSize.x, m_surfaceSize.y);
		}
		else
		{
			pa::Log::info("Failed to get the size of the surface");
			m_surfaceSize.set(0, 0);
			return false;
		}
	}
	else
	{
		pa::Log::info("Skipping creation of surface since one already exists");
	}

	return true;
}

bool pa::AndroidEngine::createContext()
{
	if (EGL_NO_CONTEXT == m_context)
	{
		pa::Log::info("Creating context");

		m_context = eglCreateContext(m_display, m_config, NULL, NULL);

		if (eglMakeCurrent(m_display, m_surface, m_surface, m_context) == EGL_TRUE)
		{
			pa::Log::info("Successfully created the context");
		}
		else
		{
			pa::Log::info("Failed to make the context current");
			return false;
		}
	}
	else
	{
		pa::Log::info("Skipping creation of context since one already exists");
	}

	return true;
}

bool pa::AndroidEngine::destroyDisplay()
{
	if (m_display != EGL_NO_DISPLAY)
	{
		eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

		if (eglTerminate(m_display))
		{
			m_display = EGL_NO_DISPLAY;
			pa::Log::info("Successfully terminated EGL");
		}
		else
		{
			pa::Log::info("Failed to terminate EGL");
			return false;
		}
	}

	return true;
}

bool pa::AndroidEngine::destroySurface()
{
	if (m_surface != EGL_NO_SURFACE)
	{
		if (eglDestroySurface(m_display, m_surface))
		{
			m_surface = EGL_NO_SURFACE;
			pa::Log::info("Successfully destroyed the surface");
			m_surfaceSize.set(0, 0);
		}
		else
		{
			pa::Log::info("Failed to destroy the surface");
			return false;
		}

#ifdef PA_ANDROID_SWAPPY
		SwappyGL_setWindow(nullptr);
#endif
	}

	return true;
}

bool pa::AndroidEngine::destroyContext()
{
	//eglMakeCurrent(m_display, m_surface, m_surface, EGL_NO_CONTEXT);

	if (m_context != EGL_NO_CONTEXT)
	{
		if (eglDestroyContext(m_display, m_context))
		{
			m_context = EGL_NO_CONTEXT;
			pa::Log::info("Successfully destroyed the context");
		}
		else
		{
			pa::Log::info("Failed to destroy the context");
			return false;
		}
	}

	return true;
}

void pa::AndroidEngine::clearBuffer()
{
	if (m_display != EGL_NO_DISPLAY && m_context != EGL_NO_CONTEXT)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		swapBuffers();
	}
}

void pa::AndroidEngine::swapBuffers()
{
	if (m_display != EGL_NO_DISPLAY && m_surface != EGL_NO_SURFACE)
	{
#ifdef PA_ANDROID_SWAPPY
		SwappyGL_swap(m_display, m_surface);
#else
		eglSwapBuffers(m_display, m_surface);
#endif
	}
}

bool pa::AndroidEngine::getHasWindow() const
{
	return (EGL_NO_DISPLAY != m_display);
}

void pa::AndroidEngine::setHasFocus(bool state)
{
	m_hasFocus = state;
}

bool pa::AndroidEngine::isAnimating()
{
	return m_hasFocus;
}

bool pa::AndroidEngine::isLandscapeMode()
{
	/*if (m_app != NULL && m_app->window != NULL)
	{
		pa::Log::info("Engine Surface size: ({}, {}) Window size: ({}, {})", getSurfaceSize().x, getSurfaceSize().y, ANativeWindow_getWidth(m_app->window), ANativeWindow_getHeight(m_app->window));
		return
			(getSurfaceSize().x == ANativeWindow_getWidth(m_app->window)) &&
			(getSurfaceSize().y == ANativeWindow_getHeight(m_app->window));
	}
	else
	{
		return false;
	}*/
	return (m_surfaceSize.x != 0 && m_surfaceSize.y != 0 && m_surfaceSize.x > m_surfaceSize.y);
}
