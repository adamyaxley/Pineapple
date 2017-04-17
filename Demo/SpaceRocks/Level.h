#include <Pineapple/Pineapple.h>

class Level : public pa::Object, public pa::InputHandler
{
public:
	Level(pa::World& world);

	void onCreate() override;
	void onStep(pa::Time deltaTime) override;
	void onQuit() override
	{
		getWorld().end();
	}

	std::unique_ptr<pa::Map> m_background;
};
