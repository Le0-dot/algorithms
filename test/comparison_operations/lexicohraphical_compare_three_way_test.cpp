#include <vector>
#include <functional>
#include <ranges>

#include <gtest/gtest.h>

#include "comparison_operations.hpp"

class lexicographical_compare_three_way_test : public ::testing::Test
{
protected:
    const std::vector<int> v1{1, 2, 3, 4, 5};
    const std::vector<int> v2{1, 2, 3, 4, 8};
    const std::function<int(int)> p1 = [] (int i) { return i + 6; };
    const std::function<int(int)> p2 = [] (int i) { return i + 3; };
};

TEST_F(lexicographical_compare_three_way_test, EmptyRange)
{
    EXPECT_EQ(alg::lexicographical_compare_three_way(std::begin(v1), std::begin(v1), std::begin(v2), std::begin(v2)), std::strong_ordering::equal);

    EXPECT_EQ(alg::lexicographical_compare_three_way(std::begin(v1), std::end(v1), std::begin(v2), std::begin(v2)), std::strong_ordering::greater);
    EXPECT_EQ(alg::lexicographical_compare_three_way(std::begin(v1), std::begin(v1), std::begin(v2), std::end(v2)), std::strong_ordering::less);
}

TEST_F(lexicographical_compare_three_way_test, BasicTest)
{
    EXPECT_EQ(alg::lexicographical_compare_three_way(std::begin(v1), std::end(v1) - 1, std::begin(v2), std::end(v2) - 1), std::strong_ordering::equal);

    EXPECT_EQ(alg::lexicographical_compare_three_way(std::begin(v1), std::end(v1), std::begin(v2), std::end(v2)), std::strong_ordering::less);

    EXPECT_EQ(alg::lexicographical_compare_three_way(std::begin(v1), std::end(v1) - 1, std::begin(v2), std::end(v2)), std::strong_ordering::less);
    EXPECT_EQ(alg::lexicographical_compare_three_way(std::begin(v1), std::end(v1), std::begin(v2), std::end(v2) - 1), std::strong_ordering::greater);
}

TEST_F(lexicographical_compare_three_way_test, RangeTest)
{
    EXPECT_EQ(alg::lexicographical_compare_three_way(std::views::all(v1) | std::views::take(4),
		std::views::all(v2) | std::views::take(4)),
		std::strong_ordering::equal);

    EXPECT_EQ(alg::lexicographical_compare_three_way(v1, v2), std::strong_ordering::less);

    EXPECT_EQ(alg::lexicographical_compare_three_way(std::views::all(v1) | std::views::take(4), v2), std::strong_ordering::less);
    EXPECT_EQ(alg::lexicographical_compare_three_way(v1, std::views::all(v2) | std::views::take(4)), std::strong_ordering::greater);
}

TEST_F(lexicographical_compare_three_way_test, ProjectionTest)
{
    EXPECT_EQ(alg::lexicographical_compare_three_way(v1, v2, {}, p1, p2), std::strong_ordering::greater);
}

TEST_F(lexicographical_compare_three_way_test, EmptyRangeN)
{
    EXPECT_EQ(alg::lexicographical_compare_three_way_n(std::begin(v1), std::begin(v2), 0), std::strong_ordering::equal);
}

TEST_F(lexicographical_compare_three_way_test, BasicTestN)
{
    EXPECT_EQ(alg::lexicographical_compare_three_way_n(std::begin(v1), std::begin(v2), std::size(v2) - 1), std::strong_ordering::equal);

    EXPECT_EQ(alg::lexicographical_compare_three_way_n(std::begin(v1), std::begin(v2), std::size(v2)), std::strong_ordering::less);
}

TEST_F(lexicographical_compare_three_way_test, RangeTestN)
{
    EXPECT_EQ(alg::lexicographical_compare_three_way_n(v1, v2, 4), std::strong_ordering::equal);

    EXPECT_EQ(alg::lexicographical_compare_three_way_n(v1, v2, std::size(v2)), std::strong_ordering::less);
}

TEST_F(lexicographical_compare_three_way_test, ProjectionTestN)
{
    EXPECT_EQ(alg::lexicographical_compare_three_way_n(v1, v2, 5, {}, p1, p2), std::strong_ordering::greater);
}
