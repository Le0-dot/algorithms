#include <vector>
#include <forward_list>
#include <list>
#include <functional>

#include <gtest/gtest.h>

#include "modifying_operations.hpp"

class rotate_test : public ::testing::Test
{
protected:
    std::vector<int> v{1, 2, 3, 4, 5};
    std::forward_list<int> fl{1, 2, 3, 4, 5};
    std::list<int> l{1, 2, 3, 4, 5};
};


TEST_F(rotate_test, EmptyRange)
{
    auto res = alg::rotate(std::begin(v), std::begin(v), std::begin(v));

    EXPECT_EQ(v, (std::vector{1, 2, 3, 4, 5}));
    EXPECT_EQ(std::begin(res), std::begin(v));
    EXPECT_EQ(std::end(res), std::begin(v));
}

TEST_F(rotate_test, BasicTest)
{
    auto res = alg::rotate(std::begin(v), std::begin(v) + 2, std::end(v));

    EXPECT_EQ(v, (std::vector{3, 4, 5, 1, 2}));
    EXPECT_EQ(std::begin(res), std::begin(v) + 3);
    EXPECT_EQ(std::end(res), std::end(v));
}

TEST_F(rotate_test, RangeTest)
{
    auto res = alg::rotate(v, std::begin(v) + 2);

    EXPECT_EQ(v, (std::vector{3, 4, 5, 1, 2}));
    EXPECT_EQ(std::begin(res), std::begin(v) + 3);
    EXPECT_EQ(std::end(res), std::end(v));
}

TEST_F(rotate_test, EmptyRangeBidirectional)
{
    auto res = alg::rotate(std::begin(l), std::begin(l), std::begin(l));

    EXPECT_EQ(l, (std::list{1, 2, 3, 4, 5}));
    EXPECT_EQ(std::begin(res), std::begin(l));
    EXPECT_EQ(std::end(res), std::begin(l));
}

TEST_F(rotate_test, BasicTestBidirectional)
{
    auto res = alg::rotate(std::begin(l), std::ranges::next(std::begin(l), 2), std::end(l));

    EXPECT_EQ(l, (std::list{3, 4, 5, 1, 2}));
    EXPECT_EQ(std::begin(res), std::ranges::next(std::begin(l), 3));
    EXPECT_EQ(std::end(res), std::end(l));
}

TEST_F(rotate_test, RangeTestBidirectional)
{
    auto res = alg::rotate(l, std::ranges::next(std::begin(l), 2));

    EXPECT_EQ(l, (std::list{3, 4, 5, 1, 2}));
    EXPECT_EQ(std::begin(res), std::ranges::next(std::begin(l), 3));
    EXPECT_EQ(std::end(res), std::end(l));
}

TEST_F(rotate_test, EmptyRangeForward)
{
    auto res = alg::rotate(std::begin(fl), std::begin(fl), std::begin(fl));

    EXPECT_EQ(fl, (std::forward_list{1, 2, 3, 4, 5}));
    EXPECT_EQ(std::begin(res), std::begin(fl));
    EXPECT_EQ(std::end(res), std::begin(fl));
}

TEST_F(rotate_test, BasicTestForward)
{
    auto res = alg::rotate(std::begin(fl), std::ranges::next(std::begin(fl), 2), std::end(fl));

    EXPECT_EQ(fl, (std::forward_list{3, 4, 5, 1, 2}));
    EXPECT_EQ(std::begin(res), std::ranges::next(std::begin(fl), 3));
    EXPECT_EQ(std::end(res), std::end(fl));
}

TEST_F(rotate_test, RangeTestForward)
{
    auto res = alg::rotate(fl, std::ranges::next(std::begin(fl), 2));

    EXPECT_EQ(fl, (std::forward_list{3, 4, 5, 1, 2}));
    EXPECT_EQ(std::begin(res), std::ranges::next(std::begin(fl), 3));
    EXPECT_EQ(std::end(res), std::end(fl));
}
