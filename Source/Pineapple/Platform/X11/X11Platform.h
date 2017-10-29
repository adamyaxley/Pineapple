/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Platform/Platform.h>
#include <Pineapple/Platform/X11/X11Key.h>
#include <GL/glx.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <vector>

namespace pa
{
	class X11Platform : public Platform
	{
	public:
		X11Platform(Arguments* arguments, const PlatformSettings& settings);
		virtual ~X11Platform();

		// Idle
		virtual void idle() override;

		// Set full screen mode
		virtual void setFullScreen(bool fullscreen) override;

		// Get input from user
		virtual void pollEvents() override;

		// Intent
		virtual void openUrl(const char* url) override;

	private:
		void keyDown(Key key);
		void keyUp(Key key);

		std::vector<Event> m_otherEvents;

		// window information
		Display* m_dpy;
		Window m_win;
		XVisualInfo* m_vi;

		// context
		GLXContext m_glc;
	};
}
