#include <Pineapple/Pineapple.h>
#include "Warp.h"

class Respawn : public pa::Object, public pa::TimerHandler
{
public:
	Respawn(pa::World& world);
	void onCreate() override;

private:
	pa::AABB aabb;
};

class Player : public Warp, public pa::InputHandler, public pa::TimerHandler
{
public:
	Player(pa::World& world);

	bool canShoot;

	void onCreate() override;
	void onKeyDown(pa::Key key) override;
	void onStep(pa::Time delta) override;
	void onDestroy() override;
};