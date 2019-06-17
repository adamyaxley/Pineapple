/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

//
//  AppDelegate.h
//  ninjacat
//
//  Created by apple on 01/08/2014.
//  Copyright (c) 2014 Pineapple. All rights reserved.
//

#import <GLKit/GLKit.h>
#import <UIKit/UIKit.h>

//@class ViewController;

@interface AppDelegate : UIResponder<UIApplicationDelegate>

@property(strong) UIWindow* window;

@property(strong) EAGLContext* context;

@end
