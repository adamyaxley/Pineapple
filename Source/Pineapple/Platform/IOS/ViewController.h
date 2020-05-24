#import <GLKit/GLKit.h>

@interface paViewController : GLKViewController<GLKViewDelegate>

- (void)registerTouches:(NSSet*)touches withEvent:(UIEvent*)event;

- (void)unregisterTouches:(NSSet*)touches withEvent:(UIEvent*)event;

@end
