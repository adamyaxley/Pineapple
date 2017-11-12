/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Platform/X11/X11Platform.h>
#include <algorithm>

std::shared_ptr<pa::Platform> pa::Make::platform(pa::Arguments* arguments, const pa::PlatformSettings& settings)
{
	return std::make_shared<pa::X11Platform>(arguments, settings);
}

int main()
{
	auto arguments = std::make_unique<pa::Arguments>();
	return pa::Main(arguments.get());
}

pa::X11Platform::X11Platform(pa::Arguments* arguments, const PlatformSettings& settings)
	: pa::Platform(settings)
	, m_dpy(nullptr)
{
	m_size = settings.graphics.size;

	Window root;
	XSetWindowAttributes swa;
	Colormap cmap;
	int att[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};

	m_dpy = XOpenDisplay(0);
	PA_ASSERTF(m_dpy, "Failed to open display");

	root = DefaultRootWindow(m_dpy);

	m_vi = glXChooseVisual(m_dpy, DefaultScreen(m_dpy), att);
	PA_ASSERTF(m_vi, "Failed to choose visual");

	cmap = XCreateColormap(m_dpy, root, m_vi->visual, AllocNone);

	swa.colormap = cmap;
	swa.event_mask =
		ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | FocusChangeMask;

	// pa::Log::info("XCreateWindow({},{},{},{},{},{},{},{},{},{},{},{})", (uintptr_t)m_dpy, root, 0, 0, this->m_size.x,
	// this->m_size.y, 0, m_vi->depth, (int)InputOutput, (uintptr_t)m_vi->visual, (int)(CWColormap | CWEventMask),
	// (uintptr_t)(&swa));
	m_win = XCreateWindow(m_dpy, root, 0, 0, this->m_size.x, this->m_size.y, 0, m_vi->depth, InputOutput, m_vi->visual,
						  CWColormap | CWEventMask, &swa);

	XFreeColormap(m_dpy, cmap);
	XMapWindow(m_dpy, m_win);
	XAutoRepeatOff(m_dpy);
	XStoreName(m_dpy, m_win, settings.title);

	// Set up close event
	Atom wmDelete = XInternAtom(m_dpy, "WM_DELETE_WINDOW", True);
	XSetWMProtocols(m_dpy, m_win, &wmDelete, 1);

	// Set up OpenGL context
	m_glc = glXCreateContext(m_dpy, m_vi, 0, GL_TRUE);
	glXMakeCurrent(m_dpy, m_win, m_glc);

	m_fileSystem = pa::MakeInternal::fileSystem(settings.fileSystem);

	// Unique pointers
	if (settings.graphics.use)
	{
		m_graphics = pa::MakeInternal::graphics(settings.graphics.size);
	}

	if (settings.sound.use)
	{
		m_sound = pa::MakeInternal::sound();
	}
}

pa::X11Platform::~X11Platform()
{
	m_sound.reset();
	m_graphics.reset();
	m_fileSystem.reset();

	if (m_dpy)
	{
		// Turn auto repeat back on
		XAutoRepeatOn(m_dpy);

		// Destroy Window
		XUnmapWindow(m_dpy, m_win);
		XDestroyWindow(m_dpy, m_win);

		// Destroy Context
		glXMakeCurrent(m_dpy, None, 0);
		glXDestroyContext(m_dpy, m_glc);

		// Close Display
		XFree(m_vi);
		XCloseDisplay(m_dpy);
	}
}

void pa::X11Platform::idle()
{
	if (getSound())
	{
		getSound()->update();
	}

	if (getGraphics())
	{
		getGraphics()->render();
		glXSwapBuffers(m_dpy, m_win);
	}
}

void pa::X11Platform::setFullScreen(bool fullscreen)
{
	XEvent xev;
	Atom wm_state = XInternAtom(m_dpy, "_NET_WM_STATE", False);
	Atom fullscreenAtom = XInternAtom(m_dpy, "_NET_WM_STATE_FULLSCREEN", False);

	memset(&xev, 0, sizeof(xev));
	xev.type = ClientMessage;
	xev.xclient.window = m_win;
	xev.xclient.message_type = wm_state;
	xev.xclient.format = 32;
	xev.xclient.data.l[0] = (int)fullscreen;
	xev.xclient.data.l[1] = fullscreenAtom;
	xev.xclient.data.l[2] = 0;

	XSendEvent(m_dpy, DefaultRootWindow(m_dpy), False, SubstructureNotifyMask, &xev);

#if 0
	if (fullscreen)
	{
		XWindowAttributes xwa;
		XGetWindowAttributes(m_dpy, DefaultRootWindow(m_dpy), &xwa);
		windowSize.x = xwa.width;
		windowSize.y = xwa.height;
	}
	else
	{
		windowSize = getSize();
	}
#endif
}

void pa::X11Platform::pollEvents()
{
	m_input.events.clear();

	while (XPending(m_dpy) > 0)
	{
		// Get next event
		XEvent xev;
		XNextEvent(m_dpy, &xev);

		Event e;
		bool addEvent = true;
		KeySym keySym;

		switch (xev.type)
		{
		case KeyPress:
#undef KeyPress
			keySym = XLookupKeysym(&xev.xkey, 0);
			addEvent = lookupX11Key(keySym, e.key);
			if (addEvent)
			{
				e.type = pa::Event::Type::KeyPress;
				keyDown(e.key);
			}
			break;

		case KeyRelease:
#undef KeyRelease
			keySym = XLookupKeysym(&xev.xkey, 0);
			addEvent = lookupX11Key(keySym, e.key);
			if (addEvent)
			{
				e.type = pa::Event::Type::KeyRelease;
				keyUp(e.key);
			}
			break;

		case ButtonPress:
			e.type = pa::Event::Type::KeyPress;
			switch (xev.xbutton.button)
			{
			case Button1:
				e.key = pa::Key::LMouseButton;
				m_pointer.setDown(true);
				break;
			case Button2: e.key = pa::Key::MMouseButton; break;
			case Button3: e.key = pa::Key::RMouseButton; break;
			}
			keyDown(e.key);
			break;

		case ButtonRelease:
			e.type = pa::Event::Type::KeyRelease;
			switch (xev.xbutton.button)
			{
			case Button1:
				e.key = pa::Key::LMouseButton;
				m_pointer.setDown(false);
				break;
			case Button2: e.key = pa::Key::MMouseButton; break;
			case Button3: e.key = pa::Key::RMouseButton; break;
			}
			keyDown(e.key);
			break;

		case FocusIn: XAutoRepeatOff(m_dpy); break;
		case FocusOut: XAutoRepeatOn(m_dpy); break;

		case ClientMessage: e.type = pa::Event::Type::Quit; break;
		}

		m_input.events.push_back(e);
	}

	std::copy(m_otherEvents.begin(), m_otherEvents.end(), std::back_inserter(m_input.events));

	XEvent event;
	XQueryPointer(m_dpy, m_win, &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root,
				  &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

	int x = PA_CLAMP(0, getSize().x, event.xbutton.x);
	int y = PA_CLAMP(0, getSize().y, event.xbutton.y);
	m_pointer.setPosition(x, y);
}

void pa::X11Platform::openUrl(const char* url)
{
	// Not implemented
}

// Adds a key is held event
void pa::X11Platform::keyDown(pa::Key key)
{
	pa::Event keyEvent;
	keyEvent.type = pa::Event::Type::KeyDown;
	keyEvent.key = key;

	m_otherEvents.push_back(keyEvent);
}

// Removes a key is held event
void pa::X11Platform::keyUp(pa::Key key)
{
	auto iterator =
		std::find_if(m_otherEvents.begin(), m_otherEvents.end(), [&key](const pa::Event& e) { return e.key == key; });

	if (iterator != m_otherEvents.end())
	{
		m_otherEvents.erase(iterator);
	}
}
