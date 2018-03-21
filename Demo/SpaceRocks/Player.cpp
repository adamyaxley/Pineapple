#include "Player.h"
#include "Bullet.h"
#include "Rock.h"

Respawn::Respawn(pa::World& world)
	: pa::Object(world)
	, pa::TimerHandler(world)
{
}

void Respawn::onCreate()
{
	aabb.getSize().set(100, 100);
	aabb.getPosition() = getWorld().getPlatform()->getGraphics()->getSize() - aabb.getSize() / 2.f;
	startTimer(pa::Time(2.0f),
			   [this] {
				   for (auto&& rock : getWorld().getChildList<Rock>())
				   {
					   if (!rock->getAABB().calculateSweptAABB().intersects(aabb))
					   {
						   getWorld().create<Player>()->getPosition().set(320, 320);
						   g_resource.respawn->play();
						   destroy();
						   break;
					   }
				   }
			   },
			   true);
}

Player::Player(pa::World& world)
	: Warp(world)
	, pa::InputHandler(world)
	, pa::TimerHandler(world)
{
}

void Player::onCreate()
{
	canShoot = true;
	setSprite(g_resource.ship->createSprite());
	getSprite()->setRotation(270);
	getAABB().getSize().set(28, 28);
}

void Player::onKeyDown(pa::Key key)
{
	pa::Vect2<float> increment;

	switch (key)
	{
	case pa::Key::W:
	case pa::Key::Up:
		increment.polar(5.f, getSprite()->getRotation());
		getVelocity() += increment;
		break;

	case pa::Key::A:
	case pa::Key::Left: getSprite()->setRotation(getSprite()->getRotation() - PA_PI / 60.f); break;

	case pa::Key::D:
	case pa::Key::Right: getSprite()->setRotation(getSprite()->getRotation() + PA_PI / 60.f); break;

	case pa::Key::Space:
	case pa::Key::AButton:
		if (canShoot)
		{
			g_resource.fire->play();
			auto bullet = getWorld().create<Bullet>();
			bullet->getPosition() = getPosition();
			bullet->getVelocity().polar(700.f, getSprite()->getRotation());
			canShoot = false;
			startTimer(pa::Time(0.1f), [&] { canShoot = true; });
		}
	}
}

void Player::onStep(pa::Time delta)
{
	Warp::onStep(delta);

	for (auto&& rock : getWorld().getChildList<Rock>())
	{
		if (rock->getAABB().calculateSweptAABB().intersects(getAABB().calculateSweptAABB()))
		{
			rock->destroy();
			destroy();
			break;
		}
	}
}

void Player::onDestroy()
{
	getWorld().create<Respawn>();
}