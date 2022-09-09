#include <vector>
#include <functional>
#include <ranges>

#include <gtest/gtest.h>

#include "comparison_operations.hpp"

class equal_test : public ::testing::Test
{
protected:
    const std::vector<int> v1{1, 2, 3, 4, 5};
    const std::vector<int> v2{1, 2, 3, 4, 8};
    const std::function<bool(int, int)> pred = [] (int i, int j) { return i % 3 == j % 3; };
    const std::function<int(int)> p1 = [] (int i) { return i + 3; };
    const std::function<int(int)> p2 = [] (int i) { return i + 6; };
};

TEST_F(equal_test, EmptyRange)
{
    EXPECT_TRUE(alg::equal(std::begin(v1), std::begin(v1), std::begin(v2), std::begin(v2)));

    EXPECT_FALSE(alg::equal(std::begin(v1), std::end(v1), std::begin(v2), std::begin(v2)));
    EXPECT_FALSE(alg::equal(std::begin(v1), std::begin(v1), std::begin(v2), std::end(v2)));
}

TEST_F(equal_test, BasicTest)
{
    EXPECT_TRUE(alg::equal(std::begin(v1), std::end(v1) - 1, std::begin(v2), std::end(v2) - 1));
    EXPECT_TRUE(alg::equal(std::begin(v1), std::end(v1) - 1, std::begin(v2), std::end(v2) - 1, pred));

    EXPECT_FALSE(alg::equal(std::begin(v1), std::end(v1), std::begin(v2), std::end(v2)));
    EXPECT_TRUE(alg::equal(std::begin(v1), std::end(v1), std::begin(v2), std::end(v2), pred));

    EXPECT_FALSE(alg::equal(std::begin(v1), std::end(v1) - 1, std::begin(v2), std::end(v2)));
    EXPECT_FALSE(alg::equal(std::begin(v1), std::end(v1), std::begin(v2), std::end(v2) - 1));
}

TEST_F(equal_test, RangeTest)
{
    EXPECT_TRUE(alg::equal(std::views::all(v1) | std::views::take(4), std::views::all(v2) | std::views::take(4)));
    EXPECT_TRUE(alg::equal(std::views::all(v1) | std::views::take(4), std::views::all(v2) | std::views::take(4), pred));

    EXPECT_FALSE(alg::equal(v1, v2));
    EXPECT_TRUE(alg::equal(v1, v2, pred));

    EXPECT_FALSE(alg::equal(std::views::all(v1) | std::views::take(4), v2));
    EXPECT_FALSE(alg::equal(v1, std::views::all(v2) | std::views::take(4), pred));
}

TEST_F(equal_test, ProjectionTest)
{
    EXPECT_FALSE(alg::equal(v1, v2, {}, p1, p2));
    EXPECT_TRUE(alg::equal(v1, v2, pred, p1, p2));
}

TEST_F(equal_test, EmptyRangeN)
{
    EXPECT_TRUE(alg::equal_n(std::begin(v1), std::begin(v2), 0));
}

TEST_F(equal_test, BasicTestN)
{
    EXPECT_TRUE(alg::equal_n(std::begin(v1), std::begin(v2), std::size(v2) - 1));
    EXPECT_TRUE(alg::equal_n(std::begin(v1), std::begin(v2), std::size(v2) - 1, pred));

    EXPECT_FALSE(alg::equal_n(std::begin(v1), std::begin(v2), std::size(v2)));
    EXPECT_TRUE(alg::equal_n(std::begin(v1), std::begin(v2), std::size(v2), pred));
}

TEST_F(equal_test, RangeTestN)
{
    EXPECT_TRUE(alg::equal_n(v1, v2, 4));
    EXPECT_TRUE(alg::equal_n(v1, v2, 4, pred));

    EXPECT_FALSE(alg::equal_n(v1, v2, std::size(v2)));
    EXPECT_TRUE(alg::equal_n(v1, v2, std::size(v2), pred));
}

TEST_F(equal_test, ProjectionTestN)
{
    EXPECT_FALSE(alg::equal_n(v1, v2, 5, {}, p1, p2));
    EXPECT_TRUE(alg::equal_n(v1, v2, 5, pred, p1, p2));
}
