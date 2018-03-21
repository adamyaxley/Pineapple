#include <Pineapple/Pineapple.h>

namespace resource
{
	std::shared_ptr<pa::Font> font1, font2, font3, font4;
}

struct Scene : public pa::Object, public pa::InputHandler
{
	Scene(pa::World& world)
		: pa::Object(world)
		, pa::InputHandler(world)
	{
		text1 = resource::font1->createText();
		text1->setText("EarlyGameBoy.ttf the quick brown fox jumps over the lazy dog");
		text1->setPosition(400, 20);
		text1->setColour(pa::ColourSet::Green);
		text1->setOrigin(text1->getSize() / 2);

		text2 = resource::font2->createText();
		text2->setText("UpheavelPro.ttf the quick brown fox jumps over the lazy dog");
		text2->setPosition(400, 40);
		text2->setColour(pa::ColourSet::Red);
		text2->setOutlineColour(pa::ColourSet::White);
		text2->setOutline(1);
		text2->setOrigin(text2->getSize() / 2);

		text3 = resource::font3->createText();
		text3->setText("RioGrande.ttf the quick brown fox jumps over the lazy dog");
		text3->setPosition(400, 240);
		text3->setColour(pa::ColourSet::White);
		text3->setOrigin(text3->getSize() / 2);

		text4 = resource::font4->createText();
		text4->setText("Fipps-Regular.otf the quick brown fox jumps over the lazy dog");
		text4->setPosition(400, 340);
		text4->setColour(pa::ColourSet::White);
		text4->setOrigin(text4->getSize() / 2);
	}

	void onQuit() override
	{
		getWorld().end();
	}

	std::unique_ptr<pa::Text> text1, text2, text3, text4;
};

int pa::Main(pa::Arguments* arguments)
{
	// Start up platform
	pa::PlatformSettings settings;
	settings.title = "Pineapple - Text";
	settings.graphics.size.set(800, 480);
	settings.sound.use = false;

	auto platform = pa::Make::platform(arguments, settings);

	resource::font1 = platform->getGraphics()->createFont("EarlyGameBoy.ttf");
	resource::font1->setSize(20);

	resource::font2 = platform->getGraphics()->createFont("UpheavalPro.ttf");
	resource::font2->setSize(30);

	resource::font3 = platform->getGraphics()->createFont("RioGrande.ttf");
	resource::font3->setSize(200);

	resource::font4 = platform->getGraphics()->createFont("Fipps-Regular.otf");
	resource::font4->setSize(60);

	platform->getGraphics()->getResourceManager().loadAll();

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