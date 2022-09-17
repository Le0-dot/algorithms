#include <string>
#include <vector>
#include <functional>

#include <gtest/gtest.h>

#include "modifying_operations.hpp"

class copy_if_test : public ::testing::Test
{
protected:
    std::string s{};
    const std::vector<char> v{'a', 'b', 'c'};
    const std::function<char(char)> p = [] (char c) { return c + 1; };
    const std::function<bool(char)> f = [] (char c) { return !((c - 'a') & 1); };
};


TEST_F(copy_if_test, EmptyRange)
{
    auto res = alg::copy_if(std::begin(v), std::begin(v), std::back_inserter(s), f);

    EXPECT_EQ(std::size(s), 0);
    EXPECT_EQ(res.in, std::begin(v));
}

TEST_F(copy_if_test, BasicTest)
{
    auto res = alg::copy_if(std::begin(v), std::end(v), std::back_inserter(s), f);

    EXPECT_EQ(std::size(s), 2);
    EXPECT_STREQ(std::data(s), "ac");
    EXPECT_EQ(res.in, std::begin(v) + 3);
}

TEST_F(copy_if_test, RangeTest)
{
    auto res = alg::copy_if(v, std::back_inserter(s), f);

    EXPECT_EQ(std::size(s), 2);
    EXPECT_STREQ(std::data(s), "ac");
    EXPECT_EQ(res.in, std::begin(v) + 3);
}

TEST_F(copy_if_test, ProjectionTest)
{
    auto res = alg::copy_if(v, std::back_inserter(s), f, p);

    EXPECT_EQ(std::size(s), 1);
    EXPECT_STREQ(std::data(s), "b");
    EXPECT_EQ(res.in, std::begin(v) + 3);
}

TEST_F(copy_if_test, EmptyRangeN)
{
    auto res = alg::copy_if_n(std::begin(v), 0, std::back_inserter(s), f);

    EXPECT_EQ(std::size(s), 0);
    EXPECT_EQ(res.in, std::begin(v));
}

TEST_F(copy_if_test, BasicTestN)
{
    auto res = alg::copy_if_n(std::begin(v), 2, std::back_inserter(s), f);

    EXPECT_EQ(std::size(s), 2);
    EXPECT_STREQ(std::data(s), "ac");
    EXPECT_EQ(res.in, std::begin(v) + 3);
}

TEST_F(copy_if_test, RangeTestN)
{
    auto res = alg::copy_if_n(v, 2, std::back_inserter(s), f);

    EXPECT_EQ(std::size(s), 2);
    EXPECT_STREQ(std::data(s), "ac");
    EXPECT_EQ(res.in, std::begin(v) + 3);
}

TEST_F(copy_if_test, ProjectionTestN)
{
    auto res = alg::copy_if_n(v, 1, std::back_inserter(s), f, p);

    EXPECT_EQ(std::size(s), 1);
    EXPECT_STREQ(std::data(s), "b");
    EXPECT_EQ(res.in, std::begin(v) + 2);
}
