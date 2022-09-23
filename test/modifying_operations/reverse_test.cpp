#include <vector>
#include <functional>

#include <gtest/gtest.h>

#include "modifying_operations.hpp"

class reverse_test : public ::testing::Test
{
protected:
    std::vector<int> v{1, 2, 3};
};


TEST_F(reverse_test, EmptyRange)
{
    auto res = alg::reverse(std::begin(v), std::begin(v));

    EXPECT_EQ(v, (std::vector{1, 2, 3}));
    EXPECT_EQ(res, std::begin(v));
}

TEST_F(reverse_test, BasicTest)
{
    auto res = alg::reverse(std::begin(v), std::end(v));

    EXPECT_EQ(v, (std::vector{3, 2, 1}));
    EXPECT_EQ(res, std::end(v));
}

TEST_F(reverse_test, RangeTest)
{
    auto res = alg::reverse(v);

    EXPECT_EQ(v, (std::vector{3, 2, 1}));
    EXPECT_EQ(res, std::end(v));
}

TEST_F(reverse_test, EmptyRangeN)
{
    auto res = alg::reverse_n(std::begin(v), 0);

    EXPECT_EQ(v, (std::vector{1, 2, 3}));
    EXPECT_EQ(res, std::begin(v));
}

TEST_F(reverse_test, BasicTestN)
{
    auto res = alg::reverse_n(std::begin(v), std::size(v));

    EXPECT_EQ(v, (std::vector{3, 2, 1}));
    EXPECT_EQ(res, std::end(v));
}

TEST_F(reverse_test, RangeTestN)
{
    auto res = alg::reverse_n(v, std::size(v));

    EXPECT_EQ(v, (std::vector{3, 2, 1}));
    EXPECT_EQ(res, std::end(v));
}
