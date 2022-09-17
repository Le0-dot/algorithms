#include <vector>
#include <functional>

#include <gtest/gtest.h>

#include "non_modifying_operations.hpp"

class predicate_of_test : public ::testing::Test
{
protected:
    const std::vector<int> v{1, 2, 3, 1, 2, 1};
    const std::function<bool(int)> p = [] (int i) { return !(i & 1); };
    const std::function<int(int)> proj = [] (int i) { return i * 2; };
};

TEST_F(predicate_of_test, EmptyRange)
{
    EXPECT_TRUE(alg::all_of(std::begin(v), std::begin(v), p));
    EXPECT_FALSE(alg::any_of(std::begin(v), std::begin(v), p));
    EXPECT_TRUE(alg::none_of(std::begin(v), std::begin(v), p));
}

TEST_F(predicate_of_test, BasicTest)
{
    EXPECT_FALSE(alg::all_of(std::begin(v), std::end(v), p));
    EXPECT_TRUE(alg::any_of(std::begin(v), std::end(v), p));
    EXPECT_FALSE(alg::none_of(std::begin(v), std::end(v), p));
}

TEST_F(predicate_of_test, RangeTest)
{
    EXPECT_FALSE(alg::all_of(v, p));
    EXPECT_TRUE(alg::any_of(v, p));
    EXPECT_FALSE(alg::none_of(v, p));
}

TEST_F(predicate_of_test, ProjectionTest)
{
    EXPECT_TRUE(alg::all_of(v, p, proj));
    EXPECT_TRUE(alg::any_of(v, p, proj));
    EXPECT_FALSE(alg::none_of(v, p, proj));
}

TEST_F(predicate_of_test, EmptyRangeN)
{
    EXPECT_TRUE(alg::all_of_n(std::begin(v), 0, p));
    EXPECT_FALSE(alg::any_of_n(std::begin(v), 0, p));
    EXPECT_TRUE(alg::none_of_n(std::begin(v), 0, p));
}

TEST_F(predicate_of_test, BasicTestN)
{
    EXPECT_FALSE(alg::all_of_n(std::begin(v), std::size(v), p));
    EXPECT_TRUE(alg::any_of_n(std::begin(v), std::size(v), p));
    EXPECT_FALSE(alg::none_of_n(std::begin(v), std::size(v), p));
}

TEST_F(predicate_of_test, RangeTestN)
{
    EXPECT_FALSE(alg::all_of_n(v, std::size(v), p));
    EXPECT_TRUE(alg::any_of_n(v, std::size(v), p));
    EXPECT_FALSE(alg::none_of_n(v, std::size(v), p));
}

TEST_F(predicate_of_test, ProjectionTestN)
{
    EXPECT_TRUE(alg::all_of_n(v, std::size(v), p, proj));
    EXPECT_TRUE(alg::any_of_n(v, std::size(v), p, proj));
    EXPECT_FALSE(alg::none_of_n(v, std::size(v), p, proj));
}
