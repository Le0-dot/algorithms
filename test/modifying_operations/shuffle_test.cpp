#include <vector>
#include <functional>
#include <random>

#include <gtest/gtest.h>

#include "modifying_operations.hpp"

class shuffle_test : public ::testing::Test
{
protected:
    std::vector<int> v{1, 2, 3, 4, 5};
    std::mt19937 gen{0}; // Generator intialized with constant will always produce same result
			 // so random shuffling of whole range will produce {1, 3, 4, 2, 5}
};


TEST_F(shuffle_test, EmptyRange)
{
    auto res = alg::shuffle(std::begin(v), std::begin(v), gen);

    EXPECT_EQ(v, (std::vector{1, 2, 3, 4, 5}));
    EXPECT_EQ(res, std::begin(v));
}

TEST_F(shuffle_test, BasicTest)
{
    auto res = alg::shuffle(std::begin(v), std::end(v), gen);

    EXPECT_EQ(v, (std::vector{1, 3, 4, 2, 5}));
    EXPECT_EQ(res, std::end(v));
}

TEST_F(shuffle_test, RangeTest)
{
    auto res = alg::shuffle(v, gen);

    EXPECT_EQ(v, (std::vector{1, 3, 4, 2, 5}));
    EXPECT_EQ(res, std::end(v));
}
