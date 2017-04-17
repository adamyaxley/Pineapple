# Pineapple
2D game engine utilizing modern C++ to provide an intuitive API and a decoupled plugin system.

Note: this software is ALPHA, it is not stable, and it's API can and will change.

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
  * paOpenGL - OpenGL rendering (uses [stb_image/stb_truetype](https://github.com/nothings/stb), [fontstash](https://github.com/memononen/fontstash) and [glm](https://github.com/g-truc/glm))
* Sound
  * paFMOD - FMOD backend (requires FMOD)

## Tutorial
TODO

## How can you help?
Please download the source and build the demos. If there are any problems, or if you have suggestions for then create an issue and I will follow up as soon as I can. Pull requests are also welcome.
