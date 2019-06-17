#include <Pineapple/Core/Platform/paPlatform.hpp>
#include <Pineapple/Graphics/Base/paGraphics.hpp>
#include <Pineapple/Platform/IOS/AppDelegate.h>
#include <Pineapple/Platform/IOS/paIOSBridge.h>

#include <cstdlib>
#include <sys/time.h>
#include <pthread.h>

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <QuartzCore/CAAnimation.h>

#define PA_NO_UTIL_GL_FTGL
#include <Pineapple/Graphics/OpenGL/paUtilGL.hpp>

namespace
{
    paLinkedList<paEvent> g_events;
	
	pthread_t g_applicationThread;
	
	void* paMainThread(void*)
	{
		paMain();
		
		return PA_NULL;
	}
}

int main(int argc, char* argv[])
{
	// Create our client thread
	pthread_attr_t attr;
	
	int result;
	
	result = pthread_attr_init(&attr);
	
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	
	result = pthread_create(&g_applicationThread, &attr, &paMainThread, PA_NULL);
	
	@autoreleasepool
	{
		UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
	}
	
	// Will never execute since UIApplicationMain never returns
	return 0;
}

// Startup and shutdown
bool paPlatform::startup(int width, int height, const char* title, unsigned int flags)
{
	paIOSBridge::setUserSize(width, height);
		
	// wait until app has loaded
	paIOSBridge::getInitThreadSignal().sync();
	
	// Create shared context for loading textures and other resources
	EAGLContext* sharedContext = [[EAGLContext alloc] initWithAPI:[paIOSBridge::getUIContext() API] sharegroup:[paIOSBridge::getUIContext() sharegroup]];
	
	if (!sharedContext)
	{
		paPlatform::print("sharedContext is null");
	}
	
	if (![EAGLContext setCurrentContext:sharedContext])
	{
		paPlatform::print("Could not set current sharedContext after init");
	}
	
	// Resize our window to fit what the user gave us
	paGraphics::resizeKeepAspectRatio(width, height);
	
	return true;
}

bool paPlatform::shutdown()
{
    // issue exit TODO
    
    // join app thread
	return true;
}

// Get input from user
void paPlatform::pollEvents()
{
    
}

paLinkedList<paEvent>& paPlatform::getEvents()
{
    return g_events;
}

paDeviceState paPlatform::queryDevice(paDeviceEnum)
{
	return paIOSBridge::getTouchPosition();
}

// Threading
void paPlatform::async(void(*)(void))
{
    // not implemented
}

// Idle
void paPlatform::idle()
{
	// Use barriers to allow the UI thread to render at the correct time.
    paIOSBridge::getFrameStartThreadSignal().sync();
	paIOSBridge::getFrameEndThreadSignal().sync();
}

// Utility
double paPlatform::getTime()
{
    /*timeval time;
    gettimeofday(&time, PA_NULL);
    
    return (double)time.tv_sec + (double)time.tv_usec / 1.0e06;*/
	
	//return CACurrentMediaTime();
	
	return (1.0 / 60.0) * getTicks();
}

int paPlatform::random()
{
    return rand();
}

// Intent
void paPlatform::openUrl(const char* url)
{
	NSString* string = [NSString stringWithUTF8String:url];
	
	dispatch_async(dispatch_get_main_queue(), ^{
		
		[[UIApplication sharedApplication] openURL:[NSURL URLWithString:string]];
	});
}

// Memory
void* paPlatform::allocate(unsigned long size)
{
    return malloc(size);
}

void paPlatform::deallocate(void* ptr)
{
    free(ptr);
}

void* paPlatform::reallocate(void* ptr, unsigned long size)
{
    return realloc(ptr, size);
}

// Standard print with formatting
int paPlatform::print(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    NSLogv([NSString stringWithUTF8String:format], args);
    va_end(args);
    
    return 0; // Need to return how many chars printed
}

// Debugging
void paPlatform::breakpoint()
{
    
}