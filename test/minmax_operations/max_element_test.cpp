#include <vector>
#include <functional>
#include <ranges>

#include <gtest/gtest.h>

#include "minmax_operations.hpp"

class max_element_test : public ::testing::Test
{
protected:
    const std::vector<int> v{1, 4, 3, 7, 5};
    const std::function<bool(int, int)> pred = [] (int i, int j) { return i > j; };
    const std::function<int(int)> p = [] (int i) { return i % 3; };
};

TEST_F(max_element_test, EmptyRange)
{
    EXPECT_EQ(alg::max_element(std::begin(v), std::begin(v)), std::begin(v));
}

TEST_F(max_element_test, BasicTest)
{
    EXPECT_EQ(alg::max_element(std::begin(v), std::end(v)), std::begin(v) + 3);
    EXPECT_EQ(alg::max_element(std::begin(v), std::end(v), pred), std::begin(v));
}

TEST_F(max_element_test, RangeTest)
{
    EXPECT_EQ(alg::max_element(v), std::begin(v) + 3);
    EXPECT_EQ(alg::max_element(v, pred), std::begin(v));
}

TEST_F(max_element_test, ProjectionTest)
{
    EXPECT_EQ(alg::max_element(v, {}, p), std::begin(v) + 4);
    EXPECT_EQ(alg::max_element(v, pred, p), std::begin(v) + 2);
}
