#include <Pineapple/Platform/IOS/IOSBridge.h>

namespace
{
	pa::ThreadSignal<2> g_platformInitThreadSignal;
	pa::ThreadSignal<2> g_graphicsInitThreadSignal;

	pa::ThreadSignal<2> g_frameStartThreadSignal;
	pa::ThreadSignal<2> g_frameEndThreadSignal;

	pa::ThreadSignal<2> g_destroyThreadSignal;
	
	EAGLContext* g_context = nil;
	
	pa::DeviceState g_touch;
	
	pa::Vect2<int> g_deviceSize;
	pa::Vect2<int> g_userSize;

	pa::IOSPlatform* g_platform = nullptr;
}

pa::ThreadSignal<2>& pa::IOSBridge::getPlatformInitThreadSignal()
{
	return g_platformInitThreadSignal;
}

pa::ThreadSignal<2>& pa::IOSBridge::getGraphicsInitThreadSignal()
{
	return g_graphicsInitThreadSignal;
}

pa::ThreadSignal<2>& pa::IOSBridge::getFrameStartThreadSignal()
{
	return g_frameStartThreadSignal;
}

pa::ThreadSignal<2>& pa::IOSBridge::getFrameEndThreadSignal()
{
	return g_frameEndThreadSignal;
}

pa::ThreadSignal<2>& pa::IOSBridge::getDestroyThreadSignal()
{
	return g_destroyThreadSignal;
}

void pa::IOSBridge::setUIContext(EAGLContext* context)
{
	g_context = context;
}

EAGLContext* pa::IOSBridge::getUIContext()
{
	return g_context;
}

void pa::IOSBridge::setTouchPosition(int x, int y)
{
	g_touch.z = 1;
	
	g_touch.x = x;
	g_touch.y = y;
}
void pa::IOSBridge::clearTouchPosition()
{
	g_touch.z = 0;
}

pa::DeviceState& pa::IOSBridge::getTouchPosition()
{
	return g_touch;
}

void pa::IOSBridge::setPlatform(pa::IOSPlatform* platform)
{
	g_platform = platform;
}

pa::IOSPlatform* pa::IOSBridge::getPlatform()
{
	return g_platform;
}

std::string pa::IOSBridge::getRoot()
{
	NSString* bundle = [[NSBundle mainBundle] bundlePath];
	const char* root = [bundle fileSystemRepresentation];
	std::string rootString(root);
	
	return rootString;
}

std::string pa::IOSBridge::getAssetPath()
{
	std::string root = getRoot();
	root += "/Assets/";
	return root;
}

std::string pa::IOSBridge::getInternalPath()
{
	std::string root = getRoot();
	root += "/Internal/";
	return root;
}