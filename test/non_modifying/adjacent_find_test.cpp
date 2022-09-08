#include <vector>
#include <functional>

#include <gtest/gtest.h>

#include "non_modifying.hpp"

class adjacent_find_test : public ::testing::Test
{
protected:
    const std::vector<char> v{1, 4, 2, 2};
    const std::function<bool(int, int)> pred = [] (int i, int j) { return i % 3 == j % 3; };
    const std::function<int(int)> proj = [] (int i) { return i * 2; };
};


TEST_F(adjacent_find_test, EmptyRange)
{
    EXPECT_EQ(alg::adjacent_find(std::begin(v), std::begin(v)), std::begin(v));
}

TEST_F(adjacent_find_test, BasicTest)
{
    EXPECT_EQ(alg::adjacent_find(std::begin(v), std::end(v)), std::begin(v) + 2);
    EXPECT_EQ(alg::adjacent_find(std::begin(v), std::end(v), pred), std::begin(v));

    EXPECT_EQ(alg::adjacent_find(std::begin(v), std::end(v) - 1), std::end(v) - 1);
}

TEST_F(adjacent_find_test, RangeTest)
{
    EXPECT_EQ(alg::adjacent_find(v), std::begin(v) + 2);
    EXPECT_EQ(alg::adjacent_find(v, pred), std::begin(v));
}

TEST_F(adjacent_find_test, ProjectionTest)
{
    EXPECT_EQ(alg::adjacent_find(v, {}, proj), std::begin(v) + 2);
    EXPECT_EQ(alg::adjacent_find(v, pred, proj), std::begin(v));
}

TEST_F(adjacent_find_test, EmptyRangeN)
{
    EXPECT_EQ(alg::adjacent_find_n(std::begin(v), 0), std::begin(v));
}

TEST_F(adjacent_find_test, BasicTestN)
{
    EXPECT_EQ(alg::adjacent_find_n(std::begin(v), std::size(v)), std::begin(v) + 2);
    EXPECT_EQ(alg::adjacent_find_n(std::begin(v), std::size(v), pred), std::begin(v));

    EXPECT_EQ(alg::adjacent_find_n(std::begin(v), std::size(v) - 1), std::end(v) - 1);
}

TEST_F(adjacent_find_test, RangeTestN)
{
    EXPECT_EQ(alg::adjacent_find_n(v, std::size(v)), std::begin(v) + 2);
    EXPECT_EQ(alg::adjacent_find_n(v, std::size(v), pred), std::begin(v));
}

TEST_F(adjacent_find_test, ProjectionTestN)
{
    EXPECT_EQ(alg::adjacent_find_n(v, std::size(v), {}, proj), std::begin(v) + 2);
    EXPECT_EQ(alg::adjacent_find_n(v, std::size(v), pred, proj), std::begin(v));
}
