/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Platform/Platform.h>
#include <Pineapple/Platform/Windows/WindowsArguments.h>
#include <Pineapple/Platform/Windows/WindowsKey.h>

LRESULT CALLBACK windowsProc(HWND hWND, UINT message, WPARAM wParam, LPARAM lParam);

namespace pa
{
	class WindowsPlatform : public Platform
	{
	public:
		WindowsPlatform(WindowsArguments* arguments, const PlatformSettings& settings);
		virtual ~WindowsPlatform();

		// Idle
		virtual void idle() override;

		// Set full screen mode
		virtual void setFullScreen(bool fullScren) override;

		// Get input from user
		virtual void pollEvents() override;

		// Intent
		virtual void openUrl(const char* url) override;

	private:
		friend LRESULT CALLBACK::windowsProc(HWND hWND, UINT message, WPARAM wParam, LPARAM lParam);

		void setupPixelFormat();

		void updatePointer();

		void keyDown(Key key);
		void keyUp(Key key);

		struct SavedWindowInfo
		{
			bool maximized;
			LONG style; // check these arent same as below
			LONG ex_style;
			RECT window_rect;
		};

		SavedWindowInfo m_savedWindowInfo;

		std::vector<Event> m_otherEvents;

		WindowsArguments* m_arguments;

		HDC m_hDC;
		HWND m_hWND;
		HGLRC m_hRC;

		DWORD m_dwExStyle; // Window Extended Style
		DWORD m_dwStyle;   // Window Style
	};
}
