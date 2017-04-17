#include <Pineapple/Pineapple.h>

struct Scene : public pa::Object, public pa::InputHandler, public pa::TimerHandler
{
	Scene(pa::World& world)
		: pa::Object(world)
		, pa::InputHandler(world)
		, pa::TimerHandler(world)
	{
	}

	void onCreate()
	{
		startTimer(pa::Time(1.f), [this] { pa::Log::info("Time: {}", getWorld().getTime().count()); }, true);

		pa::Log::info("Hello World");
	}

	void onStep()
	{
		const pa::Pointer& pointer = getWorld().getPlatform()->getPointer();

		if (pointer.getDown())
		{
			pa::Log::info("Touch: ({}, {})", pointer.getPosition().x, pointer.getPosition().y);
		}
	}

	void onKeyPress(pa::Key key)
	{
		pa::Log::info("Key pressed: {}", static_cast<int>(key));
	}

	void onQuit()
	{
		pa::Log::info("Bye bye! {}", rand());
		getWorld().end();
	}
};

int pa::Main(pa::Arguments* arguments)
{
	// Start up platform
	pa::PlatformSettings settings;
	settings.title = "Pineapple";
	settings.graphics.size.cart(640, 480);

	auto platform = pa::Make::platform(arguments, settings);

	// Create the world
	pa::World world(platform);

	// Create the first instance
	world.create<Scene>();

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