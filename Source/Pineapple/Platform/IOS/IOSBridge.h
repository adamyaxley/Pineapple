#pragma once
#include <string>

#include <Pineapple/Platform/IOS/ThreadSignal.h>
#include <Pineapple/Platform/IOS/IOSPlatform.h>

#import <OpenGLES/EAGL.h>

namespace pa
{
	namespace IOSBridge
	{
		ThreadSignal<2>& getPlatformInitThreadSignal();
		ThreadSignal<2>& getGraphicsInitThreadSignal();

		ThreadSignal<2>& getFrameStartThreadSignal();
		ThreadSignal<2>& getFrameEndThreadSignal();

		ThreadSignal<2>& getDestroyThreadSignal();

		void setUIContext(EAGLContext* context);
		EAGLContext* getUIContext();

		void setTouchPosition(int x, int y);
		void clearTouchPosition();

		DeviceState& getTouchPosition();

		void setPlatform(pa::IOSPlatform* platform);
		pa::IOSPlatform* getPlatform();

		std::string getRoot();
		std::string getAssetPath();
		std::string getInternalPath();
	}
}
