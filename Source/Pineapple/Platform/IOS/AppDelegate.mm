//
//  AppDelegate.m
//  ninjacat
//
//  Created by apple on 01/08/2014.
//  Copyright (c) 2014 Pineapple. All rights reserved.
//

#import "AppDelegate.h"
#import "paViewController.h"

#include <Pineapple/Graphics/Base/paGraphics.hpp>
#include <Pineapple/Platform/IOS/paIOSBridge.h>

#define PA_NO_UTIL_GL_FTGL
#include <Pineapple/Graphics/OpenGL/paUtilGL.hpp>

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
	
	self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
	
	if (!self.context)
	{
		paPlatform::print("context is null");
	}
	
	paIOSBridge::setUIContext(self.context);
	
	paViewController * viewController = [[paViewController alloc] initWithNibName:nil bundle:nil];
	
    GLKView *view = [[GLKView alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    view.context = self.context;
    view.delegate = viewController;
	view.drawableDepthFormat = GLKViewDrawableDepthFormat16;
	view.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
	view.drawableStencilFormat = GLKViewDrawableStencilFormatNone;
	view.drawableMultisample = GLKViewDrawableMultisampleNone;
    
    viewController.view = view;
    //viewController.delegate = viewController;
    viewController.preferredFramesPerSecond = 60;
    self.window.rootViewController = viewController;
	
    self.window.backgroundColor = [UIColor whiteColor];
    [self.window makeKeyAndVisible];
	
	if (![EAGLContext setCurrentContext:self.context])
	{
		paPlatform::print("Could not set current context after didFinishLaunchingWithOptions");
	}
	
	// grab the window frame and adjust it for orientation
	UIView *rootView = [[[UIApplication sharedApplication] keyWindow]
						rootViewController].view;
	CGRect originalFrame = [[UIScreen mainScreen] bounds];
	CGRect adjustedFrame = [rootView convertRect:originalFrame fromView:nil];
	
	paIOSBridge::setDeviceSize(adjustedFrame.size.width, adjustedFrame.size.height);
	
	// Start up graphics
    paGraphics::startup(adjustedFrame.size.width, adjustedFrame.size.height);
	PA_GL_CHECK_ERROR();
	
	//paPlatform::print("2getInitThreadSignal().sync()");
	paIOSBridge::getInitThreadSignal().sync();
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
	paPlatform::print("applicationWillResignActive");
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
	paPlatform::print("applicationDidEnterBackground");
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
	paPlatform::print("applicationWillEnterForeground");
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
	paPlatform::print("applicationDidBecomeActive");
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
	paPlatform::print("applicationWillTerminate");
}

/*-(void)dealloc
{
    paGraphics::shutdown();
    
    if ([EAGLContext currentContext] == self.context)
    {
        [EAGLContext setCurrentContext:nil];
    }
    [super dealloc]; // might not be neded
}

#pragma mark - GLKViewDelegate

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
	paIOSBridge::getFrameStartThreadSignal().sync();
	
	paGraphics::render();
	PA_GL_CHECK_ERROR();
	
	paIOSBridge::getFrameEndThreadSignal().sync();
}

#pragma mark - GLKViewControllerDelegate

- (void)glkViewControllerUpdate:(GLKViewController *)controller
{
	
}*/

@end
