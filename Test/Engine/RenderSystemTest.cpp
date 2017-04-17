#include <Pineapple/Engine/Graphics/Render.h>
#include <Pineapple/Engine/Graphics/RenderSystem.h>
#include <vector>
#include "gmock/gmock.h"
#include "gtest/gtest.h"

struct OrderedTest : public pa::Render
{
	OrderedTest(std::vector<int>& rendered, pa::RenderSystem& renderSystem, int priority)
		: pa::Render(renderSystem, pa::Render::Type::Ordered, priority)
		, m_rendered(rendered)
	{
	}

	virtual void render() override
	{
		m_rendered.push_back(getPriority());
	}

	std::vector<int>& m_rendered;
};

TEST(RenderSystem, Ordered)
{
	pa::RenderSystem SUT;

	std::vector<int> rendered;
	OrderedTest a(rendered, SUT, 1);
	OrderedTest b(rendered, SUT, 2);
	OrderedTest c(rendered, SUT, 0);

	SUT.renderOrdered();

	std::vector<int> expected({0, 1, 2});
	bool areEqual = std::equal(rendered.begin(), rendered.end(), expected.begin());
	ASSERT_TRUE(areEqual);
}

TEST(RenderSystem, OrderedChangePriority)
{
	pa::RenderSystem SUT;

	std::vector<int> rendered;
	OrderedTest a(rendered, SUT, 1);
	OrderedTest b(rendered, SUT, 2);
	OrderedTest c(rendered, SUT, 0);

	a.setPriority(3);

	SUT.renderOrdered();

	std::vector<int> expected({0, 2, 3});
	bool areEqual = std::equal(rendered.begin(), rendered.end(), expected.begin());
	ASSERT_TRUE(areEqual);
}