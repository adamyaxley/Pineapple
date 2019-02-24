#include <Pineapple/Engine/System/ObjectStore.h>
#include <Pineapple/Engine/System/World.h>
#include <Pineapple/Engine/System/Object.h>
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace
{
	pa::World g_emptyWorld;
}

struct TestObject1 : public pa::Object
{
	TestObject1()
		: pa::Object(g_emptyWorld)
	{
	}
};
struct TestObject2 : public pa::Object
{
	TestObject2()
		: pa::Object(g_emptyWorld)
	{
	}
};
struct TestObject3 : public pa::Object
{
	TestObject3()
		: pa::Object(g_emptyWorld)
	{
	}
};

TEST(ObjectStore, InstanceList)
{
	pa::ObjectStore objectStore;

	objectStore.create<TestObject1>();
	objectStore.create<TestObject1>();

	ASSERT_EQ(2u, objectStore.getList<TestObject1>().size());
}

TEST(ObjectStore, InstanceTable)
{
	pa::ObjectStore objectStore;

	objectStore.create<TestObject1>();
	objectStore.create<TestObject2>();
	objectStore.create<TestObject3>();

	ASSERT_EQ(3u, objectStore.getObjectIds().size());
}

TEST(ObjectStore, PrioritySetGet)
{
	pa::ObjectStore objectStore;

	objectStore.create<TestObject1>();
	objectStore.create<TestObject2>();
	objectStore.create<TestObject3>();

	objectStore.setPriority<TestObject2>(10);
	objectStore.setPriority<TestObject3>(20);
	objectStore.setPriority<TestObject1>(30);

	ASSERT_EQ(10, objectStore.getPriority<TestObject2>());
	ASSERT_EQ(20, objectStore.getPriority<TestObject3>());
	ASSERT_EQ(30, objectStore.getPriority<TestObject1>());
}

TEST(ObjectStore, PriorityOrder)
{
	pa::ObjectStore objectStore;

	objectStore.create<TestObject1>();
	objectStore.create<TestObject2>();
	objectStore.create<TestObject3>();

	objectStore.setPriority<TestObject2>(10);
	objectStore.setPriority<TestObject3>(20);
	objectStore.setPriority<TestObject1>(30);

	auto ids = objectStore.getObjectIds();
	auto iterator = ids.begin();

	ASSERT_EQ(10, objectStore.getObjectInfo(*iterator).getPriority());
	++iterator;

	ASSERT_EQ(20, objectStore.getObjectInfo(*iterator).getPriority());
	++iterator;

	ASSERT_EQ(30, objectStore.getObjectInfo(*iterator).getPriority());
}

TEST(ObjectStore, DefaultPriority)
{
	pa::ObjectStore objectStore;

	objectStore.create<TestObject1>();
	objectStore.setPriority<TestObject1>(10);

	// Create an object with a default priority (0)
	objectStore.create<TestObject2>();

	auto ids = objectStore.getObjectIds();
	auto iterator = ids.begin();

	ASSERT_EQ(0, objectStore.getObjectInfo(*iterator).getPriority());
	++iterator;

	ASSERT_EQ(10, objectStore.getObjectInfo(*iterator).getPriority());
}

TEST(ObjectStore, DeleteDeadInstances)
{
	pa::ObjectStore objectStore;

	objectStore.create<TestObject1>();
	objectStore.create<TestObject1>();
	objectStore.create<TestObject1>()->destroy();
	objectStore.create<TestObject1>();
	objectStore.create<TestObject2>()->destroy();
	objectStore.create<TestObject2>();

	ASSERT_EQ(6u, objectStore.getList<TestObject1>().size() + objectStore.getList<TestObject2>().size());

	objectStore.removeDeadInstances();

	ASSERT_EQ(4u, objectStore.getList<TestObject1>().size() + objectStore.getList<TestObject2>().size());
}

TEST(ObjectStore, DeleteAllInstances)
{
	pa::ObjectStore objectStore;

	objectStore.create<TestObject1>();
	objectStore.create<TestObject1>();
	objectStore.create<TestObject1>();
	objectStore.create<TestObject1>();
	objectStore.create<TestObject2>();
	objectStore.create<TestObject2>();

	ASSERT_EQ(6u, objectStore.getList<TestObject1>().size() + objectStore.getList<TestObject2>().size());

	objectStore.deleteAllInstances();

	ASSERT_EQ(0u, objectStore.getList<TestObject1>().size() + objectStore.getList<TestObject2>().size());
}

TEST(ObjectStore, LifetimeMultiple)
{
	pa::ObjectStore objectStore1;
	pa::ObjectStore objectStore2;

	objectStore1.create<TestObject1>();
	objectStore2.create<TestObject1>();
	objectStore2.create<TestObject1>();
	ASSERT_EQ(1u, objectStore1.getList<TestObject1>().size());
}

TEST(ObjectStore, LifetimeRecreation)
{
	{
		pa::ObjectStore objectStore;
		objectStore.create<TestObject1>();
		objectStore.create<TestObject1>();
	}

	{
		pa::ObjectStore objectStore;
		objectStore.create<TestObject1>();
		objectStore.create<TestObject1>();
		ASSERT_EQ(2u, objectStore.getList<TestObject1>().size());
	}
}

TEST(ObjectStore, LifetimeScoping)
{
	pa::ObjectStore objectStore1;
	objectStore1.create<TestObject1>();

	{
		pa::ObjectStore objectStore2;
		objectStore2.create<TestObject1>();
		objectStore2.create<TestObject1>();
		ASSERT_EQ(1u, objectStore1.getList<TestObject1>().size());
		ASSERT_EQ(2u, objectStore2.getList<TestObject1>().size());
	}
}
