# Pineapple [![License: Zlib](https://img.shields.io/badge/License-Zlib-brightgreen.svg)](https://opensource.org/licenses/Zlib)
2D game engine utilizing modern C++ to provide an intuitive API and a decoupled plugin system.

Note: this software is ALPHA, it is not stable, it's API can and will change.

|              | Win32                                                                           |
|:------------:|:------------------------------------------------------------------------------: |
| Build & Test | ![Build](https://ci.appveyor.com/api/projects/status/y9r29elqeg6hy7na?svg=true) |



## Goals
The following are the primary goals for this project:
* Cross-Platform
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
  * paWindows - Win32 application
* Graphics
  * paOpenGL - OpenGL rendering (uses [glew](http://glew.sourceforge.net/), [stb_image/stb_truetype](https://github.com/nothings/stb), [fontstash](https://github.com/memononen/fontstash) and [glm](https://github.com/g-truc/glm))
* Sound
  * paFMOD - FMOD backend (requires FMOD)

## Build
To build the source, demos and tests you will need the following:
* [CMake](https://cmake.org/) 3.8
* [vcpkg](https://github.com/Microsoft/vcpkg) (this is how you will install the glew package, required for the paOpenGL graphics plugin)
  * [glew](http://glew.sourceforge.net/)
* [FMOD](http://www.fmod.org/download) (required for the paFMOD sound plugin)

It is recommended to do an out of source build, to avoid polluting the source tree. Replace `{VCPKG_INSTALL_DIR}` with where you installed vcpkg and run the following:
```
mkdir builddir
cd builddir
cmake .. -DCMAKE_TOOLCHAIN_FILE={VCPKG_INSTALL_DIR}\scripts\buildsystems\vcpkg.cmake
```
Then open the generated Pineapple.sln file and hit build.

Note: To run the tests within Visual Studio you will need to install the [Google Test Adapter](https://github.com/csoltenborn/GoogleTestAdapter), which can be installed via Tools -> Extensions and Updates.

Please create an issue if you experience any problems (likely!)

## Tutorial
TODO

## How can you help?
Please download the source and build the demos. If there are any problems, or if you have suggestions then create an issue and I will follow up as soon as I can. Pull requests are also welcome for fixes (please create an issue first).
