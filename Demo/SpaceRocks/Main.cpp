#include <Pineapple/Pineapple.h>

#include "Level.h"
#include "Resource.h"

int pa::Main(pa::Arguments* arguments)
{
	// Start up platform
	pa::PlatformSettings settings;
	settings.title = "Asteroids";
	settings.graphics.size.set(640, 640);

	auto platform = pa::Make::platform(arguments, settings);

	g_resource.create(platform);

	pa::Asset::load(*platform->getGraphics());

	platform->getGraphics()->getResourceManager().loadAll();
	platform->getSound()->getResourceManager().loadAll();

	// Initialise the platform
	pa::World world(platform);

	// First Object
	world.create<Level>();

	// Process main loop
	while (true)
	{
		platform->pollEvents();
		auto& input = platform->getInput();

		if (!world.step(pa::Time(1.f / 60.f), input))
		{
			break;
		}

		platform->idle();
	}

	return 0;
}