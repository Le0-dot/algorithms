#include <vector>
#include <functional>

#include <gtest/gtest.h>

#include "modifying_operations.hpp"

class replace_copy_if_test : public ::testing::Test
{
protected:
    const std::vector<int> v1{1, 2, 3, 2};
    std::vector<int> v2{};
    const int j = 4; 
    const std::function<bool(int)> i = [] (int i) { return i == 2; };
    const std::function<int(int)> p = [] (int i) { return i - 1; };
};


TEST_F(replace_copy_if_test, EmptyRange)
{
    auto res = alg::replace_copy_if(std::begin(v1), std::begin(v1), std::back_inserter(v2), i, j);

    EXPECT_EQ(v2, (std::vector<int>{}));
    EXPECT_EQ(res.in, std::begin(v1));
}

TEST_F(replace_copy_if_test, BasicTest)
{
    auto res = alg::replace_copy_if(std::begin(v1), std::end(v1), std::back_inserter(v2), i, j);

    EXPECT_EQ(v2, (std::vector<int>{1, 4, 3, 4}));
    EXPECT_EQ(res.in, std::end(v1));
}

TEST_F(replace_copy_if_test, RangeTest)
{
    auto res = alg::replace_copy_if(v1, std::back_inserter(v2), i, j);

    EXPECT_EQ(v2, (std::vector<int>{1, 4, 3, 4}));
    EXPECT_EQ(res.in, std::end(v1));
}

TEST_F(replace_copy_if_test, ProjectionTest)
{
    auto res = alg::replace_copy_if(v1, std::back_inserter(v2), i, j, p);

    EXPECT_EQ(v2, (std::vector<int>{1, 2, 4, 2}));
    EXPECT_EQ(res.in, std::end(v1));
}

TEST_F(replace_copy_if_test, EmptyRangeN)
{
    auto res = alg::replace_copy_if_n(std::begin(v1), 0, std::back_inserter(v2), i, j);

    EXPECT_EQ(v2, (std::vector<int>{}));
    EXPECT_EQ(res.in, std::begin(v1));
}

TEST_F(replace_copy_if_test, BasicTestN)
{
    auto res = alg::replace_copy_if_n(std::begin(v1), std::size(v1), std::back_inserter(v2), i, j);

    EXPECT_EQ(v2, (std::vector<int>{1, 4, 3, 4}));
    EXPECT_EQ(res.in, std::end(v1));
}

TEST_F(replace_copy_if_test, RangeTestN)
{
    auto res = alg::replace_copy_if_n(v1, std::size(v1), std::back_inserter(v2), i, j);

    EXPECT_EQ(v2, (std::vector<int>{1, 4, 3, 4}));
    EXPECT_EQ(res.in, std::end(v1));
}

TEST_F(replace_copy_if_test, ProjectionTestN)
{
    auto res = alg::replace_copy_if_n(v1, std::size(v1), std::back_inserter(v2), i, j, p);

    EXPECT_EQ(v2, (std::vector<int>{1, 2, 4, 2}));
    EXPECT_EQ(res.in, std::end(v1));
}
