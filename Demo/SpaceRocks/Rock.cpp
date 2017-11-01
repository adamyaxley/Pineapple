#include "Rock.h"
#include "Resource.h"

std::mt19937 Rock::gen;

Rock::Rock(pa::World& world)
	: Warp(world)
	, pa::EnableChildList<Rock>(world)
{
}

void Rock::onCreate()
{
	setSprite(g_resource.rock->createSprite());

	std::uniform_real_distribution<float> rotationDis(0.1f, PA_PI / 18.f);
	std::uniform_int_distribution<int> speedDis(50, 100);
	std::uniform_real_distribution<float> directionDis(0.f, 2.f * PA_PI);

	m_rotation = rotationDis(gen);
	getVelocity().polar(speedDis(gen), directionDis(gen));
}

void Rock::onStep(pa::Time deltaTime)
{
	getSprite()->setRotation(getSprite()->getRotation() + m_rotation);
	Warp::onStep(deltaTime);
}

void Rock::onDestroy()
{
	g_resource.destroy->play();

	for (int i = 0; i < 2; i++)
	{
		getWorld().create<SmallRock>()->getPosition() = getPosition();
	}
}

SmallRock::SmallRock(pa::World& world)
	: Rock(world)
{
}

void SmallRock::onCreate()
{
	setSprite(g_resource.smallRock->createSprite());

	std::uniform_real_distribution<float> rotationDis(0.1f, PA_PI / 12.f);
	std::uniform_int_distribution<int> speedDis(100, 200);
	std::uniform_real_distribution<float> directionDis(0.f, 2.f * PA_PI);

	m_rotation = rotationDis(gen);
	getVelocity().polar(speedDis(gen) + 3.0f, directionDis(gen));
}

void SmallRock::onDestroy()
{
	g_resource.destroy->play();
}