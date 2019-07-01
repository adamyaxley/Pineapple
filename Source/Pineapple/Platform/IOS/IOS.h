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

	private:

		std::vector<Event> m_otherEvents;
	};
}