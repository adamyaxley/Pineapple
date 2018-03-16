#include <Pineapple/Engine/Container/IndexBuffer.h>
#include <algorithm>
#include <vector>
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(IndexBuffer, AcquireFromSingle)
{
	pa::IndexBuffer SUT(1);

	auto a = SUT.acquire();
	ASSERT_EQ(0, a);
}

TEST(IndexBuffer, AcquireFromMultiple)
{
	std::vector<std::size_t> result;
	result.reserve(3);

	pa::IndexBuffer SUT(3);

	result.push_back(SUT.acquire());
	result.push_back(SUT.acquire());
	result.push_back(SUT.acquire());

	std::sort(result.begin(), result.end());

	auto expected = {0, 1, 2};
	ASSERT_TRUE(std::equal(result.begin(), result.end(), expected.begin(), expected.end()));
}

TEST(IndexBuffer, ReleaseSingle)
{
	pa::IndexBuffer SUT(1);

	auto a = SUT.acquire();
	SUT.release(a);
	auto b = SUT.acquire();
	ASSERT_EQ(a, b);
}

TEST(IndexBuffer, ReleaseMultiple)
{
	pa::IndexBuffer SUT(2);

	// Acquire 2
	auto a = SUT.acquire();
	auto b = SUT.acquire();

	// Release them back
	SUT.release(b);
	SUT.release(a);

	// Reacquire them
	auto c = SUT.acquire();
	auto d = SUT.acquire();

	ASSERT_TRUE((c == b && d == a) || (c == a && d == b));
}

TEST(IndexBuffer, AcquireReleaseSome)
{
	pa::IndexBuffer SUT(5);

	for (int i = 0; i < 100; i++)
	{
		auto a = SUT.acquire();
		auto b = SUT.acquire();
		auto c = SUT.acquire();

		ASSERT_TRUE(a < 5 && a >= 0);
		ASSERT_TRUE(b < 5 && b >= 0);
		ASSERT_TRUE(c < 5 && c >= 0);

		SUT.release(c);
		SUT.release(b);
		SUT.release(a);
	}

	ASSERT_EQ(5, SUT.getSize());
}

TEST(IndexBuffer, Size)
{
	std::size_t capacities[] = {5, 10, 32};

	for (auto&& c : capacities)
	{
		pa::IndexBuffer SUT(c);

		ASSERT_EQ(c, SUT.getSize());

		for (std::size_t i = c; i > 0; i--)
		{
			SUT.acquire();
			ASSERT_EQ(i - 1, SUT.getSize());
		}

		for (std::size_t i = 0; i < c; i++)
		{
			SUT.release(i);
			ASSERT_EQ(i + 1, SUT.getSize());
		}
	}
}

TEST(IndexBuffer, Capacity)
{
	std::size_t capacities[] = {5, 10, 32, 120};

	for (auto&& c : capacities)
	{
		pa::IndexBuffer SUT(c);
		ASSERT_EQ(c, SUT.getCapacity());
	}
}

#ifndef PA_DEBUG
TEST(IndexBuffer, Stress) // 584
{
	pa::IndexBuffer SUT(500);

	for (std::size_t n = 0; n < 500000; n++)
	{
		for (std::size_t i = 0; i < 500; i++)
		{
			SUT.acquire();
		}

		for (std::size_t i = 0; i < 500; i++)
		{
			SUT.release(i);
		}
	}
}
#endif