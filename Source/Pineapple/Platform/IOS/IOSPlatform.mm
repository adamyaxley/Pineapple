#include <Pineapple/Graphics/Base/Graphics.h>
#include <Pineapple/Platform/IOS/IOSPlatform.h>
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
	// arguments will be nullptr
	return std::make_shared<pa::IOSPlatform>(settings);
}

namespace
{
	pthread_t g_applicationThread;
	
	void* applicationThreadFunc(void*)
	{
		pa::Main(nullptr);
		
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
	
	result = pthread_create(&g_applicationThread, &attr, &applicationThreadFunc, nullptr);
	
	@autoreleasepool
	{
		UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
	}
	
	// Will never execute since UIApplicationMain never returns
	return 0;
}

pa::IOSPlatform::IOSPlatform(const PlatformSettings& settings)
	: pa::Platform(settings)
{
	m_fileSystem = pa::MakeInternal::fileSystem(settings.fileSystem);

	pa::IOSBridge::setPlatform(this);
		
	// Notify that the platform has loaded
	pa::IOSBridge::getPlatformInitThreadSignal().sync();

	// Wait until graphics has loaded
	pa::IOSBridge::getGraphicsInitThreadSignal().sync();
	
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

void pa::IOSPlatform::makeGraphics(int surfaceWidth, int surfaceHeight);
{
	if (!m_graphics)
	{
		m_graphics = pa::MakeInternal::graphics(m_settings.graphics, *m_fileSystem.get());
	}

	m_size.set(surfaceWidth, surfaceHeight);
	m_graphics->resize(pa::Graphics::ResizeMode::FillMin, m_size); // TODO set this from graphics setting
}

pa::Pointer& pa::IOSPlatform::getPointer()
{
	return m_pointer;
}
