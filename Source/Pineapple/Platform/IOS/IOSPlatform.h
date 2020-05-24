#pragma once

#include <Pineapple/Engine/Platform/Platform.h>

namespace pa
{
	class IOSPlatform : public Platform
	{
	public:

		IOSPlatform(const PlatformSettings& settings);
		~IOSPlatform();

		// Idle
		virtual void idle() override;

		// Set full screen mode
		virtual void setFullScreen(bool fullScren) override {}

		// Get input from user
		virtual void pollEvents() override;

		// Intent
		virtual void openUrl(const char* url) override;

		// Create the graphics (called from the UI thread)
		void makeGraphics(int surfaceWidth, int surfaceHeight);

		// Espose pointer (called from the UI thread - ViewController)
		Pointer& getPointer();

	private:

		//std::vector<Event> m_otherEvents;
	};
}