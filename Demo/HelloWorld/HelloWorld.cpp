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
	while (world.step(pa::Time(1.f / 60.f)))
		;

	return 0;
}