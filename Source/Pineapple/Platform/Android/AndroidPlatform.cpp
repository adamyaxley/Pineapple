#include <Pineapple/Platform/Android/AndroidPlatform.h>
#include <Pineapple/Platform/Android/AndroidUtil.h>
#include <Pineapple/Platform/Android/AndroidBridge.h>
#include <android/sensor.h>
#include <memory>

std::shared_ptr<pa::Platform> pa::Make::platform(pa::Arguments* arguments, const pa::PlatformSettings& settings)
{
	auto androidArguments = static_cast<pa::AndroidArguments*>(arguments);
	return std::make_shared<pa::AndroidPlatform>(androidArguments, settings);
}

bool g_enteredAndroidMain = false;

extern "C"
{
	void android_main(struct android_app* state)
	{
		pa::Log::info("Entered android_main");

		pa::AndroidBridge::setAndroidApp(state);

		// Make sure glue isn't stripped
		app_dummy(); //No longer necessary https://github.com/android-ndk/ndk/issues/381

		if (!g_enteredAndroidMain)
		{
			g_enteredAndroidMain = true;

			auto arguments = std::make_unique<pa::AndroidArguments>(state);

			pa::Log::info("Entering main");
			pa::Main(arguments.get());
		}
		else
		{
			pa::Log::info("Ignoring second android_main entry");
		}

		pa::Log::info("Finishing activity in android_main");

		ANativeActivity_finish(state->activity);

		pa::Log::info("Leaving android_main");
		g_enteredAndroidMain = false;
	}
}

namespace
{
	int32_t onInputEvent(android_app* app, AInputEvent* inputEvent)
	{
		auto platform = static_cast<pa::AndroidPlatform*>(app->userData);
		return platform->handleInputEvent(app, inputEvent);
	}

	void onAppCmd(struct android_app* app, int32_t cmd)
	{
		auto platform = static_cast<pa::AndroidPlatform*>(app->userData);
		platform->handleAppCommand(app, cmd);
	}
}

pa::AndroidPlatform::AndroidPlatform(pa::AndroidArguments* arguments, const pa::PlatformSettings& settings)
	: pa::Platform(settings)
	, m_setPointerUpOnNextStep(false)
{
	auto state = arguments->getState();
	state->userData = this;
	state->onInputEvent = onInputEvent;
	state->onAppCmd = onAppCmd;
	m_engine.setApp(state);

	m_fileSystem = pa::MakeInternal::fileSystem(settings.fileSystem);

	// Unique pointers
	/*if (settings.graphics.use)
	{
		m_graphics = pa::MakeInternal::graphics(settings.graphics, *m_fileSystem.get());
	}*/

	if (settings.sound.use)
	{
		m_sound = pa::MakeInternal::sound(*m_fileSystem.get());
	}

	// Wait until the display has been initialised
	pollEvents();

	//getGraphics()->resizeKeepAspectRatio(width, height);

	//m_engine.setPlatformSize(settings.graphics.size);
	m_engine.initialise();
}

pa::AndroidPlatform::~AndroidPlatform()
{
	m_engine.setHasFocus(false);

	m_sound.reset();
	m_graphics.reset();
	m_fileSystem.reset();

	// Need to keep polling for events until destroy thing is seen
	pollEvents();
}

void pa::AndroidPlatform::idle()
{
	if (getSound())
	{
		getSound()->update();
	}

	if (getGraphics())
	{
		getGraphics()->render();
		m_engine.swapBuffers();
	}
}

// Get input from user
void pa::AndroidPlatform::pollEvents()
{
	m_input.events.clear();

	int timeout = m_engine.isAnimating() ? 0 : -1;
	bool waitingForEvents = true;

	if (m_setPointerUpOnNextStep)
	{
		m_pointer.setDown(false);
		m_setPointerUpOnNextStep = false;
	}

	while (waitingForEvents)
	{
		int events;
		struct android_poll_source* source;

		/*int id = */ALooper_pollAll(timeout, NULL, &events, (void**)&source);

		/*if (id < 0)
		{
		// Handle error?
		}*/

		// Process this event.
		if (source != NULL)
		{
			source->process(m_engine.getApp(), source);
		}

		// Check if we are exiting.
		if (m_engine.getApp()->destroyRequested != 0) // TODO: tear down everything
		{
			//handleCommand(m_engine.getApp(), APP_CMD_TERM_WINDOW);
			pa::Log::info("Destroy Requested");
			return;
		}

		// Wait until the app has focus again
		waitingForEvents = !m_engine.isAnimating();
		timeout = -1;

		// If a sensor has data, process it now.
		/*if (ident == LOOPER_ID_USER)
		{
		if (engine.accelerometerSensor != NULL)
		{
		ASensorEvent event;
		while (ASensorEventQueue_getEvents(engine.sensorEventQueue,
		&event, 1) > 0) {
		LOGI("accelerometer: x=%f y=%f z=%f",
		event.acceleration.x, event.acceleration.y,
		event.acceleration.z);
		}
		}
		}*/
	}

	std::copy(m_otherEvents.begin(), m_otherEvents.end(), std::back_inserter(m_input.events));
	m_otherEvents.clear();
}

void pa::AndroidPlatform::openUrl(const char* url)
{
	pa::AndroidUtil util;
	util.openUrl(url);
}

void pa::AndroidPlatform::resendWindowAppCommands()
{
	// http://stackoverflow.com/questions/12702868/how-to-force-landscape-mode-with-ndk-using-pure-c-codes?rq=1
	pa::Log::info("Re initialising because the config has changed");
	handleAppCommand(m_engine.getApp(), APP_CMD_TERM_WINDOW);
	handleAppCommand(m_engine.getApp(), APP_CMD_INIT_WINDOW);
}

int32_t pa::AndroidPlatform::handleInputEvent(android_app* app, AInputEvent* inputEvent)
{
	if (AInputEvent_getType(inputEvent) == AINPUT_EVENT_TYPE_MOTION)
	{
		int32_t actionFlags = AMotionEvent_getAction(inputEvent);
		int action = actionFlags & AMOTION_EVENT_ACTION_MASK;

		switch (action)
		{
			//case AMOTION_EVENT_ACTION_POINTER_DOWN:
		case AMOTION_EVENT_ACTION_DOWN:
		{
			m_pointer.setDown(true);
			pa::Log::info("Touch detected");
			// Fall through to next case below to get co-ordinates
		}
		case AMOTION_EVENT_ACTION_MOVE:
		{
			float x = AMotionEvent_getX(inputEvent, 0);
			float y = AMotionEvent_getY(inputEvent, 0);

			// Scale values in case we have a window which is smaller than the platform resolution
			x *= (float)m_graphics->getSize().x / (float)m_engine.getSurfaceSize().x;
			y *= (float)m_graphics->getSize().y / (float)m_engine.getSurfaceSize().y;

			m_pointer.setPosition(x, y);
			break;
		}
		//case AMOTION_EVENT_ACTION_POINTER_UP:
		case AMOTION_EVENT_ACTION_UP:
		{
			m_setPointerUpOnNextStep = true;
			//int index = (actionFlags & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT; 
			//int pid = AMotionEvent_getPointerId(inputEvent, index); 

			break;
		}
		}

		return 1;
		// ADD KEYDOWN UP ETC HERE FOR TOUCH (extra events?)
	}
	else if (AKeyEvent_getKeyCode(inputEvent) == AKEYCODE_BACK)
	{
		// actions on back key
		pa::Event backEvent;
		backEvent.type = pa::Event::Type::KeyPress;
		backEvent.key = pa::Key::Back;
		m_otherEvents.push_back(backEvent);
		return 1; // prevent default handler (exit)
	}
	return 0;
}

void pa::AndroidPlatform::handleAppCommand(struct android_app* app, int32_t cmd)
{
	switch (cmd)
	{
	case APP_CMD_INIT_WINDOW:
		pa::Log::info("APP_CMD_INIT_WINDOW");
		if (!m_engine.createDisplay())
		{
			pa::Log::info("Failed to create the display");
		}
		if (!m_engine.createSurface())
		{
			pa::Log::info("Failed to create the surface");
		}
		if (!m_engine.createContext())
		{
			pa::Log::info("Failed to create the context");
		}

		// Now check that the surface we created is correct
		if (m_engine.getSurfaceSize().x < m_engine.getSurfaceSize().y)
		{
			// Portrait, not what we want
			pa::Log::info("Detected portrait mode, terminating and waiting for landscape");
			m_engine.destroyContext();
			m_engine.destroySurface();
			m_engine.destroyDisplay();
		}
		else
		{
			// Set up graphics
			m_graphics = pa::MakeInternal::graphics(m_settings.graphics, *m_fileSystem.get());

			//if (m_engine.hasInitialised())
			{
				// Restore platform size if we are resuming the app
				getGraphics()->resize(pa::Graphics::ResizeMode::FillMin, m_engine.getSurfaceSize()); // TODO set this from graphics setting
			}
			getGraphics()->getResourceManager().restoreState();
			m_engine.setHasWindow(true); // Set that we have got the correct window
		}
		break;
	case APP_CMD_TERM_WINDOW:
		pa::Log::info("APP_CMD_TERM_WINDOW");
		if (!m_engine.getHasWindow())
		{
			// This can happen if we throw away the window if it starts up in an orientation that we hate
			pa::Log::info("Ignoring terminate window command because there is no window");
		}
		else
		{
			getGraphics()->getResourceManager().saveState();
			getGraphics()->getResourceManager().unloadAll();
			m_engine.destroyContext();
			m_engine.destroySurface();
			m_engine.destroyDisplay();
			m_engine.setHasWindow(false);
		}
		break;
	case APP_CMD_GAINED_FOCUS:
		pa::Log::info("APP_CMD_GAINED_FOCUS");
		break;
	case APP_CMD_LOST_FOCUS:
		pa::Log::info("APP_CMD_LOST_FOCUS");
		break;
	case APP_CMD_START:
		pa::Log::info("APP_CMD_START");
		break;
	case APP_CMD_RESUME:
		pa::Log::info("APP_CMD_RESUME");
		getSound()->resumeMusic();
		m_engine.setHasFocus(true);
		break;
	case APP_CMD_SAVE_STATE:
		pa::Log::info("APP_CMD_SAVE_STATE");
		break;
	case APP_CMD_PAUSE:
		pa::Log::info("APP_CMD_PAUSE");
		getSound()->pauseMusic();
		m_engine.setHasFocus(false);
		break;
	case APP_CMD_STOP:
		pa::Log::info("APP_CMD_STOP");
		break;
	case APP_CMD_DESTROY:
		pa::Log::info("APP_CMD_DESTROY");
		getGraphics()->getResourceManager().unloadAll();
		getSound()->getResourceManager().unloadAll();
		m_engine.destroyContext();
		m_engine.destroySurface();
		m_engine.destroyDisplay();
		break;
	case APP_CMD_CONFIG_CHANGED:
		pa::Log::info("APP_CMD_CONFIG_CHANGED");
		//if (!m_engine.isLandscapeMode())
		if (m_engine.getSurfaceSize().x < m_engine.getSurfaceSize().y) // We are in portrait
		{
			//sleep(100);
			//m_engine.clearBuffer();
			resendWindowAppCommands();
		}
		break;
	}
}