#include <Pineapple/Engine/Util/Obscure.h>
#include <ctime>
#include <limits>
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Obscure, Basic)
{
	pa::Obscure obscure;

	srand((unsigned int)time(NULL));
	rand();

	int value = rand();
	pa::Log::info("Testing with value: {}\n", value);

	obscure = value;

	ASSERT_EQ(static_cast<int>(value), static_cast<int>(obscure));
}

TEST(Obscure, MaxInt)
{
	pa::Obscure obscure;

	srand((unsigned int)time(NULL));
	rand();

	int value = INT_MAX;
	pa::Log::info("Testing with value: {}\n", value);

	obscure = value;

	ASSERT_EQ(static_cast<int>(value), static_cast<int>(obscure));
}

TEST(Obscure, MinInt)
{
	pa::Obscure obscure;

	srand((unsigned int)time(NULL));
	rand();

	int value = INT_MIN;
	pa::Log::info("Testing with value: {}\n", value);

	obscure = value;

	ASSERT_EQ(static_cast<int>(value), static_cast<int>(obscure));
}

TEST(Obscure, Zero)
{
	pa::Obscure obscure;

	srand((unsigned int)time(NULL));
	rand();

	int value = 0;
	pa::Log::info("Testing with value: {}\n", value);

	obscure = value;

	ASSERT_EQ(static_cast<int>(value), static_cast<int>(obscure));
}

TEST(Obscure, MultipleSet)
{
	pa::Obscure obscure;

	int value = 15134561;
	pa::Log::info("Testing with value: {}\n", value);

	obscure = 15134561;
	obscure = -22315235;
	obscure = 67866;
	obscure = -1233;
	obscure = -213;
	obscure = value;

	ASSERT_EQ(static_cast<int>(value), static_cast<int>(obscure));
}

TEST(Obscure, SetSpeed)
{
	pa::Obscure obscure;

	for (int i = 0; i < 100000; i++)
	{
		obscure = rand();
	}
}

TEST(Obscure, GetSpeed)
{
	int value = rand();
	pa::Obscure obscure(value);

	pa::Log::info("Testing with value: {}\n", value);

	for (int i = 0; i < 100000; i++)
	{
		int get = obscure;
	}
}

/*TEST(Obscure, PointerHack)
{
	int value = rand();
	pa::Obscure obscure(value);

	pa::Log::info("Testing with value: {}\n", value);

	obscure.simulatePointerHack();

	int get = obscure;
	CHECK(false);
}

TEST(Obscure, HashHack)
{
	int value = rand();
	pa::Obscure obscure(value);

	pa::Log::info("Testing with value: {}\n", value);

	obscure.simulateHashHack();

	int get = obscure;
	CHECK(false);
}*/