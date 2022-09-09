#include <vector>
#include <functional>
#include <ranges>

#include <gtest/gtest.h>

#include "comparison_operations.hpp"

class lexicographical_compare_test : public ::testing::Test
{
protected:
    const std::vector<int> v1{1, 2, 3, 4, 5};
    const std::vector<int> v2{1, 2, 3, 4, 8};
    const std::function<int(int)> p1 = [] (int i) { return i + 6; };
    const std::function<int(int)> p2 = [] (int i) { return i + 3; };
};

TEST_F(lexicographical_compare_test, EmptyRange)
{
    EXPECT_FALSE(alg::lexicographical_compare(std::begin(v1), std::begin(v1), std::begin(v2), std::begin(v2)));

    EXPECT_FALSE(alg::lexicographical_compare(std::begin(v1), std::end(v1), std::begin(v2), std::begin(v2)));
    EXPECT_TRUE(alg::lexicographical_compare(std::begin(v1), std::begin(v1), std::begin(v2), std::end(v2)));
}

TEST_F(lexicographical_compare_test, BasicTest)
{
    EXPECT_FALSE(alg::lexicographical_compare(std::begin(v1), std::end(v1) - 1, std::begin(v2), std::end(v2) - 1));
    EXPECT_FALSE(alg::lexicographical_compare(std::begin(v1), std::end(v1) - 1, std::begin(v2), std::end(v2) - 1, std::ranges::greater()));

    EXPECT_TRUE(alg::lexicographical_compare(std::begin(v1), std::end(v1), std::begin(v2), std::end(v2)));
    EXPECT_FALSE(alg::lexicographical_compare(std::begin(v1), std::end(v1), std::begin(v2), std::end(v2), std::ranges::greater()));

    EXPECT_TRUE(alg::lexicographical_compare(std::begin(v1), std::end(v1) - 1, std::begin(v2), std::end(v2)));
    EXPECT_FALSE(alg::lexicographical_compare(std::begin(v1), std::end(v1), std::begin(v2), std::end(v2) - 1));
}

TEST_F(lexicographical_compare_test, RangeTest)
{
    EXPECT_FALSE(alg::lexicographical_compare(std::views::all(v1) | std::views::take(4), std::views::all(v2) | std::views::take(4)));
    EXPECT_FALSE(alg::lexicographical_compare(std::views::all(v1) | std::views::take(4), std::views::all(v2) | std::views::take(4), std::ranges::greater()));

    EXPECT_TRUE(alg::lexicographical_compare(v1, v2));
    EXPECT_FALSE(alg::lexicographical_compare(v1, v2, std::ranges::greater()));

    EXPECT_TRUE(alg::lexicographical_compare(std::views::all(v1) | std::views::take(4), v2));
    EXPECT_FALSE(alg::lexicographical_compare(v1, std::views::all(v2) | std::views::take(4)));
}

TEST_F(lexicographical_compare_test, ProjectionTest)
{
    EXPECT_FALSE(alg::lexicographical_compare(v1, v2, {}, p1, p2));
    EXPECT_TRUE(alg::lexicographical_compare(v1, v2, std::ranges::greater(), p1, p2));
}

TEST_F(lexicographical_compare_test, EmptyRangeN)
{
    EXPECT_FALSE(alg::lexicographical_compare_n(std::begin(v1), std::begin(v2), 0));
}

TEST_F(lexicographical_compare_test, BasicTestN)
{
    EXPECT_FALSE(alg::lexicographical_compare_n(std::begin(v1), std::begin(v2), std::size(v2) - 1));
    EXPECT_FALSE(alg::lexicographical_compare_n(std::begin(v1), std::begin(v2), std::size(v2) - 1, std::ranges::greater()));

    EXPECT_TRUE(alg::lexicographical_compare_n(std::begin(v1), std::begin(v2), std::size(v2)));
    EXPECT_FALSE(alg::lexicographical_compare_n(std::begin(v1), std::begin(v2), std::size(v2), std::ranges::greater()));
}

TEST_F(lexicographical_compare_test, RangeTestN)
{
    EXPECT_FALSE(alg::lexicographical_compare_n(v1, v2, 4));
    EXPECT_FALSE(alg::lexicographical_compare_n(v1, v2, 4, std::ranges::greater()));

    EXPECT_TRUE(alg::lexicographical_compare_n(v1, v2, std::size(v2)));
    EXPECT_FALSE(alg::lexicographical_compare_n(v1, v2, std::size(v2), std::ranges::greater()));
}

TEST_F(lexicographical_compare_test, ProjectionTestN)
{
    EXPECT_FALSE(alg::lexicographical_compare_n(v1, v2, 5, {}, p1, p2));
    EXPECT_TRUE(alg::lexicographical_compare_n(v1, v2, 5, std::ranges::greater(), p1, p2));
}
