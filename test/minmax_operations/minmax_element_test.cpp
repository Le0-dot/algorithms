#include <vector>
#include <functional>
#include <ranges>

#include <gtest/gtest.h>

#include "minmax_operations.hpp"

class minmax_element_test : public ::testing::Test
{
protected:
    const std::vector<int> v{1, 4, 0, 7, 5};
    const std::function<bool(int, int)> pred = [] (int i, int j) { return i > j; };
    const std::function<int(int)> p = [] (int i) { return i % 3; };
};

TEST_F(minmax_element_test, EmptyRange)
{
    auto res = alg::minmax_element(std::begin(v), std::begin(v));

    EXPECT_EQ(res.min, std::begin(v));
    EXPECT_EQ(res.max, std::begin(v));

    res = alg::minmax_element(std::begin(v), std::begin(v) + 1);

    EXPECT_EQ(res.min, std::begin(v));
    EXPECT_EQ(res.max, std::begin(v));
}

TEST_F(minmax_element_test, BasicTest)
{
    auto res = alg::minmax_element(std::begin(v), std::end(v));

    EXPECT_EQ(res.min, std::begin(v) + 2);
    EXPECT_EQ(res.max, std::begin(v) + 3);

    res = alg::minmax_element(std::begin(v), std::end(v), pred);

    EXPECT_EQ(res.min, std::begin(v) + 3);
    EXPECT_EQ(res.max, std::begin(v) + 2);
}

TEST_F(minmax_element_test, RangeTest)
{
    auto res = alg::minmax_element(v);

    EXPECT_EQ(res.min, std::begin(v) + 2);
    EXPECT_EQ(res.max, std::begin(v) + 3);

    res = alg::minmax_element(v, pred);

    EXPECT_EQ(res.min, std::begin(v) + 3);
    EXPECT_EQ(res.max, std::begin(v) + 2);
}

TEST_F(minmax_element_test, ProjectionTest)
{
    auto res = alg::minmax_element(v, {}, p);

    EXPECT_EQ(res.min, std::begin(v) + 2);
    EXPECT_EQ(res.max, std::begin(v) + 4);

    res = alg::minmax_element(v, pred, p);

    EXPECT_EQ(res.min, std::begin(v) + 4);
    EXPECT_EQ(res.max, std::begin(v) + 2);
}
