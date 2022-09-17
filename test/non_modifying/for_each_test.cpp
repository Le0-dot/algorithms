#include <string>
#include <vector>
#include <functional>

#include <gtest/gtest.h>

#include "non_modifying_operations.hpp"

class for_each_test : public ::testing::Test
{
protected:
    std::string s{};
    const std::vector<char> v{'a', 'b', 'c'};
    const std::function<void(char)> f = [this] (char c) { s += c; };
};


TEST_F(for_each_test, EmptyRange)
{
    alg::for_each(std::begin(v), std::begin(v), f);

    EXPECT_EQ(s.size(), 0);
}

TEST_F(for_each_test, BasicTest)
{
    alg::for_each(std::begin(v), std::end(v), f);

    EXPECT_EQ(s.size(), 3);
    EXPECT_STREQ(s.data(), "abc");
}

TEST_F(for_each_test, RangeTest)
{
    alg::for_each(v, f);

    EXPECT_EQ(s.size(), 3);
    EXPECT_STREQ(s.data(), "abc");
}

TEST_F(for_each_test, ProjectionTest)
{
    alg::for_each(v, f, [] (char c) { return c + 2; });

    EXPECT_EQ(s.size(), 3);
    EXPECT_STREQ(s.data(), "cde");
}

TEST_F(for_each_test, EmptyRangeN)
{
    alg::for_each_n(std::begin(v), 0, f);

    EXPECT_EQ(s.size(), 0);
}

TEST_F(for_each_test, BasicTestN)
{
    alg::for_each_n(std::begin(v), std::size(v), f);

    EXPECT_EQ(s.size(), 3);
    EXPECT_STREQ(s.data(), "abc");
}

TEST_F(for_each_test, RangeTestN)
{
    alg::for_each_n(v, std::size(v), f);

    EXPECT_EQ(s.size(), 3);
    EXPECT_STREQ(s.data(), "abc");
}

TEST_F(for_each_test, ProjectionTestN)
{
    alg::for_each_n(v, std::size(v), f, [] (char c) { return c + 2; });

    EXPECT_EQ(s.size(), 3);
    EXPECT_STREQ(s.data(), "cde");
}
