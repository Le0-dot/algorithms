#include <string>
#include <functional>
#include <ranges>

#include <gtest/gtest.h>

#include "modifying_operations.hpp"

class fill_test : public ::testing::Test
{
protected:
    std::string s{"abc"};
    const char ch = 'X';
};


TEST_F(fill_test, EmptyRange)
{
    auto res = alg::fill(std::begin(s), std::begin(s), ch);

    EXPECT_STREQ(std::data(s), "abc");
    EXPECT_EQ(res, std::begin(s));
}

TEST_F(fill_test, BasicTest)
{
    auto res = alg::fill(std::begin(s), std::end(s) - 1, ch);

    EXPECT_STREQ(std::data(s), "XXc");
    EXPECT_EQ(res, std::begin(s) + 2);

    res = alg::fill(std::begin(s), std::end(s), ch);

    EXPECT_STREQ(std::data(s), "XXX");
    EXPECT_EQ(res, std::begin(s) + 3);
}

TEST_F(fill_test, RangeTest)
{
    auto res = alg::fill(s | std::views::take(2), ch);

    EXPECT_STREQ(std::data(s), "XXc");
    EXPECT_EQ(res, std::begin(s) + 2);

    res = alg::fill(s, ch);

    EXPECT_STREQ(std::data(s), "XXX");
    EXPECT_EQ(res, std::begin(s) + 3);
}

TEST_F(fill_test, EmptyRangeN)
{
    auto res = alg::fill_n(std::begin(s), 0, ch);

    EXPECT_STREQ(std::data(s), "abc");
    EXPECT_EQ(res, std::begin(s));
}

TEST_F(fill_test, BasicTestN)
{
    auto res = alg::fill_n(std::begin(s), std::size(s) - 1, ch);

    EXPECT_STREQ(std::data(s), "XXc");
    EXPECT_EQ(res, std::begin(s) + 2);

    res = alg::fill_n(std::begin(s), std::size(s), ch);

    EXPECT_STREQ(std::data(s), "XXX");
    EXPECT_EQ(res, std::begin(s) + 3);
}

TEST_F(fill_test, RangeTestN)
{
    auto res = alg::fill_n(s, 2, ch);

    EXPECT_STREQ(std::data(s), "XXc");
    EXPECT_EQ(res, std::begin(s) + 2);

    res = alg::fill_n(s, std::size(s), ch);

    EXPECT_STREQ(std::data(s), "XXX");
    EXPECT_EQ(res, std::begin(s) + 3);
}
