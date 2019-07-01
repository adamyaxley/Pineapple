#include <Pineapple/Core/Platform/paPlatform.hpp>
#include <Pineapple/Graphics/Base/paGraphics.hpp>
#include <Pineapple/Platform/IOS/AppDelegate.h>
#include <Pineapple/Platform/IOS/IOSBridge.h>

#include <cstdlib>
#include <sys/time.h>
#include <pthread.h>

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <QuartzCore/CAAnimation.h>

std::shared_ptr<pa::Platform> pa::Make::platform(pa::Arguments* arguments, const pa::PlatformSettings& settings)
{
	return std::make_shared<pa::IOSPlatform>(settings);
}

namespace
{
	pthread_t g_applicationThread;
	
	void* UIMainThread(void*)
	{
		pa::Main();
		
		return nullptr;
	}
}

int main(int argc, char* argv[])
{
	// Create our client thread
	pthread_attr_t attr;
	
	int result;
	
	result = pthread_attr_init(&attr);
	
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	
	result = pthread_create(&g_applicationThread, &attr, &UIMainThread, PA_NULL);
	
	@autoreleasepool
	{
		UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
	}
	
	// Will never execute since UIApplicationMain never returns
	return 0;
}

// Startup and shutdown
pa::IOSPlatform::IOSPlatform(const PlatformSettings& settings)
{
	pa::IOSBridge::setUserSize(settings.graphics.size.x, settings.graphics.size.y);
		
	// wait until app has loaded
	pa::IOSBridge::getInitThreadSignal().sync();
	
	// Create shared context for loading textures and other resources
	EAGLContext* sharedContext = [[EAGLContext alloc] initWithAPI:[pa::IOSBridge::getUIContext() API] sharegroup:[pa::IOSBridge::getUIContext() sharegroup]];
	
	if (!sharedContext)
	{
		pa::Log::info("sharedContext is null");
	}
	
	if (![EAGLContext setCurrentContext:sharedContext])
	{
		pa::Log::info("Could not set current sharedContext after init");
	}
	
	// Resize our window to fit what the user gave us
	// TODO this should be done when graphics is inititialised
	paGraphics::resizeKeepAspectRatio(width, height);
}

pa::IOSPlatform::~IOSPlatform()
{
    // issue exit TODO
    
    // join app thread
}

// Idle
void pa::IOSPlatform::idle()
{
	// Use barriers to allow the UI thread to render at the correct time.
    pa::IOSBridge::getFrameStartThreadSignal().sync();
	pa::IOSBridge::getFrameEndThreadSignal().sync();
}

// Get input from user
void pa::IOSPlatform::pollEvents()
{
    // TODO?
}

// Intent
void pa::IOSPlatform::openUrl(const char* url)
{
	NSString* string = [NSString stringWithUTF8String:url];
	
	dispatch_async(dispatch_get_main_queue(), ^{
		
		[[UIApplication sharedApplication] openURL:[NSURL URLWithString:string]];
	});
}
