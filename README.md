# Pineapple [![License: Zlib](https://img.shields.io/badge/License-Zlib-brightgreen.svg)](https://opensource.org/licenses/Zlib)
2D game engine utilizing modern C++ to provide an intuitive API and a decoupled plugin system.

Note: this software is ALPHA, it is not stable, it's API can and will change.

|              | Win64 | Win32 |
|:------------:|:----: |:-----:|
| Build & Test | [![Build](https://ci.appveyor.com/api/projects/status/77denkuux6smnk7j?svg=true)](https://ci.appveyor.com/project/Adam19855/pineapple-8gctu) | [![Build](https://ci.appveyor.com/api/projects/status/y9r29elqeg6hy7na?svg=true)](https://ci.appveyor.com/project/Adam19855/pineapple) |



## Goals
The following are the primary goals for this project:
* Cross-Platform
* Realtime Resource Modification
* Modern C++
* Intuitive and Concise API
* Minimal Dependencies

## Architecture
### Engine
The engine consists of one or more Worlds that contain zero or more Objects. The World is responsible for stepping the Objects forward in time based on some Input, storing newly created Objects, and removing any Objects that were destroyed. This simulation loop is executed indefinitely until the world is manually ended.

A simple but complete Hello World in Pineapple could be:

```c++
#include <Pineapple/Pineapple.h>

struct HelloWorld : public pa::Object
{
	HelloWorld(pa::World& world)
		: pa::Object(world)
	{
		pa::Log::info("Hello World");
		getWorld().end();
	}
};

int main()
{
	// Create the world
	pa::World world;

	// Create the first object
	world.create<HelloWorld>();

	// Process main loop without any Input
	while (world.step(pa::Time(1.f / 60.f)));

	return 0;
}
```

### Plugins
There are three types of plugins: Platform, Graphics and Sound. The interface for each plugin type is predefined and set in stone and therefore makes plugins of the same type completely interchangeable.

Currently the following plugins are provided:
* Platform
  * Windows - Win32 application 32/64bit (tested on Windows 10)
  * X11 - Unix with X Window System (tested on Ubuntu)
  * Android - Native application with some java code (tested with NDK r18b)
* Graphics
  * OpenGL - OpenGL rendering (uses [glad](https://github.com/Dav1dde/glad), [stb_image/stb_truetype](https://github.com/nothings/stb), [fontstash](https://github.com/memononen/fontstash) and [glm](https://github.com/g-truc/glm))
    * OpenGL 4.1 (Compatibility mode) on Windows and Unix
    * OpenGLES 1.0 on Android
* Sound
  * FMOD - FMOD wrapper (requires FMOD installation)
  * SoundPool - Android SoundPool wrapper

## Build
To build the source, demos and tests you will need the following:
* [CMake](https://cmake.org/) 3.8
* [FMOD](http://www.fmod.org/download) (required for the FMOD sound plugin)

It is recommended to do an out of source build, to avoid polluting the source tree. Run the following:
```
mkdir builddir
cd builddir
cmake ..
```
You can give a specific generator to cmake using the -G flag. The following generators are supported:
* Win32 - "Visual Studio 15 2017"
* Win64 - "Visual Studio 15 2017 Win64"
* Unix - Use the default (not actively tested)

For Android use Android Studio to load the root Pineapple CMakeLists.txt file.

Note: To run the tests within Visual Studio you will need to install the [Google Test Adapter](https://github.com/csoltenborn/GoogleTestAdapter), which can be installed via Tools -> Extensions and Updates. For Visual Studio 2017 there is an official [Test Adapter for Google Test](https://marketplace.visualstudio.com/items?itemName=VisualCPPTeam.TestAdapterforGoogleTest) that is maintained by the Visual C++ Team.

Please create an issue if you experience any problems (likely!)

## Tutorial
TODO

## How can you help?
Please download the source and build the demos. If there are any problems, or if you have suggestions then create an issue and I will follow up as soon as I can. Pull requests are also welcome for fixes (please create an issue first).
