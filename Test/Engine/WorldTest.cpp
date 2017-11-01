#include <Pineapple/Engine/System/InputHandler.h>
#include <Pineapple/Engine/System/TimerHandler.h>
#include <Pineapple/Engine/System/World.h>
#include "gmock/gmock.h"
#include "gtest/gtest.h"

struct TestWorldEndObject : public pa::Object
{
	TestWorldEndObject(pa::World& world)
		: pa::Object(world)
	{
	}

	void onCreate() override
	{
		getWorld().end();
	}
};

struct TestWorldNextSceneObject2;

struct TestWorldNextSceneObject1 : public pa::Object
{
	TestWorldNextSceneObject1(pa::World& world)
		: pa::Object(world)
	{
	}

	void onCreate() override
	{
		getWorld().resetNextStep<TestWorldNextSceneObject2>();
	}
};

struct TestWorldNextSceneObject2 : public pa::Object
{
	TestWorldNextSceneObject2(pa::World& world)
		: pa::Object(world)
	{
	}
};

struct TestWorldNextSceneWithCallbacksObject1 : public pa::Object, public pa::InputHandler
{
	TestWorldNextSceneWithCallbacksObject1(pa::World& world)
		: pa::Object(world)
		, pa::InputHandler(world)
	{
	}
};

struct TestWorldVariadicTemplatesObject : public pa::Object
{
	TestWorldVariadicTemplatesObject(pa::World& world, int x, std::string y)
		: pa::Object(world)
	{
		pa::Log::info("TestWorldVariadicTemplatesObject({}, {})", x, y.c_str());
	}
};

struct TestWorldPerfectForwarding : public pa::Object
{
	const bool success;

	TestWorldPerfectForwarding(pa::World& world, int&& perfect1, int& perfect2)
		: pa::Object(world)
		, success(true)
	{
		perfect2 = 1;
	}

	template <typename T, typename U>
	TestWorldPerfectForwarding(pa::World& world, T&& inperfect1, U&& inperfect2)
		: pa::Object(world)
		, success(false)
	{
	}
};

TEST(World, PerfectForwarding)
{
	{
		int lvalue = 0;
		int& lvalueref = lvalue;

		pa::World world;
		world.create<TestWorldPerfectForwarding>(7, lvalueref);

		ASSERT_EQ(true, (*world.getList<TestWorldPerfectForwarding>().begin())->success);
		ASSERT_EQ(1, lvalueref);
	}

	{
		int lvalue = 0;
		int& lvalueref = lvalue;

		pa::World world;
		world.resetNextStep<TestWorldPerfectForwarding>(7, lvalueref);
		ASSERT_EQ(0, lvalueref);
		world.step(pa::Time(0.f));
		ASSERT_EQ(true, (*world.getList<TestWorldPerfectForwarding>().begin())->success);
		ASSERT_EQ(1, lvalueref);
	}
}

TEST(World, End)
{
	pa::World world;
	bool stillAlive = world.step(pa::Time(0.f));

	ASSERT_EQ(true, stillAlive);

	world.end();
	stillAlive = world.step(pa::Time(0.f));

	ASSERT_EQ(false, stillAlive);
}

TEST(World, Ticks)
{
	pa::World world;

	ASSERT_EQ(0, world.getTicks());

	world.step(pa::Time(0.f));

	ASSERT_EQ(1, world.getTicks());

	world.step(pa::Time(0.f));

	ASSERT_EQ(2, world.getTicks());

	world.step(pa::Time(0.f));

	ASSERT_EQ(3, world.getTicks());
}

TEST(World, NextScene)
{
	pa::World world;

	world.create<TestWorldNextSceneObject1>();

	ASSERT_EQ(1u, world.getList<TestWorldNextSceneObject1>().size());
	ASSERT_EQ(0u, world.getList<TestWorldNextSceneObject2>().size());

	world.step(pa::Time(0.f));

	ASSERT_EQ(0u, world.getList<TestWorldNextSceneObject1>().size());
	ASSERT_EQ(1u, world.getList<TestWorldNextSceneObject2>().size());
}

struct CreatedObjectOnStep : public pa::Object
{
	bool stepped{false};
	CreatedObjectOnStep(pa::World& world)
		: pa::Object(world)
	{
	}

	void onStep(pa::Time deltaTime) override
	{
		stepped = true;
	}
};

struct CreatesObjectOnFirstStep : public pa::Object
{
	CreatesObjectOnFirstStep(pa::World& world)
		: pa::Object(world)
	{
	}

	void onStep(pa::Time deltaTime) override
	{
		if (getWorld().getTicks() == 0)
		{
			getWorld().create<CreatedObjectOnStep>();
			ASSERT_EQ(getWorld().getList<CreatedObjectOnStep>().size(), 1u);
		}
	}
};

TEST(World, CreatingAnObjectDuringStep)
{
	pa::World world;

	world.create<CreatesObjectOnFirstStep>();
	world.step(pa::Time(0.f));
}

TEST(World, CreatedObjectDuringStepIsNotStepped)
{
	{
		pa::World world;

		world.setPriority<CreatesObjectOnFirstStep>(-1);
		world.create<CreatesObjectOnFirstStep>();

		world.step(pa::Time(0.f));
		ASSERT_EQ(false, (*world.getList<CreatedObjectOnStep>().begin())->stepped);

		world.step(pa::Time(0.f));
		ASSERT_EQ(true, (*world.getList<CreatedObjectOnStep>().begin())->stepped);
	}

	{
		pa::World world;

		world.setPriority<CreatedObjectOnStep>(0);
		world.setPriority<CreatesObjectOnFirstStep>(-1);
		world.create<CreatesObjectOnFirstStep>();

		world.step(pa::Time(0.f));
		ASSERT_EQ(false, (*world.getList<CreatedObjectOnStep>().begin())->stepped);

		world.step(pa::Time(0.f));
		ASSERT_EQ(true, (*world.getList<CreatedObjectOnStep>().begin())->stepped);
	}
}

TEST(World, CallbackStepInput)
{
	pa::World world;

	world.create<TestWorldNextSceneWithCallbacksObject1>();

	world.step(pa::Time(0.f));
}

TEST(World, CallbackCleanup)
{
	pa::World world;

	world.create<TestWorldNextSceneWithCallbacksObject1>();
}

TEST(World, VariadicTemplates)
{
	pa::World world;

	// This is a compile time test
	world.create<TestWorldVariadicTemplatesObject>(5, "hello");
}

namespace
{
	struct Base : public pa::Object, private pa::EnableChildList<Base>
	{
		Base(pa::World& world)
			: pa::Object(world)
			, pa::EnableChildList<Base>(this)
		{
		}
	};

	struct Derived : public Base, private pa::EnableChildList<Derived>
	{
		Derived(pa::World& world)
			: Base(world)
			, pa::EnableChildList<Derived>(this)
		{
		}
	};

	struct DerivedDerived : public Derived
	{
		DerivedDerived(pa::World& world)
			: Derived(world)
		{
		}
	};
}

TEST(World, RegisterChildren)
{
	// Guarantee small memory overhead for registering children
	ASSERT_EQ(sizeof(Base), sizeof(pa::Object));

	pa::World world;

	auto base = world.create<Base>();

	ASSERT_EQ(world.getList<Base>().size(), 1u);
	ASSERT_EQ(world.getChildList<Base>().size(), 1u);
	ASSERT_EQ(world.getList<Derived>().size(), 0u);
	ASSERT_EQ(world.getChildList<Derived>().size(), 0u);

	base->destroy();
	world.step(pa::Time(0.f));

	ASSERT_EQ(world.getList<Base>().size(), 0u);
	ASSERT_EQ(world.getChildList<Base>().size(), 0u);
	ASSERT_EQ(world.getList<Derived>().size(), 0u);
	ASSERT_EQ(world.getChildList<Derived>().size(), 0u);

	auto derived = world.create<Derived>();

	ASSERT_EQ(world.getList<Base>().size(), 0u);
	ASSERT_EQ(world.getChildList<Base>().size(), 1u);
	ASSERT_EQ(world.getList<Derived>().size(), 1u);
	ASSERT_EQ(world.getChildList<Derived>().size(), 1u);

	derived->destroy();
	world.step(pa::Time(0.f));

	ASSERT_EQ(world.getList<Base>().size(), 0u);
	ASSERT_EQ(world.getChildList<Base>().size(), 0u);
	ASSERT_EQ(world.getList<Derived>().size(), 0u);
	ASSERT_EQ(world.getChildList<Derived>().size(), 0u);

	auto derivedDerived = world.create<DerivedDerived>();

	ASSERT_EQ(world.getList<Base>().size(), 0u);
	ASSERT_EQ(world.getChildList<Base>().size(), 1u);
	ASSERT_EQ(world.getList<Derived>().size(), 0u);
	ASSERT_EQ(world.getChildList<Derived>().size(), 1u);

	derivedDerived->destroy();
	world.step(pa::Time(0.f));

	ASSERT_EQ(world.getList<Base>().size(), 0u);
	ASSERT_EQ(world.getChildList<Base>().size(), 0u);
	ASSERT_EQ(world.getList<Derived>().size(), 0u);
	ASSERT_EQ(world.getChildList<Derived>().size(), 0u);
}