#include <vector>
#include <functional>

#include <gtest/gtest.h>

#include "modifying_operations.hpp"

class unique_copy_test : public ::testing::Test
{
protected:
    const std::vector<int> v1{1, 3, 3, 1, 1};
    std::vector<int> v2{0, 0, 0};
    const std::function<bool(int, int)> f = [] (int a, int b) { return a % 2 == b % 2; };
    const std::function<int(int)> p = [] (int i) { return 1; };
};


TEST_F(unique_copy_test, EmptyRange)
{
    auto res = alg::unique_copy(std::begin(v1), std::begin(v1), std::begin(v2));

    EXPECT_EQ(v2, (std::vector{0, 0, 0}));
    EXPECT_EQ(res.in, std::begin(v1));
    EXPECT_EQ(res.out, std::begin(v2));
}

TEST_F(unique_copy_test, BasicTest)
{
    auto res = alg::unique_copy(std::begin(v1), std::end(v1), std::begin(v2));

    EXPECT_EQ(v2, (std::vector{1, 3, 1}));
    EXPECT_EQ(res.in, std::end(v1));
    EXPECT_EQ(res.out, std::end(v2));
}

TEST_F(unique_copy_test, RangeTest)
{
    auto res = alg::unique_copy(v1, std::begin(v2));

    EXPECT_EQ(v2, (std::vector{1, 3, 1}));
    EXPECT_EQ(res.in, std::end(v1));
    EXPECT_EQ(res.out, std::end(v2));
}

TEST_F(unique_copy_test, ComparatorTest)
{
    auto res = alg::unique_copy(v1, std::begin(v2), f);

    EXPECT_EQ(v2, (std::vector{1, 0, 0}));
    EXPECT_EQ(res.in, std::end(v1));
    EXPECT_EQ(res.out, std::begin(v2) + 1);
}

TEST_F(unique_copy_test, ProjectionTest)
{
    auto res = alg::unique_copy(v1, std::begin(v2), {}, p);

    EXPECT_EQ(v2, (std::vector{1, 0, 0}));
    EXPECT_EQ(res.in, std::end(v1));
    EXPECT_EQ(res.out, std::begin(v2) + 1);
}
