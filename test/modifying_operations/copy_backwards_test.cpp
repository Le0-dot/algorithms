#include <vector>
#include <functional>
#include <ranges>

#include <gtest/gtest.h>

#include "modifying_operations.hpp"

class copy_backwards_test : public ::testing::Test
{
protected:
    const std::vector<int> v1{1, 2, 3};
    std::vector<int> v2{0, 0, 0};
};


TEST_F(copy_backwards_test, EmptyRange)
{
    auto res = alg::copy_backwards(std::begin(v1), std::begin(v1), std::end(v2));

    EXPECT_EQ(v2, (std::vector<int>{0, 0, 0}));
    EXPECT_EQ(res.in, std::begin(v1));
    EXPECT_EQ(res.out, std::end(v2));
}

TEST_F(copy_backwards_test, BasicTest)
{
    auto res = alg::copy_backwards(std::begin(v1), std::end(v1) - 1, std::end(v2));

    EXPECT_EQ(v2, (std::vector<int>{0, 1, 2}));
    EXPECT_EQ(res.in, std::begin(v1) + 2);
    EXPECT_EQ(res.out, std::begin(v2) + 1);

    res = alg::copy_backwards(std::begin(v1), std::end(v1), std::end(v2));

    EXPECT_EQ(v2, (std::vector<int>{1, 2, 3}));
    EXPECT_EQ(res.in, std::begin(v1) + 3);
    EXPECT_EQ(res.out, std::begin(v2));
}

TEST_F(copy_backwards_test, RangeTest)
{
    auto res = alg::copy_backwards(v1 | std::views::take(2), std::end(v2));

    EXPECT_EQ(v2, (std::vector<int>{0, 1, 2}));
    EXPECT_EQ(res.in, std::begin(v1) + 2);
    EXPECT_EQ(res.out, std::begin(v2) + 1);

    res = alg::copy_backwards(v1, std::end(v2));

    EXPECT_EQ(v2, (std::vector<int>{1, 2, 3}));
    EXPECT_EQ(res.in, std::begin(v1) + 3);
    EXPECT_EQ(res.out, std::begin(v2));
}

TEST_F(copy_backwards_test, EmptyRangeN)
{
    auto res = alg::copy_backwards_n(std::begin(v1), 0, std::end(v2));

    EXPECT_EQ(v2, (std::vector<int>{0, 0, 0}));
    EXPECT_EQ(res.in, std::begin(v1));
    EXPECT_EQ(res.out, std::end(v2));
}

TEST_F(copy_backwards_test, BasicTestN)
{
    auto res = alg::copy_backwards_n(std::begin(v1), std::size(v1) - 1, std::end(v2));

    EXPECT_EQ(v2, (std::vector<int>{0, 1, 2}));
    EXPECT_EQ(res.in, std::begin(v1) + 2);
    EXPECT_EQ(res.out, std::begin(v2) + 1);

    res = alg::copy_backwards_n(std::begin(v1), std::size(v1), std::end(v2));

    EXPECT_EQ(v2, (std::vector<int>{1, 2, 3}));
    EXPECT_EQ(res.in, std::begin(v1) + 3);
    EXPECT_EQ(res.out, std::begin(v2));
}

TEST_F(copy_backwards_test, RangeTestN)
{
    auto res = alg::copy_backwards_n(v1, 2, std::end(v2));

    EXPECT_EQ(v2, (std::vector<int>{0, 1, 2}));
    EXPECT_EQ(res.in, std::begin(v1) + 2);
    EXPECT_EQ(res.out, std::begin(v2) + 1);

    res = alg::copy_backwards_n(v1, std::size(v1), std::end(v2));

    EXPECT_EQ(v2, (std::vector<int>{1, 2, 3}));
    EXPECT_EQ(res.in, std::begin(v1) + 3);
    EXPECT_EQ(res.out, std::begin(v2));
}
