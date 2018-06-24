#include <Pineapple/Engine/System/TimerHandler.h>
#include <Pineapple/Engine/System/World.h>
#include <Pineapple/Engine/System/Object.h>
#include "gmock/gmock.h"
#include "gtest/gtest.h"

struct ObjectSingleTimer : public pa::Object, public pa::TimerHandler
{
	bool check{false};
	ObjectSingleTimer(pa::World& world)
		: pa::Object(world)
		, pa::TimerHandler(world)
	{
		startTimer(pa::Time(1.f), [this] { check = true; });
	}
};

TEST(Timer, Single)
{
	pa::World world;
	auto object = world.create<ObjectSingleTimer>();

	world.step(pa::Time(0.9f));
	ASSERT_FALSE(object->check);
	world.step(pa::Time(0.2f));
	ASSERT_TRUE(object->check);
}

struct ObjectDestroyTimer : public pa::Object, public pa::TimerHandler
{
	ObjectDestroyTimer(pa::World& world)
		: pa::Object(world)
		, pa::TimerHandler(world)
	{
		startTimer(pa::Time(1.f), [this] { destroy(); });
	}
};

TEST(Timer, DestroyObject)
{
	pa::World world;
	world.create<ObjectDestroyTimer>();
	world.step(pa::Time(0.9f));
	ASSERT_FALSE(world.getList<ObjectDestroyTimer>().empty());
	world.step(pa::Time(0.2f));
	ASSERT_TRUE(world.getList<ObjectDestroyTimer>().empty());
}

struct ObjectMultipleTimers : public pa::Object, public pa::TimerHandler
{
	bool first{false};
	bool second{false};

	ObjectMultipleTimers(pa::World& world)
		: pa::Object(world)
		, pa::TimerHandler(world)
	{
		startTimer(pa::Time(1.f), [this] { first = true; });
		startTimer(pa::Time(2.f), [this] { second = true; });
	}
};

TEST(Timer, Multiple)
{
	pa::World world;
	auto object = world.create<ObjectMultipleTimers>();

	world.step(pa::Time(0.9f));
	ASSERT_FALSE(object->first);
	ASSERT_FALSE(object->second);
	world.step(pa::Time(0.2f));
	ASSERT_TRUE(object->first);
	ASSERT_FALSE(object->second);
	world.step(pa::Time(0.8f));
	ASSERT_TRUE(object->first);
	ASSERT_FALSE(object->second);
	world.step(pa::Time(0.2f));
	ASSERT_TRUE(object->first);
	ASSERT_TRUE(object->second);
}

struct ObjectRepeatedTimer : public pa::Object, public pa::TimerHandler
{
	int n{0};

	ObjectRepeatedTimer(pa::World& world)
		: pa::Object(world)
		, pa::TimerHandler(world)
	{
		startTimer(pa::Time(1.f), [this] { n++; }, true);
	}
};

TEST(Timer, Repeat)
{
	pa::World world;
	auto object = world.create<ObjectRepeatedTimer>();

	world.step(pa::Time(5.8f));
	ASSERT_EQ(object->n, 5);
	world.step(pa::Time(0.3f));
	ASSERT_EQ(object->n, 6);
}