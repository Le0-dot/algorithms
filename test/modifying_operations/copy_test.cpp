#include <string>
#include <vector>
#include <functional>

#include <gtest/gtest.h>

#include "modifying_operations.hpp"

class copy_test : public ::testing::Test
{
protected:
    std::string s{};
    const std::vector<char> v{'a', 'b', 'c'};
};


TEST_F(copy_test, EmptyRange)
{
    auto res = alg::copy(std::begin(v), std::begin(v), std::back_inserter(s));

    EXPECT_EQ(std::size(s), 0);
    EXPECT_EQ(res.in, std::begin(v));
}

TEST_F(copy_test, BasicTest)
{
    auto res = alg::copy(std::begin(v), std::end(v), std::back_inserter(s));

    EXPECT_EQ(std::size(s), 3);
    EXPECT_STREQ(std::data(s), "abc");
    EXPECT_EQ(res.in, std::begin(v) + 3);
}

TEST_F(copy_test, RangeTest)
{
    auto res = alg::copy(v, std::back_inserter(s));

    EXPECT_EQ(std::size(s), 3);
    EXPECT_STREQ(std::data(s), "abc");
    EXPECT_EQ(res.in, std::begin(v) + 3);
}

TEST_F(copy_test, EmptyRangeN)
{
    auto res = alg::copy_n(std::begin(v), 0, std::back_inserter(s));

    EXPECT_EQ(std::size(s), 0);
    EXPECT_EQ(res.in, std::begin(v));
}

TEST_F(copy_test, BasicTestN)
{
    auto res = alg::copy_n(std::begin(v), std::size(v), std::back_inserter(s));

    EXPECT_EQ(std::size(s), 3);
    EXPECT_STREQ(std::data(s), "abc");
    EXPECT_EQ(res.in, std::begin(v) + 3);
}

TEST_F(copy_test, RangeTestN)
{
    auto res = alg::copy_n(v, std::size(v), std::back_inserter(s));

    EXPECT_EQ(std::size(s), 3);
    EXPECT_STREQ(std::data(s), "abc");
    EXPECT_EQ(res.in, std::begin(v) + 3);
}
