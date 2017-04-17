#include <Pineapple/Engine/Container/List.h>
#include <Pineapple/Engine/Container/ListView.h>
#include <algorithm>
#include <initializer_list>
#include <list>
#include <vector>
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace
{
	struct BaseTest
	{
		int test{0};
		BaseTest(int i)
			: test(i)
		{
		}
	};

	struct DerivedTest : public BaseTest
	{
		DerivedTest(int i)
			: BaseTest(i)
		{
		}
	};

	struct DerivedVirtualBaseTest : public virtual BaseTest
	{
		DerivedVirtualBaseTest(int i)
			: BaseTest(i)
		{
		}
	};
}

TEST(List, PushFront)
{
	pa::List<int> SUT;
	SUT.emplaceFront(5);

	ASSERT_EQ(5, SUT.front());
	ASSERT_EQ(5, SUT.back());
	ASSERT_EQ(1u, SUT.getSize());

	SUT.emplaceFront(10);
	ASSERT_EQ(10, SUT.front());
	ASSERT_EQ(5, SUT.back());
	ASSERT_EQ(2u, SUT.getSize());

	SUT.emplaceFront(15);
	ASSERT_EQ(15, SUT.front());
	ASSERT_EQ(5, SUT.back());
	ASSERT_EQ(3u, SUT.getSize());
}

TEST(List, PushBack)
{
	pa::List<int> SUT;
	SUT.emplaceBack(5);

	ASSERT_EQ(5, SUT.front());
	ASSERT_EQ(5, SUT.back());
	ASSERT_EQ(1u, SUT.getSize());

	SUT.emplaceBack(10);
	ASSERT_EQ(5, SUT.front());
	ASSERT_EQ(10, SUT.back());
	ASSERT_EQ(2u, SUT.getSize());

	SUT.emplaceBack(15);
	ASSERT_EQ(5, SUT.front());
	ASSERT_EQ(15, SUT.back());
	ASSERT_EQ(3u, SUT.getSize());
}

TEST(List, ForEach)
{
	auto data = {1, 5, 23, 99, 102, 4};

	std::vector<int> expected(data);
	pa::List<int> SUT(data);

	unsigned int i = 0;
	for (auto&& element : SUT)
	{
		ASSERT_EQ(expected[i++], element);
	}

	ASSERT_EQ(data.size(), i);
}

TEST(List, Insert)
{
	auto initial = {0, 1, 2, 3};
	auto result = {0, 10, 1, 10, 2, 10, 3};

	pa::List<int> SUT(initial);

	auto itr = SUT.begin();

	++itr;
	SUT.insert(itr, 10);

	++itr;
	SUT.insert(itr, 10);

	++itr;
	SUT.insert(itr, 10);

	std::vector<int> resultVector(result);
	bool areEqual = std::equal(SUT.begin(), SUT.end(), resultVector.begin());
	ASSERT_TRUE(areEqual);
}

TEST(List, EraseBegin)
{
	auto initial = {0, 1, 2, 3};
	auto result = {1, 2, 3};

	pa::List<int> SUT(initial);
	SUT.erase(SUT.begin());

	std::vector<int> resultVector(result);
	bool areEqual = std::equal(SUT.begin(), SUT.end(), resultVector.begin());
	ASSERT_TRUE(areEqual);
}

TEST(List, EraseEnd)
{
	auto initial = {0, 1, 2, 3};
	auto result = {0, 1, 2};

	pa::List<int> SUT(initial);
	auto itr = SUT.begin();
	++itr;
	++itr;
	++itr;
	SUT.erase(itr);

	ASSERT_TRUE(itr == SUT.end());

	std::vector<int> resultVector(result);
	bool areEqual = std::equal(SUT.begin(), SUT.end(), resultVector.begin());
	ASSERT_TRUE(areEqual);
}

TEST(List, EraseMiddle)
{
	auto initial = {0, 1, 2, 3};
	auto result = {0, 1, 3};

	pa::List<int> SUT(initial);
	auto itr = SUT.begin();
	++itr;
	++itr;
	SUT.erase(itr);

	std::vector<int> resultVector(result);
	bool areEqual = std::equal(SUT.begin(), SUT.end(), resultVector.begin());
	ASSERT_TRUE(areEqual);
}

TEST(List, Clear)
{
	pa::List<int> SUT({0, 1, 2, 3});
	SUT.clear();

	ASSERT_EQ(0u, SUT.getSize());
	ASSERT_TRUE(SUT.begin() == SUT.end());
}

TEST(List, PolymorphicIterator)
{
	DerivedTest a{1}, b{2}, c{3};
	pa::List<DerivedTest, BaseTest> list{a, b, c};

	pa::ListView<BaseTest> SUT(list);

	int i = 1;
	for (auto&& item : SUT)
	{
		ASSERT_EQ(i++, item.test);
	}
}

TEST(List, InsertObjectsWithVirtualBase)
{
	pa::List<DerivedVirtualBaseTest, BaseTest> SUT;

	SUT.emplaceBack(1);
}

#ifndef PA_DEBUG

TEST(List, StressPushBackList)
{
	for (int i = 0; i < 1000; i++)
	{
		pa::List<int> SUT;

		for (int j = 0; j < 10000; j++)
		{
			SUT.emplaceBack(j);
		}
	}
}

TEST(List, StressPushBackStdList)
{
	for (int i = 0; i < 1000; i++)
	{
		std::list<int> SUT;

		for (int j = 0; j < 10000; j++)
		{
			SUT.push_back(j);
		}
	}
}

TEST(List, StressPushBackStdVector)
{
	for (int i = 0; i < 1000; i++)
	{
		std::vector<int> SUT;

		for (int j = 0; j < 10000; j++)
		{
			SUT.push_back(j);
		}
	}
}

TEST(List, StressPushFrontList)
{
	for (int i = 0; i < 1000; i++)
	{
		pa::List<int> SUT;

		for (int j = 0; j < 10000; j++)
		{
			SUT.emplaceFront(j);
		}
	}
}

TEST(List, StressPushFrontStdList)
{
	for (int i = 0; i < 1000; i++)
	{
		std::list<int> SUT;

		for (int j = 0; j < 10000; j++)
		{
			SUT.push_front(j);
		}
	}
}

TEST(List, StressInsertList)
{
	for (int i = 0; i < 1000; i++)
	{
		pa::List<int> SUT = {-1, -1, -1, -1, -1};
		auto itr = SUT.begin();
		++itr;
		++itr;

		for (int j = 0; j < 10000; j++)
		{
			SUT.insert(itr, j);
		}
	}
}

TEST(List, StressInsertStdList)
{
	for (int i = 0; i < 1000; i++)
	{
		std::list<int> SUT = {-1, -1, -1, -1, -1};
		auto itr = SUT.begin();
		++itr;
		++itr;

		for (int j = 0; j < 10000; j++)
		{
			SUT.insert(itr, j);
		}
	}
}
#endif