#include <Pineapple/Pineapple.h>

struct Creature : public pa::Object, public pa::InputHandler
{
	Creature(pa::World& world, std::unique_ptr<pa::Sprite> sprite)
		: pa::Object(world)
		, pa::InputHandler(world)
		, m_sprite(std::move(sprite))
	{
		m_sprite->setPosition({ 320, 240 });
		m_sprite->setScale(5.f);
	}

	void onKeyDown(pa::Key key) override
	{
		const int speed = 3;
		
		switch (key)
		{
		case pa::Key::Left:
			m_increment.x -= speed;
			break;
		case pa::Key::Right:
			m_increment.x += speed;
			break;
		case pa::Key::Up:
			m_increment.y -= speed;
			break;
		case pa::Key::Down:
			m_increment.y += speed;
			break;
		}
	}

	void onStep(pa::Time delta) override
	{
		const unsigned int standingIndexes[] = { 1, 4, 7 };

		const unsigned int walkingIndexes[3][4] = {
			{ 0, 1, 2, 1 },
			{ 3, 4, 5, 4 },
			{ 6, 7, 8, 7 }
		};

		bool standing = false;

		if (m_increment.x > 0)
		{
			m_walkingIndex = 2;
			m_walkingFlip = true;
		}
		else if (m_increment.x < 0)
		{
			m_walkingIndex = 2;
			m_walkingFlip = false;
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
		m_increment = { 0, 0 };

		m_sprite->setHFlip(m_walkingFlip);

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
	}

	std::unique_ptr<pa::Sprite> m_sprite;
	pa::Vect2<int> m_increment{ 0, 0 };
	int m_walkingIndex{ 1 };
	int m_walkingSteps{ 0 };
	bool m_walkingFlip{ false };
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

		int x = i % 3;
		int y = i / 3;

		auto frame = spriteSheet->createTexture(x * frameWidth, y * frameHeight, frameWidth, frameHeight);
		frame->load();
		frames.push_back(std::move(frame));
	}

	// Create a sprite from those frames
	auto creatureSprite = platform->getGraphics()->createSprite(std::move(frames));

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