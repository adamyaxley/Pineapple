/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Platform/X11/X11Key.h>
#include <X11/keysym.h>

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

bool pa::lookupX11Key(unsigned int key, pa::Key& keyOut)
{
	// <todo> digits from 0 - 9

	// Map Characters (case insensitive)
	if (key >= 'a' && key <= 'z')
	{
		keyOut = g_asciiLetterLookup[key - 'a'];
		return true;
	}
	if (key >= 'A' && key <= 'Z')
	{
		keyOut = g_asciiLetterLookup[key - 'A'];
		return true;
	}

	switch (key)
	{
	// Functions 1
	// case XK_3270_PrintScreen:			return PA_PRINT_SCREEN;
	case XK_Scroll_Lock: keyOut = pa::Key::Scroll; break;
	case XK_Pause:
		keyOut = pa::Key::Pause; break;

	// Cursor Control
	case XK_Insert: keyOut = pa::Key::Insert; break;
	case XK_Home: keyOut = pa::Key::Home; break;
	case XK_Prior: keyOut = pa::Key::PageUp; break;
	case XK_Delete: keyOut = pa::Key::Delete; break;
	case XK_End: keyOut = pa::Key::End; break;
	case XK_Next:
		keyOut = pa::Key::PageDown; break;

	// Motion
	case XK_Left: keyOut = pa::Key::Left; break;
	case XK_Up: keyOut = pa::Key::Up; break;
	case XK_Right: keyOut = pa::Key::Right; break;
	case XK_Down:
		keyOut = pa::Key::Down; break;

	// Number Pad
	case XK_Num_Lock: keyOut = pa::Key::NumLock; break;
	case XK_KP_Divide: keyOut = pa::Key::Divide; break;
	case XK_KP_Multiply: keyOut = pa::Key::Multiply; break;
	case XK_KP_Subtract: keyOut = pa::Key::Subtract; break;
	case XK_KP_Add: keyOut = pa::Key::Add; break;
	case XK_KP_Enter: keyOut = pa::Key::Enter; break;
	case XK_KP_Decimal: keyOut = pa::Key::Decimal; break;
	case XK_KP_0: keyOut = pa::Key::NumPad0; break;
	case XK_KP_1: keyOut = pa::Key::NumPad1; break;
	case XK_KP_2: keyOut = pa::Key::NumPad2; break;
	case XK_KP_3: keyOut = pa::Key::NumPad3; break;
	case XK_KP_4: keyOut = pa::Key::NumPad4; break;
	case XK_KP_5: keyOut = pa::Key::NumPad5; break;
	case XK_KP_6: keyOut = pa::Key::NumPad6; break;
	case XK_KP_7: keyOut = pa::Key::NumPad7; break;
	case XK_KP_8: keyOut = pa::Key::NumPad8; break;
	case XK_KP_9:
		keyOut = pa::Key::NumPad9; break;

	// Main Buttons
	case XK_Escape: keyOut = pa::Key::Esc; break;
	case XK_Tab: keyOut = pa::Key::Tab; break;
	case XK_Caps_Lock: keyOut = pa::Key::Caps; break;
	case XK_Shift_L: keyOut = pa::Key::LShift; break;
	case XK_Control_L: keyOut = pa::Key::LCtrl; break;
	case XK_Alt_L: keyOut = pa::Key::LAlt; break;
	case XK_space: keyOut = pa::Key::Space; break;
	case XK_Alt_R:
		keyOut = pa::Key::RAlt; break; // <todo> doesnt work
	case XK_Control_R: keyOut = pa::Key::RCtrl; break;
	case XK_Shift_R: keyOut = pa::Key::RShift; break;
	case XK_Return: keyOut = pa::Key::Enter; break;
	case XK_BackSpace:
		keyOut = pa::Key::BackSpace; break;

	// Auxiliary Functions
	case XK_F1: keyOut = pa::Key::F1; break;
	case XK_F2: keyOut = pa::Key::F2; break;
	case XK_F3: keyOut = pa::Key::F3; break;
	case XK_F4: keyOut = pa::Key::F4; break;
	case XK_F5: keyOut = pa::Key::F5; break;
	case XK_F6: keyOut = pa::Key::F6; break;
	case XK_F7: keyOut = pa::Key::F7; break;
	case XK_F8: keyOut = pa::Key::F8; break;
	case XK_F9: keyOut = pa::Key::F9; break;
	case XK_F10: keyOut = pa::Key::F10; break;
	case XK_F11: keyOut = pa::Key::F11; break;
	case XK_F12: keyOut = pa::Key::F12; break;
	case XK_F13: keyOut = pa::Key::F13; break;
	case XK_F14: keyOut = pa::Key::F14; break;
	case XK_F15: keyOut = pa::Key::F15; break;
	case XK_F16: keyOut = pa::Key::F16; break;
	case XK_F17: keyOut = pa::Key::F17; break;
	case XK_F18: keyOut = pa::Key::F18; break;
	case XK_F19: keyOut = pa::Key::F19; break;
	case XK_F20: keyOut = pa::Key::F20; break;
	case XK_F21: keyOut = pa::Key::F21; break;
	case XK_F22: keyOut = pa::Key::F22; break;
	case XK_F23: keyOut = pa::Key::F23; break;
	case XK_F24: keyOut = pa::Key::F24; break;
	default: return false;
	}
	return true;
}
