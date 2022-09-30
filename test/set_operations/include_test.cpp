#include <vector>
#include <functional>

#include <gtest/gtest.h>

#include "set_operations.hpp"

class includes_test : public ::testing::Test
{
protected:
    const std::vector<char> v1{'a', 'b', 'c', 'e', 'f', 'h', 'x'}, v2{'a', 'c'};
    const std::function<bool(char, char)> f = std::ranges::greater();
    const std::function<char(char)> p1 = [] (char i) { return i; };
    const std::function<char(char)> p2 = [] (char i) { return i + 2; };
};


TEST_F(includes_test, EmptyRangeTest)
{
    EXPECT_FALSE(alg::includes(std::begin(v1), std::begin(v1), std::begin(v2), std::end(v2)));
    EXPECT_TRUE(alg::includes(std::begin(v1), std::end(v1), std::begin(v2), std::begin(v2)));
}


TEST_F(includes_test, BasicTest)
{
    EXPECT_TRUE(alg::includes(std::begin(v1), std::end(v1), std::begin(v2), std::end(v2)));
    EXPECT_FALSE(alg::includes(std::begin(v1), std::end(v1), std::begin(v2), std::end(v2), f));
}

TEST_F(includes_test, RangeTest)
{
    EXPECT_TRUE(alg::includes(v1, v2));
    EXPECT_FALSE(alg::includes(v1, v2, f));
}

TEST_F(includes_test, ProjectionTest)
{
    EXPECT_TRUE(alg::includes(v1, v2, {}, p1, p2));
    EXPECT_FALSE(alg::includes(v1, v2, f, p1, p2));
}
