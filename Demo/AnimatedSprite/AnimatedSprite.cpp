#include <Pineapple/Pineapple.h>

struct OldMan : pa::Object
{
	OldMan(pa::World& world, std::unique_ptr<pa::Sprite> sprite)
		: pa::Object(world)
		, m_sprite(std::move(sprite))
	{
		m_sprite->setPosition({ 320, 240 });
		m_sprite->setScale(15.f);
	}

	void onStep(pa::Time delta) override
	{
		// Increment the animation
		if (m_sprite->getFrame() == 0)
		{
			m_sprite->setPlaybackMode(pa::Sprite::PlaybackMode::Forward);
		}
		else if (m_sprite->getFrame() == 2)
		{
			m_sprite->setPlaybackMode(pa::Sprite::PlaybackMode::Backward);
		}
	}

	std::unique_ptr<pa::Sprite> m_sprite;
};

int pa::Main(pa::Arguments* arguments)
{
	// Start up platform
	pa::PlatformSettings settings;
	settings.title = "Pineapple";
	settings.graphics.size.cart(640, 480);

	auto platform = pa::Make::platform(arguments, settings);

	// Load our sprite sheet
	auto spriteSheet = platform->getGraphics()->createTexture("StarChar1.png");
	spriteSheet->load();

	// Specify the frames that we want
	std::vector<std::shared_ptr<pa::Texture>> frames;
	for (int i = 0; i < 3; i++)
	{
		const int frameWidth = 16;
		const int frameHeight = 24;

		auto frame = spriteSheet->createTexture((i + 9) * frameWidth, 0, frameWidth, frameHeight);
		frame->load();
		frames.push_back(std::move(frame));
	}

	// Create a sprite from those frames
	auto oldManSprite = platform->getGraphics()->createSprite(std::move(frames));

	// Create the world
	pa::World world(platform);

	// Create the first instance
	world.create<OldMan>(std::move(oldManSprite));

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