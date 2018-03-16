/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Graphics/Graphics.h>
#include <Pineapple/Engine/Platform/Platform.h>
#include <Pineapple/Engine/Sound/Sound.h>
#include <Pineapple/Engine/Util/Macro.h>
#include <Pineapple/Platform/Windows/WindowsKey.h>
#include <Pineapple/Platform/Windows/WindowsPlatform.h>

// Trim fat from windows include
#define WIN32_LEAN_AND_MEAN

#include <algorithm>
#include <codecvt>
#include <cstdlib>
#include <ctime>
#include <fcntl.h>
#include <io.h>
#include <iterator>
#include <shellapi.h>
#include <stdarg.h>
#include <stdio.h>
#include <windows.h>

std::shared_ptr<pa::Platform> pa::Make::platform(pa::Arguments* arguments, const pa::PlatformSettings& settings)
{
	auto windowsArguments = static_cast<pa::WindowsArguments*>(arguments);
	return std::make_shared<pa::WindowsPlatform>(windowsArguments, settings);
}

namespace
{
	void setVSync(bool sync)
	{
		typedef BOOL(APIENTRY * PFNWGLSWAPINTERVALPROC)(int);
		PFNWGLSWAPINTERVALPROC wglSwapIntervalEXT = 0;

		wglSwapIntervalEXT = (PFNWGLSWAPINTERVALPROC)wglGetProcAddress("wglSwapIntervalEXT");

		if (wglSwapIntervalEXT)
		{
			wglSwapIntervalEXT(sync ? 1 : 0);
		}
	}

	void showConsole()
	{
		AllocConsole();

		HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
		int hCrt = _open_osfhandle((intptr_t)handle_out, _O_TEXT);
		FILE* hf_out = _fdopen(hCrt, "w");
		setvbuf(hf_out, NULL, _IONBF, 1);
		*stdout = *hf_out;

		HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
		hCrt = _open_osfhandle((intptr_t)handle_in, _O_TEXT);
		FILE* hf_in = _fdopen(hCrt, "r");
		setvbuf(hf_in, NULL, _IONBF, 128);
		*stdin = *hf_in;
	}
}

// Windows entry point
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Set some global variables
	auto arguments = std::make_unique<pa::WindowsArguments>(hInstance, nCmdShow);

	// Convert windows command line arguments to ansi style ones
	// int argc;
	// char** argv = reinterpret_cast<char**>(CommandLineToArgvW(GetCommandLineW(), &argc)); // TODO check this works
	// with unicode

	showConsole();

	// Call our main function from here
	return pa::Main(arguments.get());
}

pa::WindowsPlatform::WindowsPlatform(pa::WindowsArguments* arguments, const pa::PlatformSettings& settings)
	: pa::Platform(settings)
	, m_arguments(arguments)
	, m_hDC(nullptr)
	, m_hWND(nullptr)
	, m_hRC(nullptr)
{
	m_size = settings.graphics.size;

	WNDCLASSEX windowClass;

	RECT WindowRect;

	const TCHAR* className = TEXT("PineappleClass");

	// Fill out the window class structure
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = windowsProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = m_arguments->getInstance();
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = className;
	windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	// Register the class
	if (!RegisterClassEx(&windowClass))
	{
		throw std::exception("Cannot register class");
	}

	WindowRect.left = (long)0;
	WindowRect.right = (long)m_size.x;
	WindowRect.top = (long)0;
	WindowRect.bottom = (long)m_size.y;

	m_dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	m_dwStyle = WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_THICKFRAME);

	// Adjust window to true requested size
	AdjustWindowRectEx(&WindowRect, m_dwStyle, FALSE, m_dwExStyle);

#ifdef UNICODE
	int bufferSize = MultiByteToWideChar(CP_UTF8, 0, settings.title.c_str(), -1, nullptr, 0);
	LPWSTR translatedTitle = static_cast<LPWSTR>(pa::Memory::allocate(sizeof(wchar_t) * (bufferSize + 1)));
	MultiByteToWideChar(CP_UTF8, 0, settings.title.c_str(), -1, translatedTitle, bufferSize);
	translatedTitle[bufferSize] = L'\0';
#else
	const char* translatedTitle = settings.title.c_str();
#endif

	// Create the window
	m_hWND = CreateWindowEx(m_dwExStyle,														 // Extended style
							className, translatedTitle, m_dwStyle, CW_USEDEFAULT, CW_USEDEFAULT, // Window coords
							WindowRect.right - WindowRect.left, // Calculate Adjusted Window Width
							WindowRect.bottom - WindowRect.top, // Calculate Adjusted Window Height
							NULL,								// Handle to parent
							NULL,								// Handle to menu
							m_arguments->getInstance(),
							this); // Pass a pointer to the class here

#ifdef UNICODE
	pa::Memory::deallocate(translatedTitle);
#endif

	// Did window creation fail
	if (!m_hWND)
	{
		throw std::exception("Failed to create window");
	}

	m_isFullScreen = false;

	ShowWindow(m_hWND, SW_SHOW);
	UpdateWindow(m_hWND);

	// Seed random number generator and call it once
	srand((unsigned int)::time(0));
	rand();

	m_fileSystem = pa::MakeInternal::fileSystem(settings.fileSystem);

	// Unique pointers
	if (settings.graphics.use)
	{
		m_graphics = pa::MakeInternal::graphics(settings.graphics.size, *m_fileSystem.get());
	}

	if (settings.sound.use)
	{
		m_sound = pa::MakeInternal::sound(*m_fileSystem.get());
	}
}

pa::WindowsPlatform::~WindowsPlatform()
{
	m_sound.reset();
	m_graphics.reset();
	m_fileSystem.reset();

	// Free memory
	wglMakeCurrent(m_hDC, NULL);
	wglDeleteContext(m_hRC);
	ReleaseDC(m_hWND, m_hDC);

	// Destroy window
	DestroyWindow(m_hWND);
}

void pa::WindowsPlatform::setFullScreen(bool fullscreen)
{
	// Adapted from:
	// http://src.chromium.org/viewvc/chrome/trunk/src/ui/views/win/fullscreen_handler.cc?revision=HEAD&view=markup
	bool for_metro = false;

	// Save current window state if not already fullscreen.
	if (!m_isFullScreen)
	{
		// Save current window information.  We force the window into restored mode
		// before going fullscreen because Windows doesn't seem to hide the
		// taskbar if the window is in the maximized state.
		m_savedWindowInfo.maximized = !!::IsZoomed(m_hWND);
		if (m_savedWindowInfo.maximized)
			::SendMessage(m_hWND, WM_SYSCOMMAND, SC_RESTORE, 0);
		m_savedWindowInfo.style = GetWindowLong(m_hWND, GWL_STYLE);
		m_savedWindowInfo.ex_style = GetWindowLong(m_hWND, GWL_EXSTYLE);
		GetWindowRect(m_hWND, &m_savedWindowInfo.window_rect);
	}

	m_isFullScreen = fullscreen;

	if (m_isFullScreen)
	{
		// Set new window style and size.
		SetWindowLong(m_hWND, GWL_STYLE, m_savedWindowInfo.style & ~(WS_CAPTION | WS_THICKFRAME));
		SetWindowLong(m_hWND, GWL_EXSTYLE,
					  m_savedWindowInfo.ex_style &
						  ~(WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE));

		// On expand, if we're given a window_rect, grow to it, otherwise do
		// not resize.
		if (!for_metro)
		{
			MONITORINFO monitor_info;
			monitor_info.cbSize = sizeof(monitor_info);
			GetMonitorInfo(MonitorFromWindow(m_hWND, MONITOR_DEFAULTTONEAREST), &monitor_info);

			SetWindowPos(m_hWND, NULL, monitor_info.rcMonitor.left, monitor_info.rcMonitor.top,
						 monitor_info.rcMonitor.right - monitor_info.rcMonitor.left,
						 monitor_info.rcMonitor.bottom - monitor_info.rcMonitor.top,
						 SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);

			m_size.x = monitor_info.rcMonitor.right - monitor_info.rcMonitor.left;
			m_size.y = monitor_info.rcMonitor.bottom - monitor_info.rcMonitor.top;
		}
	}
	else
	{
		// Reset original window style and size.  The multiple window size/moves
		// here are ugly, but if SetWindowPos() doesn't redraw, the taskbar won't be
		// repainted.  Better-looking methods welcome.
		SetWindowLong(m_hWND, GWL_STYLE, m_savedWindowInfo.style);
		SetWindowLong(m_hWND, GWL_EXSTYLE, m_savedWindowInfo.ex_style);

		if (!for_metro)
		{
			// On restore, resize to the previous saved rect size.
			RECT new_rect(m_savedWindowInfo.window_rect);
			SetWindowPos(m_hWND, NULL, new_rect.left, new_rect.top, new_rect.right - new_rect.left,
						 new_rect.bottom - new_rect.top, SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
		}
		if (m_savedWindowInfo.maximized)
			::SendMessage(m_hWND, WM_SYSCOMMAND, SC_MAXIMIZE, 0);

		m_size = m_settings.graphics.size;
	}
}

void pa::WindowsPlatform::openUrl(const char* url)
{
	// Not implemented
}

void pa::WindowsPlatform::pollEvents()
{
	MSG msg;
	m_input.events.clear();

	while (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
	{
		pa::Event event;
		bool addEvent = true;

		if (msg.message == WM_QUIT)
		{
			event.type = pa::Event::Type::Quit;
		}
		else
		{
			TranslateMessage(&msg);

			switch (msg.message)
			{
			// Keyboard
			case WM_KEYDOWN:
				if (!(msg.lParam & 0x40000000)) // If its the first time this key has been pressed
				{
					addEvent = pa::lookupWindowsKey((unsigned int)msg.wParam, msg.lParam, event.key);
					if (addEvent)
					{
						event.type = pa::Event::Type::KeyPress;
						keyDown(event.key);
					}
				}
				break;

			case WM_KEYUP:
				addEvent = pa::lookupWindowsKey((unsigned int)msg.wParam, msg.lParam, event.key);
				if (addEvent)
				{
					event.type = pa::Event::Type::KeyRelease;
					keyUp(event.key);
				}
				break;

			case WM_CHAR:
			{
				// wide to UTF-8
				event.type = pa::Event::Type::CharInput;
				std::wstring_convert<std::codecvt_utf8<wchar_t>> conv1;
				std::string utf8 = conv1.to_bytes((wchar_t)msg.wParam);
				event.input = utf8;
				break;
			}

			// Left mouse button
			case WM_LBUTTONDOWN:
				event.type = pa::Event::Type::KeyPress;
				event.key = pa::Key::LMouseButton;
				keyDown(event.key);
				break;

			case WM_LBUTTONUP:
				event.type = pa::Event::Type::KeyRelease;
				event.key = pa::Key::LMouseButton;
				keyUp(event.key);
				break;

			// Middle mouse button
			case WM_MBUTTONDOWN:
				event.type = pa::Event::Type::KeyPress;
				event.key = pa::Key::MMouseButton;
				keyDown(event.key);
				break;

			case WM_MBUTTONUP:
				event.type = pa::Event::Type::KeyRelease;
				event.key = pa::Key::MMouseButton;
				keyUp(event.key);
				break;

			// Right mouse button
			case WM_RBUTTONDOWN:
				event.type = pa::Event::Type::KeyPress;
				event.key = pa::Key::RMouseButton;
				keyDown(event.key);
				break;

			case WM_RBUTTONUP:
				event.type = pa::Event::Type::KeyRelease;
				event.key = pa::Key::RMouseButton;
				keyUp(event.key);
				break;

			default: addEvent = false;
			}
		}

		if (addEvent)
		{
			// Add this event to the linked list
			m_input.events.push_back(event);
		}
		else
		{
			DefWindowProc(msg.hwnd, msg.message, msg.wParam, msg.lParam);
		}
	}

	std::copy(m_otherEvents.begin(), m_otherEvents.end(), std::back_inserter(m_input.events));

	updatePointer();
}

void pa::WindowsPlatform::idle()
{
	if (getSound())
	{
		getSound()->update();
	}

	if (getGraphics())
	{
		getGraphics()->render();
		SwapBuffers(m_hDC);
	}
}

// Adds a key is held event
void pa::WindowsPlatform::keyDown(pa::Key key)
{
	pa::Event keyEvent;
	keyEvent.type = pa::Event::Type::KeyDown;
	keyEvent.key = key;

	m_otherEvents.push_back(keyEvent);
}

// Removes a key is held event
void pa::WindowsPlatform::keyUp(pa::Key key)
{
	auto iterator =
		std::find_if(m_otherEvents.begin(), m_otherEvents.end(), [&key](const pa::Event& e) { return e.key == key; });

	if (iterator != m_otherEvents.end())
	{
		m_otherEvents.erase(iterator);
	}
}

void pa::WindowsPlatform::updatePointer()
{
	// This code works while the mouse is outside the client area
	POINT mousePos;
	GetCursorPos(&mousePos);

	RECT windowPos, clientPos;
	GetWindowRect(m_hWND, &windowPos);
	clientPos = windowPos;

	AdjustWindowRectEx(&windowPos, m_dwStyle, FALSE, m_dwExStyle);

	clientPos.left -= windowPos.left - clientPos.left;
	clientPos.top -= windowPos.top - clientPos.top;

	int x = PA_CLAMP(0, pa::Platform::getSize().x, mousePos.x - clientPos.left);
	int y = PA_CLAMP(0, pa::Platform::getSize().y, mousePos.y - clientPos.top);

	bool down = ((GetKeyState(VK_LBUTTON) & 0x100) != 0);

	m_pointer.setPosition(x, y);
	m_pointer.setDown(down);
}

void pa::WindowsPlatform::setupPixelFormat()
{
	PIXELFORMATDESCRIPTOR pfd = {sizeof(PIXELFORMATDESCRIPTOR),
								 1, // Default version
								 PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
								 PFD_TYPE_RGBA,
								 32, // 32 bit color mode
								 0,
								 0,
								 0,
								 0,
								 0,
								 0, // Ignore color bits
								 0, // No alpha buffer
								 0, // Ignore shift bit
								 0, // No accumulation buffer
								 0,
								 0,
								 0,
								 0,  // Ignore accumulation bits
								 16, // 16 bit z-buffer size
								 0,  // No stencil buffer
								 0,  // No aux buffer
								 PFD_MAIN_PLANE,
								 0, // Reserved
								 0,
								 0,
								 0}; // Layer masks ignored

	PA_ASSERTF(m_hDC != nullptr, "The Display Context has not been set yet (m_hDC)");

	// Choose closest matching format
	int nPixelFormat = ChoosePixelFormat(m_hDC, &pfd);

	// Set the pixel format to the device context
	SetPixelFormat(m_hDC, nPixelFormat, &pfd);
}

// Windows procedure event handler
LRESULT CALLBACK windowsProc(HWND hWND, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		pa::WindowsPlatform* windowsPlatform =
			static_cast<pa::WindowsPlatform*>(((CREATESTRUCT*)lParam)->lpCreateParams);

		// Get device context
		windowsPlatform->m_hDC = GetDC(hWND);
		windowsPlatform->setupPixelFormat();

		// Create rendering context
		windowsPlatform->m_hRC = wglCreateContext(windowsPlatform->m_hDC);
		wglMakeCurrent(windowsPlatform->m_hDC, windowsPlatform->m_hRC);
		setVSync(true);

		return 0;
		break;
	}

	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
		break;

	default: break;
	}

	return (DefWindowProc(hWND, message, wParam, lParam));
}