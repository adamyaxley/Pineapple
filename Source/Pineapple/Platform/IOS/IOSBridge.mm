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
	paThreadSignal<2> g_initThreadSignal;
	paThreadSignal<2> g_frameStartThreadSignal;
	paThreadSignal<2> g_frameEndThreadSignal;
	paThreadSignal<2> g_destroyThreadSignal;
	
	EAGLContext* g_context = nil;
	
	paDeviceState g_touch;
	
	paVect2<int> g_deviceSize;
	paVect2<int> g_userSize;
}

paThreadSignal<2>& paIOSBridge::getInitThreadSignal()
{
	return g_initThreadSignal;
}

paThreadSignal<2>& paIOSBridge::getFrameStartThreadSignal()
{
	return g_frameStartThreadSignal;
}

paThreadSignal<2>& paIOSBridge::getFrameEndThreadSignal()
{
	return g_frameEndThreadSignal;
}

paThreadSignal<2>& paIOSBridge::getDestroyThreadSignal()
{
	return g_destroyThreadSignal;
}

void paIOSBridge::setUIContext(EAGLContext* context)
{
	g_context = context;
}

EAGLContext* paIOSBridge::getUIContext()
{
	return g_context;
}

void paIOSBridge::setTouchPosition(int x, int y)
{
	g_touch.z = 1;
	
	g_touch.x = x;
	g_touch.y = y;
}
void paIOSBridge::clearTouchPosition()
{
	g_touch.z = 0;
}

paDeviceState& paIOSBridge::getTouchPosition()
{
	return g_touch;
}

void paIOSBridge::setDeviceSize(int x, int y)
{
	g_deviceSize.x = x;
	g_deviceSize.y = y;
}

const paVect2<int>& paIOSBridge::getDeviceSize()
{
	return g_deviceSize;
}

void paIOSBridge::setUserSize(int x, int y)
{
	g_userSize.x = x;
	g_userSize.y = y;
}

const paVect2<int>& paIOSBridge::getUserSize()
{
	return g_userSize;
}

std::string paIOSBridge::getRoot()
{
	NSString* bundle = [[NSBundle mainBundle] bundlePath];
	const char* root = [bundle fileSystemRepresentation];
	std::string rootString(root);
	
	return rootString;
}

std::string paIOSBridge::makeAssetPath(const char* path)
{
	std::string root = getRoot();
	root += "/Assets/";
	root += path;
	return root;
}