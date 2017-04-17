#include <Pineapple/Pineapple.h>
#include <random>

struct Block : public pa::Entity
{
	Block(pa::World& world, std::shared_ptr<pa::Texture> texture)
		: pa::Entity(world)
	{
		setSprite(texture->createSprite());
	}
};

struct Clown : public pa::Entity, public pa::TimerHandler
{
	std::mt19937 generator;
	std::uniform_int_distribution<int> directionDistribution{0, 7};
	Clown(pa::World& world, std::shared_ptr<pa::Texture> texture)
		: pa::Entity(world)
		, pa::TimerHandler(world)
	{
		setSprite(texture->createSprite());
		startTimer(pa::Time(1.0f),
				   [this] { getVelocity().polar(256.f, 2 * PA_PI * directionDistribution(generator) / 8); }, true);
	}

	void onStep(pa::Time deltaTime) override
	{
		pa::Entity::onStep(deltaTime);

		for (auto&& block : getWorld().getList<Block>())
		{
			float entryTime;
			pa::Vect2<float> response;
			if (getAABB().collidesWithStatic(block->getAABB(), entryTime, response))
			{
				if (response.x != 0)
				{
					getVelocity().x *= -1;
				}
				else
				{
					getVelocity().y *= -1;
				}
				break;
			}
		}
	}
};

struct Level : public pa::Object, public pa::InputHandler
{
	std::unique_ptr<pa::Map> m_back;
	std::shared_ptr<Clown> m_clown;

	Level(pa::World& world)
		: pa::Object(world)
		, pa::InputHandler(world)
	{
		auto backTileSet = world.getPlatform()->getGraphics()->createTileSet("back.png", 96, 96);
		backTileSet->load();
		m_back = backTileSet->createPlainWrappedMap(0, 0);

		// Create blocks
		auto blockTexture = world.getPlatform()->getGraphics()->createTexture("block.png");
		blockTexture->load();
		for (int i = 0; i < world.getPlatform()->getGraphics()->getSize().x / 32; i++)
		{
			world.create<Block>(blockTexture)->setPosition(16.f + i * 32, 16.f);
		}
		for (int i = 0; i < world.getPlatform()->getGraphics()->getSize().x / 32; i++)
		{
			world.create<Block>(blockTexture)
				->setPosition(16.f + i * 32, world.getPlatform()->getGraphics()->getSize().y - 16.f);
		}
		for (int i = 0; i < world.getPlatform()->getGraphics()->getSize().y / 32 - 2; i++)
		{
			world.create<Block>(blockTexture)->setPosition(16.f, 48.f + i * 32);
		}
		for (int i = 0; i < world.getPlatform()->getGraphics()->getSize().y / 32 - 2; i++)
		{
			world.create<Block>(blockTexture)
				->setPosition(world.getPlatform()->getGraphics()->getSize().x - 16.f, 48.f + i * 32);
		}

		// Create clown
		auto clownTexture = world.getPlatform()->getGraphics()->createTexture("clown.png");
		clownTexture->load();
		m_clown = world.create<Clown>(clownTexture);
		m_clown->getPosition() = world.getPlatform()->getGraphics()->getSize() / 2.f;
	}

	void onStep(pa::Time deltaTime) override
	{
		if (getWorld().getPlatform()->getPointer().getDown())
		{
			if ((m_clown->getPosition() - getWorld().getPlatform()->getPointer().getPosition()).length() < 16)
			{
				m_clown->getPosition() = getWorld().getPlatform()->getGraphics()->getSize() / 2.f;
				m_clown->getVelocity().cart(0, 0);
			}
		}
	}

	void onQuit()
	{
		getWorld().end();
	}
};

int pa::Main(pa::Arguments* arguments)
{
	// Start up platform
	pa::PlatformSettings settings;
	settings.title = "Catch The Clown";
	settings.graphics.size.cart(640, 480);
	auto platform = pa::Make::platform(arguments, settings);

	// Initialise the world
	pa::World world(platform);

	// Create the Level object
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
