#include <vector>
#include <functional>

#include <gtest/gtest.h>

#include "modifying_operations.hpp"

class replace_test : public ::testing::Test
{
protected:
    std::vector<int> v{1, 2, 3, 2};
    const int i = 2, j = 4; 
    const std::function<int(int)> p = [] (int i) { return i - 1; };
};


TEST_F(replace_test, EmptyRange)
{
    auto res = alg::replace(std::begin(v), std::begin(v), i, j);

    EXPECT_EQ(v, (std::vector<int>{1, 2, 3, 2}));
    EXPECT_EQ(res, std::begin(v));
}

TEST_F(replace_test, BasicTest)
{
    auto res = alg::replace(std::begin(v), std::end(v), i, j);

    EXPECT_EQ(v, (std::vector<int>{1, 4, 3, 4}));
    EXPECT_EQ(res, std::end(v));
}

TEST_F(replace_test, RangeTest)
{
    auto res = alg::replace(v, i, j);

    EXPECT_EQ(v, (std::vector<int>{1, 4, 3, 4}));
    EXPECT_EQ(res, std::end(v));
}

TEST_F(replace_test, ProjectionTest)
{
    auto res = alg::replace(v, i, j, p);

    EXPECT_EQ(v, (std::vector<int>{1, 2, 4, 2}));
    EXPECT_EQ(res, std::end(v));
}

TEST_F(replace_test, EmptyRangeN)
{
    auto res = alg::replace_n(std::begin(v), 0, i, j);

    EXPECT_EQ(v, (std::vector<int>{1, 2, 3, 2}));
    EXPECT_EQ(res, std::begin(v));
}

TEST_F(replace_test, BasicTestN)
{
    auto res = alg::replace_n(std::begin(v), std::size(v), i, j);

    EXPECT_EQ(v, (std::vector<int>{1, 4, 3, 4}));
    EXPECT_EQ(res, std::end(v));
}

TEST_F(replace_test, RangeTestN)
{
    auto res = alg::replace_n(v, std::size(v), i, j);

    EXPECT_EQ(v, (std::vector<int>{1, 4, 3, 4}));
    EXPECT_EQ(res, std::end(v));
}

TEST_F(replace_test, ProjectionTestN)
{
    auto res = alg::replace_n(v, std::size(v), i, j, p);

    EXPECT_EQ(v, (std::vector<int>{1, 2, 4, 2}));
    EXPECT_EQ(res, std::end(v));
}
