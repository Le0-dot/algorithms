#include <vector>
#include <functional>

#include <gtest/gtest.h>

#include "modifying_operations.hpp"

class rotate_copy_test : public ::testing::Test
{
protected:
    const std::vector<int> v1{1, 2, 3, 4, 5};
    std::vector<int> v2{0, 0, 0, 0, 0};
};


TEST_F(rotate_copy_test, EmptyRange)
{
    auto res = alg::rotate_copy(std::begin(v1), std::begin(v1), std::begin(v1), std::begin(v2));

    EXPECT_EQ(v2, (std::vector{0, 0, 0, 0, 0}));
    EXPECT_EQ(res.in, std::begin(v1));
    EXPECT_EQ(res.out, std::begin(v2));
}

TEST_F(rotate_copy_test, BasicTest)
{
    auto res = alg::rotate_copy(std::begin(v1), std::begin(v1) + 2, std::end(v1), std::begin(v2));

    EXPECT_EQ(v2, (std::vector{3, 4, 5, 1, 2}));
    EXPECT_EQ(res.in, std::end(v1));
    EXPECT_EQ(res.out, std::end(v2));
}

TEST_F(rotate_copy_test, RangeTest)
{
    auto res = alg::rotate_copy(v1, std::begin(v1) + 2, std::begin(v2));

    EXPECT_EQ(v2, (std::vector{3, 4, 5, 1, 2}));
    EXPECT_EQ(res.in, std::end(v1));
    EXPECT_EQ(res.out, std::end(v2));
}
