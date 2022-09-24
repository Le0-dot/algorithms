#include <vector>
#include <sstream>
#include <functional>
#include <random>
#include <ranges>

#include <gtest/gtest.h>

#include "modifying_operations.hpp"

class sample_test : public ::testing::Test
{
protected:
    const std::vector<int> v1{1, 2, 3, 4, 5};
    std::vector<int> v2{0, 0, 0};
    std::istringstream s{"12345"};
    std::vector<char> v3{'X', 'X', 'X'};
    std::mt19937 gen{0}; // Generator intialized with constant will always produce same result
};


TEST_F(sample_test, EmptyRange)
{
    auto res = alg::sample(std::begin(v1), std::begin(v1), std::begin(v2), 3, gen);

    EXPECT_EQ(v2, (std::vector{0, 0, 0}));
    EXPECT_EQ(res, std::begin(v2));

    res = alg::sample(std::begin(v1), std::end(v1), std::begin(v2), 0, gen);

    EXPECT_EQ(v2, (std::vector{0, 0, 0}));
    EXPECT_EQ(res, std::begin(v2));
}

TEST_F(sample_test, BasicTest)
{
    auto res = alg::sample(std::begin(v1), std::end(v1), std::begin(v2), 3, gen);

    EXPECT_EQ(v2, (std::vector{1, 4, 5}));
    EXPECT_EQ(res, std::end(v2));
}

TEST_F(sample_test, RangeTest)
{
    auto res = alg::sample(v1, std::begin(v2), 3, gen);

    EXPECT_EQ(v1, (std::vector{1, 4, 5}));
    EXPECT_EQ(res, std::end(v2));
}

TEST_F(sample_test, EmptyRangeInput)
{
    auto res = alg::sample(std::istream_iterator<char>{s}, std::istream_iterator<char>{s}, std::begin(v3), 3, gen);

    EXPECT_EQ(v3, (std::vector{'X', 'X', 'X'}));
    EXPECT_EQ(res, std::begin(v3));

    res = alg::sample(std::istream_iterator<char>{s}, std::istream_iterator<char>{}, std::begin(v3), 0, gen);

    EXPECT_EQ(v3, (std::vector{'X', 'X', 'X'}));
    EXPECT_EQ(res, std::begin(v3));
}

TEST_F(sample_test, BasicTestInput)
{
    auto res = alg::sample(std::istream_iterator<char>{s}, std::istream_iterator<char>{}, std::begin(v3), 3, gen);

    EXPECT_EQ(v3, (std::vector{'1', '2', '5'}));
    EXPECT_EQ(res, std::end(v3));
}
