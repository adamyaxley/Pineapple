/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

//
//  IOSBridge.h
//  IOS
//
//  Created by apple on 03/08/2014.
//  Copyright (c) 2014 Pineapple. All rights reserved.
//

#ifndef PA_INCLUDE_IOS_BRIDGE
	#define PA_INCLUDE_IOS_BRIDGE

	#include <string>

	#include <Pineapple/Platform/IOS/ThreadSignal.h>
	#import <OpenGLES/EAGL.h>

namespace pa
{
	namespace IOSBridge
	{
		ThreadSignal<2>& getInitThreadSignal();
		ThreadSignal<2>& getFrameStartThreadSignal();
		ThreadSignal<2>& getFrameEndThreadSignal();
		ThreadSignal<2>& getDestroyThreadSignal();

		void setUIContext(EAGLContext* context);
		EAGLContext* getUIContext();

		void setTouchPosition(int x, int y);
		void clearTouchPosition();

		DeviceState& getTouchPosition();

		void setDeviceSize(int x, int y);
		const Vect2<int>& getDeviceSize();

		void setUserSize(int x, int y);
		const Vect2<int>& getUserSize();

		std::string getRoot();
		std::string makeAssetPath(const char* path);
	}

#endif
}
