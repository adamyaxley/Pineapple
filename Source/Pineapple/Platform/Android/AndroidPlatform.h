#pragma once

#include <Pineapple/Engine/Platform/Platform.h>
#include <Pineapple/Platform/Android/AndroidArguments.h>
#include <Pineapple/Platform/Android/AndroidEngine.h>

namespace pa
{
	class AndroidPlatform : public Platform
	{
	public:

		AndroidPlatform(AndroidArguments* arguments, const PlatformSettings& settings);
		~AndroidPlatform();

		// Idle
		virtual void idle() override;

		// Set full screen mode
		virtual void setFullScreen(bool fullScren) override {}

		// Get input from user
		virtual void pollEvents() override;

		// Intent
		virtual void openUrl(const char* url) override;

		int32_t handleInputEvent(android_app* app, AInputEvent* inputEvent);

		void handleAppCommand(android_app* app, int32_t cmd);

	private:

		std::vector<Event> m_otherEvents;

		AndroidEngine m_engine;

		bool m_setPointerUpOnNextStep;
	};
}