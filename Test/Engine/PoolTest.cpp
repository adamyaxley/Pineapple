#include <Pineapple/Engine/Container/DynamicPool.h>
#include <Pineapple/Engine/Container/Pool.h>
#include <functional>
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace
{
	struct POD
	{
		int a, b, c;
		float d, e, f;
		long long g;
		bool h;
	};

	struct ConstructorTestObject
	{
		template <typename T>
		ConstructorTestObject(T&& callback)
		{
			std::forward<T>(callback)();
		}
	};

	struct BaseTest
	{
		virtual ~BaseTest()
		{
		}
	};

	struct DerivedTest : public BaseTest
	{
		template <typename T>
		DerivedTest(T&& callback)
			: m_callback(std::forward<T>(callback))
		{
		}

		~DerivedTest()
		{
			m_callback();
		}

		std::function<void()> m_callback;
	};
}

struct DestructorTestObject
{
	template <typename T>
	DestructorTestObject(T&& callback)
		: m_callback(std::forward<T>(callback))
	{
	}

	~DestructorTestObject()
	{
		m_callback();
	}

	std::function<void()> m_callback;
};

TEST(Pool, IntNew)
{
	constexpr int size = 100000;

	int* ints[size];

	for (int i = 0; i < size; i++)
	{
		ints[i] = new int();
	}

	for (int i = 0; i < size; i++)
	{
		delete ints[i];
	}
}

TEST(Pool, IntPool)
{
	constexpr int size = 100000;

	pa::Pool pool(sizeof(int), size);
	pa::Pool::Ptr<int> ints[size];

	for (int i = 0; i < size; i++)
	{
		ints[i] = pool.acquire<int>();
	}
}

TEST(Pool, PODNew)
{
	constexpr int size = 100000;

	POD* pods[size];

	for (int i = 0; i < size; i++)
	{
		pods[i] = new POD();
	}

	for (int i = 0; i < size; i++)
	{
		delete pods[i];
	}
}

TEST(Pool, PODPool)
{
	constexpr int size = 100000;

	pa::Pool pool(sizeof(POD), size);
	pa::Pool::Ptr<POD> pods[size];

	for (int i = 0; i < size; i++)
	{
		pods[i] = pool.acquire<POD>();
	}

	/*volatile int i = 0;
	volatile POD access = *pods[i];*/
}

TEST(Pool, ConstructorIsCalled)
{
	bool called = false;

	pa::Pool SUT(sizeof(ConstructorTestObject), 1);
	SUT.acquire<ConstructorTestObject>([&called]() { called = true; });

	ASSERT_EQ(true, called);
}

TEST(Pool, IntDynamicPool)
{
	constexpr int size = 100000;

	pa::DynamicPool pool(sizeof(int), 128);
	pa::Pool::Ptr<int> ints[size];

	for (int i = 0; i < size; i++)
	{
		ints[i] = pool.acquire<int>();
	}
}

TEST(Pool, DestructorIsCalled)
{
	bool called = false;

	{
		pa::Pool SUT(sizeof(DestructorTestObject), 1);
		auto object = SUT.acquire<DestructorTestObject>([&called]() { called = true; });

		ASSERT_EQ(false, called);
	}

	ASSERT_EQ(true, called);
}

TEST(Pool, Size)
{
	pa::Pool pool(sizeof(int), 10);

	ASSERT_EQ(10, pool.getSize());

	auto ptr = pool.acquire<int>();

	ASSERT_EQ(9, pool.getSize());
}

TEST(Pool, PtrSizeIsSmall)
{
	auto uniquePtrSize = sizeof(std::unique_ptr<int>);
	auto poolPtrSize = sizeof(pa::Pool::Ptr<int>);

	ASSERT_TRUE(poolPtrSize <= 2 * uniquePtrSize);
}

TEST(Pool, PtrIsCastable)
{
	pa::Pool pool(sizeof(DerivedTest), 1);
	auto SUT = pool.acquire<DerivedTest>([] {});

	pa::Pool::Ptr<BaseTest> basePtr = std::move(SUT);
}

TEST(Pool, PtrIsPolymorphic)
{
	bool called = false;

	pa::Pool pool(sizeof(DerivedTest), 1);
	auto SUT = pool.acquire<DerivedTest>([&called]() { called = true; });

	{
		pa::Pool::Ptr<BaseTest> basePtr = std::move(SUT);
		ASSERT_FALSE(called);
	}

	ASSERT_TRUE(called);
}