/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Platform/Event.h>
#include <Pineapple/Platform/Windows/WindowsKey.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace
{
	static const pa::Key g_asciiDigitLookup[] = {pa::Key::D0, pa::Key::D1, pa::Key::D2, pa::Key::D3, pa::Key::D4,
												 pa::Key::D5, pa::Key::D6, pa::Key::D7, pa::Key::D8, pa::Key::D9};

	static const pa::Key g_asciiLetterLookup[] = {pa::Key::A, pa::Key::B, pa::Key::C, pa::Key::D, pa::Key::E,
												  pa::Key::F, pa::Key::G, pa::Key::H, pa::Key::I, pa::Key::J,
												  pa::Key::K, pa::Key::L, pa::Key::M, pa::Key::N, pa::Key::O,
												  pa::Key::P, pa::Key::Q, pa::Key::R, pa::Key::S, pa::Key::T,
												  pa::Key::U, pa::Key::V, pa::Key::W, pa::Key::X, pa::Key::Y,
												  pa::Key::Z};
}

bool pa::lookupWindowsKey(unsigned int key, LPARAM lParam, pa::Key& keyOut)
{
	if (key >= 'A' && key <= 'Z')
	{
		keyOut = g_asciiLetterLookup[key - 'A'];
		return true;
	}
	if (key >= '0' && key <= '9')
	{
		keyOut = g_asciiDigitLookup[key - '0'];
		return true;
	}
	switch (key)
	{
	// Functions 1
	case VK_SNAPSHOT: keyOut = pa::Key::PrintScreen; break;
	case VK_SCROLL: keyOut = pa::Key::Scroll; break;
	case VK_PAUSE:
		keyOut = pa::Key::Pause;
		break;
	// Functions 2
	case VK_INSERT: keyOut = pa::Key::Insert; break;
	case VK_HOME: keyOut = pa::Key::Home; break;
	case VK_PRIOR: keyOut = pa::Key::PageUp; break;
	case VK_DELETE: keyOut = pa::Key::Delete; break;
	case VK_END: keyOut = pa::Key::End; break;
	case VK_NEXT:
		keyOut = pa::Key::PageDown;
		break;
	// Arrows
	case VK_LEFT: keyOut = pa::Key::Left; break;
	case VK_UP: keyOut = pa::Key::Up; break;
	case VK_RIGHT: keyOut = pa::Key::Right; break;
	case VK_DOWN:
		keyOut = pa::Key::Down;
		break;
	// Number pad
	case VK_NUMLOCK: keyOut = pa::Key::NumLock; break;
	case VK_DIVIDE: keyOut = pa::Key::Divide; break;
	case VK_MULTIPLY: keyOut = pa::Key::Multiply; break;
	case VK_SUBTRACT: keyOut = pa::Key::Subtract; break;
	case VK_ADD:
		keyOut = pa::Key::Add;
		break;
	// Enter button same as vk_enter?
	case VK_DECIMAL: keyOut = pa::Key::Decimal; break;
	case VK_NUMPAD0: keyOut = pa::Key::NumPad0; break;
	case VK_NUMPAD1: keyOut = pa::Key::NumPad1; break;
	case VK_NUMPAD2: keyOut = pa::Key::NumPad2; break;
	case VK_NUMPAD3: keyOut = pa::Key::NumPad3; break;
	case VK_NUMPAD4: keyOut = pa::Key::NumPad4; break;
	case VK_NUMPAD5: keyOut = pa::Key::NumPad5; break;
	case VK_NUMPAD6: keyOut = pa::Key::NumPad6; break;
	case VK_NUMPAD7: keyOut = pa::Key::NumPad7; break;
	case VK_NUMPAD8: keyOut = pa::Key::NumPad8; break;
	case VK_NUMPAD9:
		keyOut = pa::Key::NumPad9;
		break;
	// Main buttons
	case VK_ESCAPE: keyOut = pa::Key::Esc; break;
	case VK_TAB: keyOut = pa::Key::Tab; break;
	case VK_CAPITAL: keyOut = pa::Key::Caps; break;
	case VK_SHIFT:
		if (GetKeyState(VK_LSHIFT) & 0x8000)
			keyOut = pa::Key::LShift;
		else
			keyOut = pa::Key::RShift;
		break;
	case VK_CONTROL:
		if (lParam & (1 << 24))
			keyOut = pa::Key::RCtrl;
		else
			keyOut = pa::Key::LCtrl;
		break;
	case VK_MENU: // causes window to lose focus
		if (lParam & (1 << 24))
			keyOut = pa::Key::RAlt;
		else
			keyOut = pa::Key::LAlt;
		break;
	case VK_SPACE: keyOut = pa::Key::Space; break;
	case VK_RETURN:
		keyOut = pa::Key::Enter;
		break; // both enter and numpad enter
	case VK_BACK:
		keyOut = pa::Key::BackSpace;
		break;
	// Functions
	case VK_F1: keyOut = pa::Key::F1; break;
	case VK_F2: keyOut = pa::Key::F2; break;
	case VK_F3: keyOut = pa::Key::F3; break;
	case VK_F4: keyOut = pa::Key::F4; break;
	case VK_F5: keyOut = pa::Key::F5; break;
	case VK_F6: keyOut = pa::Key::F6; break;
	case VK_F7: keyOut = pa::Key::F7; break;
	case VK_F8: keyOut = pa::Key::F8; break;
	case VK_F9: keyOut = pa::Key::F9; break;
	case VK_F10: keyOut = pa::Key::F10; break;
	case VK_F11: keyOut = pa::Key::F11; break;
	case VK_F12: keyOut = pa::Key::F12; break;
	case VK_F13: keyOut = pa::Key::F13; break;
	case VK_F14: keyOut = pa::Key::F14; break;
	case VK_F15: keyOut = pa::Key::F15; break;
	case VK_F16: keyOut = pa::Key::F16; break;
	case VK_F17: keyOut = pa::Key::F17; break;
	case VK_F18: keyOut = pa::Key::F18; break;
	case VK_F19: keyOut = pa::Key::F19; break;
	case VK_F20: keyOut = pa::Key::F20; break;
	case VK_F21: keyOut = pa::Key::F21; break;
	case VK_F22: keyOut = pa::Key::F22; break;
	case VK_F23: keyOut = pa::Key::F23; break;
	case VK_F24: keyOut = pa::Key::F24; break;
	default: return false;
	}

	return true;
}
