#include <vector>
#include <functional>

#include <gtest/gtest.h>

#include "modifying_operations.hpp"

class transform_test : public ::testing::Test
{
protected:
    const std::vector<int> v1{1, 2, 3};
    std::vector<int> v2{0, 1, 2};
    const std::function<int(int)> f1 = [] (int i) { return i * i; };
    const std::function<int(int, int)> f2 = [] (int a, int b) { return a * a + b * b; };
    const std::function<int(int)> p1 = [] (int i) { return i / 2; };
    const std::function<int(int)> p2 = [] (int i) { return i + 1; };
};


TEST_F(transform_test, EmptyRange)
{
    auto res = alg::transform(std::begin(v1), std::begin(v1), std::begin(v2), f1);

    EXPECT_EQ(v2, (std::vector{0, 1, 2}));
    EXPECT_EQ(res.in, std::begin(v1));
    EXPECT_EQ(res.out, std::begin(v2));
}

TEST_F(transform_test, BasicTest)
{
    auto res = alg::transform(std::begin(v1), std::end(v1), std::begin(v2), f1);

    EXPECT_EQ(v2, (std::vector{1, 4, 9}));
    EXPECT_EQ(res.in, std::begin(v1) + 3);
    EXPECT_EQ(res.out, std::begin(v2) + 3);
}

TEST_F(transform_test, RangeTest)
{
    auto res = alg::transform(v1, std::begin(v2), f1);

    EXPECT_EQ(v2, (std::vector{1, 4, 9}));
    EXPECT_EQ(res.in, std::begin(v1) + 3);
    EXPECT_EQ(res.out, std::begin(v2) + 3);
}

TEST_F(transform_test, ProjectionTest)
{
    auto res = alg::transform(v1, std::begin(v2), f1, p1);

    EXPECT_EQ(v2, (std::vector{0, 1, 1}));
    EXPECT_EQ(res.in, std::begin(v1) + 3);
    EXPECT_EQ(res.out, std::begin(v2) + 3);
}

TEST_F(transform_test, EmptyRangeBinary)
{
    auto res = alg::transform(std::begin(v1), std::begin(v1), std::begin(v2), std::end(v2), std::begin(v2), f2);

    EXPECT_EQ(v2, (std::vector{0, 1, 2}));
    EXPECT_EQ(res.in1, std::begin(v1));
    EXPECT_EQ(res.in2, std::begin(v2));
    EXPECT_EQ(res.out, std::begin(v2));

    res = alg::transform(std::begin(v1), std::end(v1), std::begin(v2), std::begin(v2), std::begin(v2), f2);

    EXPECT_EQ(v2, (std::vector{0, 1, 2}));
    EXPECT_EQ(res.in1, std::begin(v1));
    EXPECT_EQ(res.in2, std::begin(v2));
    EXPECT_EQ(res.out, std::begin(v2));
}

TEST_F(transform_test, BasicTestBinary)
{
    auto res = alg::transform(std::begin(v1), std::end(v1), std::begin(v2), std::end(v2), std::begin(v2), f2);

    EXPECT_EQ(v2, (std::vector{1, 5, 13}));
    EXPECT_EQ(res.in1, std::begin(v1) + 3);
    EXPECT_EQ(res.in2, std::begin(v2) + 3);
    EXPECT_EQ(res.out, std::begin(v2) + 3);
}

TEST_F(transform_test, RangeTestBinary)
{
    auto res = alg::transform(v1, v2, std::begin(v2), f2);

    EXPECT_EQ(v2, (std::vector{1, 5, 13}));
    EXPECT_EQ(res.in1, std::begin(v1) + 3);
    EXPECT_EQ(res.in2, std::begin(v2) + 3);
    EXPECT_EQ(res.out, std::begin(v2) + 3);
}

TEST_F(transform_test, ProjectionTestBinary)
{
    auto res = alg::transform(v1, v2, std::begin(v2), f2, p1, p2);

    EXPECT_EQ(v2, (std::vector{1, 5, 10}));
    EXPECT_EQ(res.in1, std::begin(v1) + 3);
    EXPECT_EQ(res.in2, std::begin(v2) + 3);
    EXPECT_EQ(res.out, std::begin(v2) + 3);
}

TEST_F(transform_test, EmptyRangeN)
{
    auto res = alg::transform_n(std::begin(v1), 0, std::begin(v2), f1);

    EXPECT_EQ(v2, (std::vector{0, 1, 2}));
    EXPECT_EQ(res.in, std::begin(v1));
    EXPECT_EQ(res.out, std::begin(v2));
}

TEST_F(transform_test, BasicTestN)
{
    auto res = alg::transform_n(std::begin(v1), std::size(v1) - 1, std::begin(v2), f1);

    EXPECT_EQ(v2, (std::vector{1, 4, 2}));
    EXPECT_EQ(res.in, std::begin(v1) + 2);
    EXPECT_EQ(res.out, std::begin(v2) + 2);

    res = alg::transform_n(std::begin(v1), std::size(v1), std::begin(v2), f1);

    EXPECT_EQ(v2, (std::vector{1, 4, 9}));
    EXPECT_EQ(res.in, std::begin(v1) + 3);
    EXPECT_EQ(res.out, std::begin(v2) + 3);
}

TEST_F(transform_test, RangeTestN)
{
    auto res = alg::transform_n(v1, std::size(v1) - 1, std::begin(v2), f1);

    EXPECT_EQ(v2, (std::vector{1, 4, 2}));
    EXPECT_EQ(res.in, std::begin(v1) + 2);
    EXPECT_EQ(res.out, std::begin(v2) + 2);

    res = alg::transform_n(v1, std::size(v1), std::begin(v2), f1);

    EXPECT_EQ(v2, (std::vector{1, 4, 9}));
    EXPECT_EQ(res.in, std::begin(v1) + 3);
    EXPECT_EQ(res.out, std::begin(v2) + 3);
}

TEST_F(transform_test, ProjectionTestN)
{
    auto res = alg::transform_n(v1, std::size(v1) - 1, std::begin(v2), f1, p1);

    EXPECT_EQ(v2, (std::vector{0, 1, 2}));
    EXPECT_EQ(res.in, std::begin(v1) + 2);
    EXPECT_EQ(res.out, std::begin(v2) + 2);

    res = alg::transform_n(v1, std::size(v1), std::begin(v2), f1, p1);

    EXPECT_EQ(v2, (std::vector{0, 1, 1}));
    EXPECT_EQ(res.in, std::begin(v1) + 3);
    EXPECT_EQ(res.out, std::begin(v2) + 3);
}

TEST_F(transform_test, EmptyRangeBinaryN)
{
    auto res = alg::transform_n(std::begin(v1), std::begin(v2), 0, std::begin(v2), f2);

    EXPECT_EQ(v2, (std::vector{0, 1, 2}));
    EXPECT_EQ(res.in1, std::begin(v1));
    EXPECT_EQ(res.in2, std::begin(v2));
    EXPECT_EQ(res.out, std::begin(v2));
}

TEST_F(transform_test, BasicTestBinaryN)
{
    auto res = alg::transform_n(std::begin(v1), std::begin(v2), std::size(v1) - 1, std::begin(v2), f2);

    EXPECT_EQ(v2, (std::vector{1, 5, 2}));
    EXPECT_EQ(res.in1, std::begin(v1) + 2);
    EXPECT_EQ(res.in2, std::begin(v2) + 2);
    EXPECT_EQ(res.out, std::begin(v2) + 2);

    res = alg::transform_n(std::begin(v1), std::begin(v2), std::size(v1), std::begin(v2), f2);

    EXPECT_EQ(v2, (std::vector{2, 29, 13}));
    EXPECT_EQ(res.in1, std::begin(v1) + 3);
    EXPECT_EQ(res.in2, std::begin(v2) + 3);
    EXPECT_EQ(res.out, std::begin(v2) + 3);
}

TEST_F(transform_test, RangeTestBinaryN)
{
    auto res = alg::transform_n(v1, v2, std::size(v1) - 1, std::begin(v2), f2);

    EXPECT_EQ(v2, (std::vector{1, 5, 2}));
    EXPECT_EQ(res.in1, std::begin(v1) + 2);
    EXPECT_EQ(res.in2, std::begin(v2) + 2);
    EXPECT_EQ(res.out, std::begin(v2) + 2);

    res = alg::transform_n(v1, v2, std::size(v1), std::begin(v2), f2);

    EXPECT_EQ(v2, (std::vector{2, 29, 13}));
    EXPECT_EQ(res.in1, std::begin(v1) + 3);
    EXPECT_EQ(res.in2, std::begin(v2) + 3);
    EXPECT_EQ(res.out, std::begin(v2) + 3);
}

TEST_F(transform_test, ProjectionTestBinaryN)
{
    auto res = alg::transform_n(v1, v2, std::size(v1) - 1, std::begin(v2), f2, p1, p2);

    EXPECT_EQ(v2, (std::vector{1, 5, 2}));
    EXPECT_EQ(res.in1, std::begin(v1) + 2);
    EXPECT_EQ(res.in2, std::begin(v2) + 2);
    EXPECT_EQ(res.out, std::begin(v2) + 2);

    res = alg::transform_n(v1, v2, std::size(v1), std::begin(v2), f2, p1, p2);

    EXPECT_EQ(v2, (std::vector{4, 37, 10}));
    EXPECT_EQ(res.in1, std::begin(v1) + 3);
    EXPECT_EQ(res.in2, std::begin(v2) + 3);
    EXPECT_EQ(res.out, std::begin(v2) + 3);
}
