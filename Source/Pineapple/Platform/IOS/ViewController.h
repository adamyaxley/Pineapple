/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

//
//  ViewController.h
//  IOS
//
//  Created by apple on 10/08/2014.
//  Copyright (c) 2014 Pineapple. All rights reserved.
//

#import <GLKit/GLKit.h>

@interface ViewController : GLKViewController<GLKViewDelegate>

- (void)registerTouches:(NSSet*)touches withEvent:(UIEvent*)event;

- (void)unregisterTouches:(NSSet*)touches withEvent:(UIEvent*)event;

@end
