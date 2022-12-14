#include <vector>
#include <functional>

#include <gtest/gtest.h>

#include "modifying_operations.hpp"

class replace_if_test : public ::testing::Test
{
protected:
    std::vector<int> v{1, 2, 3, 2};
    const int j = 4; 
    const std::function<bool(int)> i = [] (int i) { return i == 2; };
    const std::function<int(int)> p = [] (int i) { return i - 1; };
};


TEST_F(replace_if_test, EmptyRange)
{
    auto res = alg::replace_if(std::begin(v), std::begin(v), i, j);

    EXPECT_EQ(v, (std::vector{1, 2, 3, 2}));
    EXPECT_EQ(res, std::begin(v));
}

TEST_F(replace_if_test, BasicTest)
{
    auto res = alg::replace_if(std::begin(v), std::end(v), i, j);

    EXPECT_EQ(v, (std::vector{1, 4, 3, 4}));
    EXPECT_EQ(res, std::end(v));
}

TEST_F(replace_if_test, RangeTest)
{
    auto res = alg::replace_if(v, i, j);

    EXPECT_EQ(v, (std::vector{1, 4, 3, 4}));
    EXPECT_EQ(res, std::end(v));
}

TEST_F(replace_if_test, ProjectionTest)
{
    auto res = alg::replace_if(v, i, j, p);

    EXPECT_EQ(v, (std::vector{1, 2, 4, 2}));
    EXPECT_EQ(res, std::end(v));
}

TEST_F(replace_if_test, EmptyRangeN)
{
    auto res = alg::replace_if_n(std::begin(v), 0, i, j);

    EXPECT_EQ(v, (std::vector{1, 2, 3, 2}));
    EXPECT_EQ(res, std::begin(v));
}

TEST_F(replace_if_test, BasicTestN)
{
    auto res = alg::replace_if_n(std::begin(v), std::size(v), i, j);

    EXPECT_EQ(v, (std::vector{1, 4, 3, 4}));
    EXPECT_EQ(res, std::end(v));
}

TEST_F(replace_if_test, RangeTestN)
{
    auto res = alg::replace_if_n(v, std::size(v), i, j);

    EXPECT_EQ(v, (std::vector{1, 4, 3, 4}));
    EXPECT_EQ(res, std::end(v));
}

TEST_F(replace_if_test, ProjectionTestN)
{
    auto res = alg::replace_if_n(v, std::size(v), i, j, p);

    EXPECT_EQ(v, (std::vector{1, 2, 4, 2}));
    EXPECT_EQ(res, std::end(v));
}
