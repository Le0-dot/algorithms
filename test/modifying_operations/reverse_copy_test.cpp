#include <vector>
#include <functional>

#include <gtest/gtest.h>

#include "modifying_operations.hpp"

class reverse_copy_test : public ::testing::Test
{
protected:
    const std::vector<int> v1{1, 2, 3};
    std::vector<int> v2{0, 0, 0};
};


TEST_F(reverse_copy_test, EmptyRange)
{
    auto res = alg::reverse_copy(std::begin(v1), std::begin(v1), std::begin(v2));

    EXPECT_EQ(v2, (std::vector{0, 0, 0}));
    EXPECT_EQ(res.in, std::begin(v1));
    EXPECT_EQ(res.out, std::begin(v2));
}

TEST_F(reverse_copy_test, BasicTest)
{
    auto res = alg::reverse_copy(std::begin(v1), std::end(v1), std::begin(v2));

    EXPECT_EQ(v2, (std::vector{3, 2, 1}));
    EXPECT_EQ(res.in, std::end(v1));
    EXPECT_EQ(res.out, std::end(v2));
}

TEST_F(reverse_copy_test, RangeTest)
{
    auto res = alg::reverse_copy(v1, std::begin(v2));

    EXPECT_EQ(v2, (std::vector{3, 2, 1}));
    EXPECT_EQ(res.in, std::end(v1));
    EXPECT_EQ(res.out, std::end(v2));
}

TEST_F(reverse_copy_test, EmptyRangeN)
{
    auto res = alg::reverse_copy_n(std::begin(v1), 0, std::begin(v2));

    EXPECT_EQ(v2, (std::vector{0, 0, 0}));
    EXPECT_EQ(res.in, std::begin(v1));
    EXPECT_EQ(res.out, std::begin(v2));
}

TEST_F(reverse_copy_test, BasicTestN)
{
    auto res = alg::reverse_copy_n(std::begin(v1), std::size(v1), std::begin(v2));

    EXPECT_EQ(v2, (std::vector{3, 2, 1}));
    EXPECT_EQ(res.in, std::end(v1));
    EXPECT_EQ(res.out, std::end(v2));
}

TEST_F(reverse_copy_test, RangeTestN)
{
    auto res = alg::reverse_copy_n(v1, std::size(v1), std::begin(v2));

    EXPECT_EQ(v2, (std::vector{3, 2, 1}));
    EXPECT_EQ(res.in, std::end(v1));
    EXPECT_EQ(res.out, std::end(v2));
}
