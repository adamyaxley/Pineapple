//
//  paViewController.m
//  paIOS
//
//  Created by apple on 10/08/2014.
//  Copyright (c) 2014 Pineapple. All rights reserved.
//

#import "paViewController.h"

#include <Pineapple/Platform/IOS/paIOSBridge.h>
#include <Pineapple/Graphics/Base/paGraphics.hpp>

@implementation paViewController

#pragma mark - GLKViewDelegate

- (void)viewDidLoad
{
	[super viewDidLoad];
	// Not called for some reason, because im not loading from a nib file?
	
	paPlatform::print("viewDidLoad");
}

- (void)viewDidAppear:(BOOL)animated
{
	[super viewDidAppear:animated];
	
	paPlatform::print("viewDidAppear animated=%s", animated ? "T" : "F");
}

- (NSUInteger)supportedInterfaceOrientations
{
	return UIInterfaceOrientationMaskLandscape;
}

-(BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation
{
	return (toInterfaceOrientation == UIInterfaceOrientationLandscapeLeft ||
			toInterfaceOrientation == UIInterfaceOrientationLandscapeRight);
}

-(BOOL)shouldAutorotate
{
	return YES;
}

-(void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation
{
	// COPY PASTA FOR NOW
	paPlatform::print("didRotateFromInterfaceOrientation");
	
	// grab the window frame and adjust it for orientation
	UIView *rootView = [[[UIApplication sharedApplication] keyWindow]
						rootViewController].view;
	CGRect originalFrame = [[UIScreen mainScreen] bounds];
	CGRect adjustedFrame = [rootView convertRect:originalFrame fromView:nil];
	
	paIOSBridge::setDeviceSize(adjustedFrame.size.width, adjustedFrame.size.height);
	
	// Start up graphics
	paGraphics::resize(adjustedFrame.size.width, adjustedFrame.size.height);
    paGraphics::resizeKeepAspectRatio(paIOSBridge::getUserSize().x, paIOSBridge::getUserSize().y);
}

- (void)registerTouches:(NSSet *)touches withEvent:(UIEvent *)event
{
	UITouch* touch = [[event touchesForView:self.view] anyObject];
	
	CGPoint location = [touch locationInView:self.view];
	
	// Adjust to user screen size
	float x = location.x;
	float y = location.y;
	
	float xRatio = (float)paGraphics::getSize().x / (float)paIOSBridge::getDeviceSize().x;
	float yRatio = (float)paGraphics::getSize().y / (float)paIOSBridge::getDeviceSize().y;
	
	x *= xRatio;
	y *= yRatio;
	
	paIOSBridge::setTouchPosition((int)x, (int)y);
}

- (void)unregisterTouches:(NSSet *)touches withEvent:(UIEvent *)event
{
	paIOSBridge::clearTouchPosition();
}

// TODO fix multitouch bugs

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
	[self registerTouches:touches withEvent:event];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
	[self registerTouches:touches withEvent:event];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	[self unregisterTouches:touches withEvent:event];
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
	[self unregisterTouches:touches withEvent:event];
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
	paIOSBridge::getFrameStartThreadSignal().sync();
	
	paGraphics::render();
	
	paIOSBridge::getFrameEndThreadSignal().sync();
}

#pragma mark - GLKViewControllerDelegate

- (void)glkViewControllerUpdate:(GLKViewController *)controller
{
	
}

@end
