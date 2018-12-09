#include <Pineapple/Engine/System/InputHandler.h>
#include <Pineapple/Engine/System/World.h>
#include <Pineapple/Engine/System/Object.h>
#include "gmock/gmock.h"
#include "gtest/gtest.h"

template <int N>
struct TestStress : public pa::Object
{
	int life = N;

	TestStress(pa::World& world)
		: pa::Object(world)
	{
	}

	virtual void onStep(pa::Time delta) override
	{
		if (--life == 0)
		{
			destroy();
		}
	}
};

TEST(EngineStress, World) // Release 35
{
	for (int i = 0; i < 10; i++)
	{
		pa::World world;

		for (int j = 0; j < 1000; j++)
		{
			world.create<TestStress<0>>();
			world.create<TestStress<1>>();
			world.create<TestStress<2>>();
			world.create<TestStress<3>>();
			world.create<TestStress<4>>();
			world.create<TestStress<5>>();
			world.create<TestStress<6>>();
			world.create<TestStress<7>>();
			world.create<TestStress<8>>();
			world.create<TestStress<9>>();
			world.create<TestStress<10>>();
			world.step(pa::Time(0.f));
		}
	}
}