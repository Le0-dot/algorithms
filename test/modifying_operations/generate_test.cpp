#include <string>
#include <functional>
#include <ranges>

#include <gtest/gtest.h>

#include "modifying_operations.hpp"

class generate_test : public ::testing::Test
{
protected:
    std::string s{"abc"};
    std::function<char()> gen = [] () { return 'X'; };
};


TEST_F(generate_test, EmptyRange)
{
    auto res = alg::generate(std::begin(s), std::begin(s), gen);

    EXPECT_STREQ(std::data(s), "abc");
    EXPECT_EQ(res, std::begin(s));
}

TEST_F(generate_test, BasicTest)
{
    auto res = alg::generate(std::begin(s), std::end(s) - 1, gen);

    EXPECT_STREQ(std::data(s), "XXc");
    EXPECT_EQ(res, std::begin(s) + 2);

    res = alg::generate(std::begin(s), std::end(s), gen);

    EXPECT_STREQ(std::data(s), "XXX");
    EXPECT_EQ(res, std::begin(s) + 3);
}

TEST_F(generate_test, RangeTest)
{
    auto res = alg::generate(s | std::views::take(2), gen);

    EXPECT_STREQ(std::data(s), "XXc");
    EXPECT_EQ(res, std::begin(s) + 2);

    res = alg::generate(s, gen);

    EXPECT_STREQ(std::data(s), "XXX");
    EXPECT_EQ(res, std::begin(s) + 3);
}

TEST_F(generate_test, EmptyRangeN)
{
    auto res = alg::generate_n(std::begin(s), 0, gen);

    EXPECT_STREQ(std::data(s), "abc");
    EXPECT_EQ(res, std::begin(s));
}

TEST_F(generate_test, BasicTestN)
{
    auto res = alg::generate_n(std::begin(s), std::size(s) - 1, gen);

    EXPECT_STREQ(std::data(s), "XXc");
    EXPECT_EQ(res, std::begin(s) + 2);

    res = alg::generate_n(std::begin(s), std::size(s), gen);

    EXPECT_STREQ(std::data(s), "XXX");
    EXPECT_EQ(res, std::begin(s) + 3);
}

TEST_F(generate_test, RangeTestN)
{
    auto res = alg::generate_n(s, 2, gen);

    EXPECT_STREQ(std::data(s), "XXc");
    EXPECT_EQ(res, std::begin(s) + 2);

    res = alg::generate_n(s, std::size(s), gen);

    EXPECT_STREQ(std::data(s), "XXX");
    EXPECT_EQ(res, std::begin(s) + 3);
}
