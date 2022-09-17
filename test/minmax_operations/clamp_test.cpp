#include <vector>
#include <functional>
#include <ranges>

#include <gtest/gtest.h>

#include "minmax_operations.hpp"

class clamp_test : public ::testing::Test
{
protected:
    const int v = 10, l1 = 5, h1 = 7, l2 = 7, h2 = 12, l3 = 12, h3 = 15;
    const std::function<bool(int, int)> pred = [] (int i, int j) { return i > j; };
    const std::function<int(int)> p = [] (int i) { return i % 4; };
};

TEST_F(clamp_test, BasicTest)
{
    EXPECT_EQ(alg::clamp(v, l1, h1), h1);
    EXPECT_EQ(alg::clamp(v, l2, h2), v);
    EXPECT_EQ(alg::clamp(v, l3, h3), l3);

    EXPECT_EQ(alg::clamp(v, l1, h1, pred), l1);
    EXPECT_EQ(alg::clamp(v, l2, h2, pred), l2);
    EXPECT_EQ(alg::clamp(v, l3, h3, pred), h3);
}

TEST_F(clamp_test, ProjectionTest)
{
    EXPECT_EQ(alg::clamp(v, l1, h1, {}, p), v);
    EXPECT_EQ(alg::clamp(v, l2, h2, {}, p), l2);
    EXPECT_EQ(alg::clamp(v, l3, h3, {}, p), v);

    EXPECT_EQ(alg::clamp(v, l1, h1, pred, p), l1);
    EXPECT_EQ(alg::clamp(v, l2, h2, pred, p), v);
    EXPECT_EQ(alg::clamp(v, l3, h3, pred, p), l3);
}
