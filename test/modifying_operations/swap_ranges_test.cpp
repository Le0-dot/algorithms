#include <vector>
#include <functional>
#include <ranges>

#include <gtest/gtest.h>

#include "modifying_operations.hpp"

class swap_ranges_test : public ::testing::Test
{
protected:
    std::vector<int> v1{1, 2, 3};
    std::vector<int> v2{4, 5, 6};
};


TEST_F(swap_ranges_test, EmptyRange)
{
    alg::swap_ranges(std::begin(v1), std::begin(v1),  std::begin(v2), std::end(v2));

    EXPECT_EQ(v1, (std::vector{1, 2, 3}));
    EXPECT_EQ(v2, (std::vector{4, 5, 6}));

    alg::swap_ranges(std::begin(v1), std::end(v1),  std::begin(v2), std::begin(v2));

    EXPECT_EQ(v1, (std::vector{1, 2, 3}));
    EXPECT_EQ(v2, (std::vector{4, 5, 6}));
}

TEST_F(swap_ranges_test, BasicTest)
{
    alg::swap_ranges(std::begin(v1), std::end(v1),  std::begin(v2), std::end(v2));

    EXPECT_EQ(v1, (std::vector{4, 5, 6}));
    EXPECT_EQ(v2, (std::vector{1, 2, 3}));

    alg::swap_ranges(std::begin(v1), std::end(v1) - 1, std::begin(v2), std::end(v2));

    EXPECT_EQ(v1, (std::vector{1, 2, 6}));
    EXPECT_EQ(v2, (std::vector{4, 5, 3}));
}

TEST_F(swap_ranges_test, RangeTest)
{
    alg::swap_ranges(v1,  v2);

    EXPECT_EQ(v1, (std::vector{4, 5, 6}));
    EXPECT_EQ(v2, (std::vector{1, 2, 3}));

    alg::swap_ranges(v1 | std::views::take(2), v2);

    EXPECT_EQ(v1, (std::vector{1, 2, 6}));
    EXPECT_EQ(v2, (std::vector{4, 5, 3}));
}
