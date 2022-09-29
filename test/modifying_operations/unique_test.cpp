#include <vector>
#include <functional>

#include <gtest/gtest.h>

#include "modifying_operations.hpp"

class unique_test : public ::testing::Test
{
protected:
    std::vector<int> v{1, 3, 3, 1, 1};
    const std::function<bool(int, int)> f = [] (int a, int b) { return a % 2 == b % 2; };
    const std::function<int(int)> p = [] (int i) { return 1; };
};


TEST_F(unique_test, EmptyRange)
{
    auto res = alg::unique(std::begin(v), std::begin(v));

    EXPECT_EQ(std::begin(res), std::begin(v));
    EXPECT_EQ(std::end(res), std::begin(v));

    v.erase(std::begin(res), std::end(res));

    EXPECT_EQ(v, (std::vector{1, 3, 3, 1, 1}));
}

TEST_F(unique_test, BasicTest)
{
    auto res = alg::unique(std::begin(v), std::end(v));

    EXPECT_EQ(std::begin(res), std::begin(v) + 3);
    EXPECT_EQ(std::end(res), std::end(v));

    v.erase(std::begin(res), std::end(res));

    EXPECT_EQ(v, (std::vector{1, 3, 1}));
}

TEST_F(unique_test, RangeTest)
{
    auto res = alg::unique(v);

    EXPECT_EQ(std::begin(res), std::begin(v) + 3);
    EXPECT_EQ(std::end(res), std::end(v));

    v.erase(std::begin(res), std::end(res));

    EXPECT_EQ(v, (std::vector{1, 3, 1}));
}

TEST_F(unique_test, ComparatorTest)
{
    auto res = alg::unique(v, f);

    EXPECT_EQ(std::begin(res), std::begin(v) + 1);
    EXPECT_EQ(std::end(res), std::end(v));

    v.erase(std::begin(res), std::end(res));

    EXPECT_EQ(v, (std::vector{1}));
}

TEST_F(unique_test, ProjectionTest)
{
    auto res = alg::unique(v, {}, p);

    EXPECT_EQ(std::begin(res), std::begin(v) + 1);
    EXPECT_EQ(std::end(res), std::end(v));

    v.erase(std::begin(res), std::end(res));

    EXPECT_EQ(v, (std::vector{1}));
}
