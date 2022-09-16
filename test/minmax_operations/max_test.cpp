#include <vector>
#include <functional>
#include <ranges>

#include <gtest/gtest.h>

#include "minmax_operations.hpp"

class max_test : public ::testing::Test
{
protected:
    const int a = 2, b = 6;
    const std::vector<int> v{1, 4, 3, 7, 5};
    const std::initializer_list<int> l{1, 4, 3, 7, 5};
    const std::function<bool(int, int)> pred = [] (int i, int j) { return i > j; };
    const std::function<int(int)> p = [] (int i) { return i % 3; };
};

TEST_F(max_test, BasicTest)
{
    EXPECT_EQ(alg::max(a, b), b);
    EXPECT_EQ(alg::max(a, b, pred), a);

    EXPECT_EQ(alg::max(v), *(std::begin(v) + 3));
    EXPECT_EQ(alg::max(v, pred), *std::begin(v));

    EXPECT_EQ(alg::max(l), *(std::begin(l) + 3));
    EXPECT_EQ(alg::max(l, pred), *std::begin(l));
}

TEST_F(max_test, ProjectionTest)
{
    EXPECT_EQ(alg::max(a, b, {}, p), a);
    EXPECT_EQ(alg::max(a, b, pred, p), b);

    EXPECT_EQ(alg::max(v, {}, p), *(std::begin(v) + 4));
    EXPECT_EQ(alg::max(v, pred, p), *(std::begin(v) + 2));

    EXPECT_EQ(alg::max(l, {}, p), *(std::begin(l) + 4));
    EXPECT_EQ(alg::max(l, pred, p), *(std::begin(l) + 2));
}
