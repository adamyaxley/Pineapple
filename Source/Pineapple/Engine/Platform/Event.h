/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <string>

namespace pa
{
	enum class Key
	{
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,

		D0,
		D1,
		D2,
		D3,
		D4,
		D5,
		D6,
		D7,
		D8,
		D9,

		PrintScreen,
		Scroll,
		Pause,

		Insert,
		Home,
		PageUp,
		Delete,
		End,
		PageDown,

		Left,
		Up,
		Right,
		Down,

		NumLock,
		Divide,
		Multiply,
		Subtract,
		Add,
		Decimal,
		NumPad0,
		NumPad1,
		NumPad2,
		NumPad3,
		NumPad4,
		NumPad5,
		NumPad6,
		NumPad7,
		NumPad8,
		NumPad9,

		Esc,
		Tab,
		Caps,
		LShift,
		LCtrl,
		LAlt,
		Space,
		RAlt,
		RCtrl,
		RShift,
		Enter,
		BackSpace,

		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		F13,
		F14,
		F15,
		F16,
		F17,
		F18,
		F19,
		F20,
		F21,
		F22,
		F23,
		F24,

		LMouseButton,
		MMouseButton,
		RMouseButton,

		AButton,
		BButton,
		XButton,
		YButton,
		LButton,
		RButton,
		Start,
		Select,
		Touch,
		CloseLid,

		Back
	};

	// Keyboard or other input events
	struct Event
	{
		enum class Type
		{
			KeyPress,
			KeyDown,
			KeyRelease,
			CharInput,
			Quit
		};

		Type type;

		// Specifies the keyboard key (if applicable)
		Key key;

		// Specifies the UTF8 character that was pressed
		std::string input;
	};
}
