/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Container/Vect2.h>
#include <Pineapple/Engine/Platform/Event.h>
#include <Pineapple/Engine/Platform/Pointer.h>
#include <Pineapple/Engine/System/Input.h>
#include <Pineapple/Engine/Util/Macro.h>

#include <Pineapple/Engine/Graphics/Graphics.h>
#include <Pineapple/Engine/Sound/Sound.h>

#include <memory>
#include <vector>

namespace pa
{
	struct Arguments
	{
		virtual ~Arguments()
		{
		}
	};

	extern int Main(Arguments*);

	class Platform;

	struct PlatformSettings
	{
		const char* title;

		struct Graphics
		{
			bool use = true;
			Vect2<int> size;
		} graphics;

		struct Sound
		{
			bool use = true;
		} sound;
	};

	namespace Make
	{
		std::shared_ptr<Platform> platform(Arguments* arguments, const PlatformSettings& settings);
	}

	class Platform
	{
	public:
		// Startup and shutdown
		Platform(const PlatformSettings& settings);
		virtual ~Platform()
		{
		}

		// Size
		const Vect2<int>& getSize() const;

		bool isFullScreen() const;

		const Input& getInput() const;
		const Pointer& getPointer() const;

		// Graphics
		Graphics* getGraphics();

		// Sound
		Sound* getSound();

		// Idle
		virtual void idle() = 0;

		// Set full screen mode
		virtual void setFullScreen(bool fullScren) = 0;

		// Get input from user
		virtual void pollEvents() = 0;

		// Intent
		virtual void openUrl(const char* url) = 0;

	protected:
		const PlatformSettings m_settings;

		Vect2<int> m_size;

		bool m_isFullScreen;

		Input m_input;
		Pointer m_pointer;

		std::unique_ptr<Graphics> m_graphics;
		std::unique_ptr<Sound> m_sound;
	};
}
