#import "ViewController.h"

#include <Pineapple/Platform/IOS/IOSBridge.h>

@implementation paViewController

#pragma mark - GLKViewDelegate

- (void)viewDidLoad
{
	[super viewDidLoad];
	// Not called for some reason, because im not loading from a nib file?
	
	pa::Log::info("viewDidLoad");
}

- (void)viewDidAppear:(BOOL)animated
{
	[super viewDidAppear:animated];
	
	pa::Log::info("viewDidAppear animated=%s", animated ? "T" : "F");
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
	pa::Log::info("didRotateFromInterfaceOrientation");
	
	// grab the window frame and adjust it for orientation
	UIView *rootView = [[[UIApplication sharedApplication] keyWindow]
						rootViewController].view;
	CGRect originalFrame = [[UIScreen mainScreen] bounds];
	CGRect adjustedFrame = [rootView convertRect:originalFrame fromView:nil];
	
	pa::IOSBridge::getPlatform()->makeGraphics(adjustedFrame.size.width, adjustedFrame.size.height);
}

- (void)registerTouches:(NSSet *)touches withEvent:(UIEvent *)event
{
	UITouch* touch = [[event touchesForView:self.view] anyObject];
	
	CGPoint location = [touch locationInView:self.view];
	
	// Adjust to user screen size
	float x = location.x;
	float y = location.y;
	
	auto graphicsSize = pa::IOSBridge::getPlatform()->getGraphics()->getSize();
	auto platformSize = pa::IOSBridge::getPlatform()->getSize();

	float xRatio = (float)graphicsSize.x / (float)platformSize.x;
	float yRatio = (float)graphicsSize.y / (float)platformSize.y;
	
	x *= xRatio;
	y *= yRatio;
	
	pa::IOSBridge::getPlatform()->getPointer().setDown(true);
	pa::IOSBridge::getPlatform()->getPointer().setPosition(x, y);
}

- (void)unregisterTouches:(NSSet *)touches withEvent:(UIEvent *)event
{
	pa::IOSBridge::getPlatform()->getPointer().setDown(false);
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
	pa::IOSBridge::getFrameStartThreadSignal().sync();
	
	pa::IOSBridge::getPlatform()->getGraphics()->render();
	
	pa::IOSBridge::getFrameEndThreadSignal().sync();
}

#pragma mark - GLKViewControllerDelegate

- (void)glkViewControllerUpdate:(GLKViewController *)controller
{
	
}

@end
