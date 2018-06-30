#pragma once

#include <android_native_app_glue.h>
#include <Pineapple/Engine/Container/Vect2.h>

#include <EGL/egl.h>
#include <GLES/gl.h>

#include <android/sensor.h>
#include <android/log.h>


namespace pa
{
	class AndroidEngine
	{
	public:
		AndroidEngine();
		~AndroidEngine();

		void setApp(android_app* state);
		android_app* getApp() { return m_app; }

		bool hasInitialised() { return m_hasInitialised; }
		void initialise() { m_hasInitialised = true; }

		bool createDisplay();
		bool createSurface();
		bool createContext();
		bool destroyDisplay();
		bool destroySurface();
		bool destroyContext();

		bool isLandscapeMode();

		void clearBuffer();
		void swapBuffers();

		const Vect2<int>& getSurfaceSize() { return m_surfaceSize; }

		void setHasWindow(bool state);
		bool getHasWindow() const;
		void setHasFocus(bool state);
		bool isAnimating();

	private:
		android_app * m_app;

		/*ASensorManager* m_sensorManager;
		ASensor* m_accelerometerSensor;
		ASensorEventQueue* m_sensorEventQueue;*/

		bool m_hasWindow;
		bool m_hasFocus;
		Vect2<int> m_surfaceSize;

		bool m_hasInitialised;
		//SavedState m_state;

		EGLDisplay m_display;
		EGLSurface m_surface;
		EGLContext m_context;
		EGLConfig m_config;
	};
}

