#include <iterator>
#include <vector>
#include <functional>

#include <gtest/gtest.h>

#include "set_operations.hpp"

class set_symmetric_difference_test : public ::testing::Test
{
protected:
    const std::vector<int> v1{1, 2, 4, 5, 6}, v2{2, 5, 7};
    std::vector<int> v3{};
    const std::function<bool(int, int)> f = std::ranges::greater();
    const std::function<char(int)> p1 = [] (int i) { return i; };
    const std::function<char(int)> p2 = [] (int i) { return i + 1; };
};


TEST_F(set_symmetric_difference_test, EmptyRangeTest)
{
    auto res = ::alg::set_symmetric_difference(std::begin(v1), std::begin(v1), std::begin(v2), std::end(v2), std::back_inserter(v3));

    EXPECT_EQ(res.in1, std::begin(v1));
    EXPECT_EQ(res.in2, std::end(v2));
    EXPECT_EQ(std::size(v3), std::size(v2));
    EXPECT_EQ(v3, v2);

    v3.clear();

    res = ::alg::set_symmetric_difference(std::begin(v1), std::end(v1), std::begin(v2), std::begin(v2), std::back_inserter(v3));

    EXPECT_EQ(res.in1, std::end(v1));
    EXPECT_EQ(res.in2, std::begin(v2));
    EXPECT_EQ(std::size(v3), std::size(v1));
    EXPECT_EQ(v3, v1);

    v3.clear();

    res = ::alg::set_symmetric_difference(std::begin(v1), std::begin(v1), std::begin(v2), std::begin(v2), std::back_inserter(v3));

    EXPECT_EQ(res.in1, std::begin(v1));
    EXPECT_EQ(res.in2, std::begin(v2));
    EXPECT_EQ(std::size(v3), 0);
}

TEST_F(set_symmetric_difference_test, BasicTest)
{
    auto res = ::alg::set_symmetric_difference(std::begin(v1), std::end(v1), std::begin(v2), std::end(v2), std::back_inserter(v3));

    EXPECT_EQ(res.in1, std::end(v1));
    EXPECT_EQ(res.in2, std::end(v2));
    EXPECT_EQ(std::size(v3), 4);
    EXPECT_EQ(v3, (std::vector{1, 4, 6, 7}));
}

TEST_F(set_symmetric_difference_test, RangeTest)
{
    auto res = ::alg::set_symmetric_difference(v1, v2, std::back_inserter(v3));

    EXPECT_EQ(res.in1, std::end(v1));
    EXPECT_EQ(res.in2, std::end(v2));
    EXPECT_EQ(std::size(v3), 4);
    EXPECT_EQ(v3, (std::vector{1, 4, 6, 7}));
}

TEST_F(set_symmetric_difference_test, ProjectionTest)
{
    auto res = ::alg::set_symmetric_difference(std::begin(v1), std::end(v1), std::begin(v2), std::end(v2), std::back_inserter(v3), {}, p1, p2);

    EXPECT_EQ(res.in1, std::end(v1));
    EXPECT_EQ(res.in2, std::end(v2));
    EXPECT_EQ(std::size(v3), 6);
    EXPECT_EQ(v3, (std::vector{1, 2, 2, 4, 5, 7}));
}
