#include <vector>
#include <functional>

#include <gtest/gtest.h>

#include "modifying_operations.hpp"

class remove_copy_test : public ::testing::Test
{
protected:
    const std::vector<int> v1{1, 2, 3, 2};
    std::vector<int> v2{};
    const int i = 2; 
    const std::function<int(int)> p = [] (int i) { return i - 1; };
};


TEST_F(remove_copy_test, EmptyRange)
{
    auto res = alg::remove_copy(std::begin(v1), std::begin(v1), std::back_inserter(v2), i);

    EXPECT_EQ(v2, (std::vector<int>{}));
    EXPECT_EQ(res.in, std::begin(v1));
}

TEST_F(remove_copy_test, BasicTest)
{
    auto res = alg::remove_copy(std::begin(v1), std::end(v1), std::back_inserter(v2), i);

    EXPECT_EQ(v2, (std::vector{1, 3}));
    EXPECT_EQ(res.in, std::end(v1));
}

TEST_F(remove_copy_test, RangeTest)
{
    auto res = alg::remove_copy(v1, std::back_inserter(v2), i);

    EXPECT_EQ(v2, (std::vector{1, 3}));
    EXPECT_EQ(res.in, std::end(v1));
}

TEST_F(remove_copy_test, ProjectionTest)
{
    auto res = alg::remove_copy(v1, std::back_inserter(v2), i, p);

    EXPECT_EQ(v2, (std::vector{1, 2, 2}));
    EXPECT_EQ(res.in, std::end(v1));
}

TEST_F(remove_copy_test, EmptyRangeN)
{
    auto res = alg::remove_copy_n(std::begin(v1), 0, std::back_inserter(v2), i);

    EXPECT_EQ(v2, (std::vector<int>{}));
    EXPECT_EQ(res.in, std::begin(v1));
}

TEST_F(remove_copy_test, BasicTestN)
{
    auto res = alg::remove_copy_n(std::begin(v1), std::size(v1), std::back_inserter(v2), i);

    EXPECT_EQ(v2, (std::vector{1, 3}));
    EXPECT_EQ(res.in, std::end(v1));
}

TEST_F(remove_copy_test, RangeTestN)
{
    auto res = alg::remove_copy_n(v1, std::size(v1), std::back_inserter(v2), i);

    EXPECT_EQ(v2, (std::vector{1, 3}));
    EXPECT_EQ(res.in, std::end(v1));
}

TEST_F(remove_copy_test, ProjectionTestN)
{
    auto res = alg::remove_copy_n(v1, std::size(v1), std::back_inserter(v2), i, p);

    EXPECT_EQ(v2, (std::vector{1, 2, 2}));
    EXPECT_EQ(res.in, std::end(v1));
}
