//
//  paIOSBridge.cpp
//  paIOS
//
//  Created by apple on 03/08/2014.
//  Copyright (c) 2014 Pineapple. All rights reserved.
//

#include <Pineapple/Platform/IOS/paIOSBridge.h>
#include <Pineapple/Core/Platform/paEvent.hpp>

namespace
{
	pa::ThreadSignal<2> g_initThreadSignal;
	pa::ThreadSignal<2> g_frameStartThreadSignal;
	pa::ThreadSignal<2> g_frameEndThreadSignal;
	pa::ThreadSignal<2> g_destroyThreadSignal;
	
	EAGLContext* g_context = nil;
	
	pa::DeviceState g_touch;
	
	pa::Vect2<int> g_deviceSize;
	pa::Vect2<int> g_userSize;
}

pa::ThreadSignal<2>& pa::IOSBridge::getInitThreadSignal()
{
	return g_initThreadSignal;
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

void pa::IOSBridge::setDeviceSize(int x, int y)
{
	g_deviceSize.x = x;
	g_deviceSize.y = y;
}

const pa::Vect2<int>& pa::IOSBridge::getDeviceSize()
{
	return g_deviceSize;
}

void pa::IOSBridge::setUserSize(int x, int y)
{
	g_userSize.x = x;
	g_userSize.y = y;
}

const pa::Vect2<int>& pa::IOSBridge::getUserSize()
{
	return g_userSize;
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