#include <Pineapple/Pineapple.h>

struct Creature : public pa::Object, public pa::InputHandler
{
	Creature(pa::World& world, std::unique_ptr<pa::Sprite> sprite)
		: pa::Object(world)
		, pa::InputHandler(world)
		, m_sprite(std::move(sprite))
	{
		m_sprite->setPosition({320, 240});
		m_sprite->setScale(5.f);
	}

	void onKeyDown(pa::Key key) override
	{
		const int speed = 3;

		switch (key)
		{
		case pa::Key::Left: m_increment.x -= speed; break;
		case pa::Key::Right: m_increment.x += speed; break;
		case pa::Key::Up: m_increment.y -= speed; break;
		case pa::Key::Down: m_increment.y += speed; break;
		}
	}

	void onStep(pa::Time delta) override
	{
		const std::size_t standingIndexes[] = {1, 4, 7};
		const std::size_t walkingIndexes[3][4] = {{0, 1, 2, 1}, {3, 4, 5, 4}, {6, 7, 8, 7}};

		bool standing = false;

		if (m_increment.x > 0)
		{
			m_walkingIndex = 2;
			m_horizontalFlip = true;
		}
		else if (m_increment.x < 0)
		{
			m_walkingIndex = 2;
			m_horizontalFlip = false;
		}
		else if (m_increment.y > 0)
		{
			m_walkingIndex = 1;
		}
		else if (m_increment.y < 0)
		{
			m_walkingIndex = 0;
		}
		else
		{
			standing = true;
		}

		m_sprite->getPosition() += m_increment;
		m_sprite->setHFlip(m_horizontalFlip);

		// Set correct animation based on state
		if (standing)
		{
			m_sprite->setFrame(standingIndexes[m_walkingIndex]);
			m_walkingSteps = 0;
		}
		else
		{
			m_sprite->setFrame(walkingIndexes[m_walkingIndex][(++m_walkingSteps / 6) % 4]);
		}

		m_increment = {0, 0};
	}

	std::unique_ptr<pa::Sprite> m_sprite;
	pa::Vect2<int> m_increment{0, 0};
	std::size_t m_walkingIndex{1};
	std::size_t m_walkingSteps{0};
	bool m_horizontalFlip{false};
};

int pa::Main(pa::Arguments* arguments)
{
	// Start up platform
	pa::PlatformSettings settings;
	settings.title = "Animated Sprite";
	settings.graphics.size.cart(640, 480);
	auto platform = pa::Make::platform(arguments, settings);

	// Load our sprite sheet
	auto spriteSheet = platform->getGraphics()->createTexture("creature.png");
	spriteSheet->load();

	// Specify the frames that we want
	std::vector<std::shared_ptr<pa::Texture>> frames;
	for (int i = 0; i < 12; i++)
	{
		const int frameWidth = 16;
		const int frameHeight = 24;
		const int x = i % 3;
		const int y = i / 3;

		auto frame = spriteSheet->createTexture(x * frameWidth, y * frameHeight, frameWidth, frameHeight);
		frames.push_back(frame);
	}

	// Create a sprite from those frames
	auto creatureSprite = platform->getGraphics()->createSprite(frames);

	// Create a simple background
	auto tileSet = platform->getGraphics()->createTileSet("background.png", 32, 32);
	tileSet->load();
	auto map = tileSet->createMap(nullptr, 0, 0, true, true, -1);

	// Create the world
	pa::World world(platform);

	// Create the first instance
	world.create<Creature>(std::move(creatureSprite));

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