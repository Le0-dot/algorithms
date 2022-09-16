#include <vector>
#include <functional>
#include <ranges>

#include <gtest/gtest.h>

#include "minmax_operations.hpp"

class minmax_test : public ::testing::Test
{
protected:
    const int a = 2, b = 6;
    const std::vector<int> v{1, 4, 0, 7, 5};
    const std::initializer_list<int> l{1, 4, 0, 7, 5};
    const std::function<bool(int, int)> pred = [] (int i, int j) { return i > j; };
    const std::function<int(int)> p = [] (int i) { return i % 3; };
};

TEST_F(minmax_test, BasicTest)
{
    auto res = alg::minmax(a, b);

    EXPECT_EQ(res.min, a);
    EXPECT_EQ(res.max, b);

    auto res1 = alg::minmax(a, b, pred);
    
    EXPECT_EQ(res1.min, b);
    EXPECT_EQ(res1.max, a);

    auto resv = alg::minmax(v);

    EXPECT_EQ(resv.min, *(std::begin(v) + 2));
    EXPECT_EQ(resv.max, *(std::begin(v) + 3));

    resv = alg::minmax(v, pred);

    EXPECT_EQ(resv.min, *(std::begin(v) + 3));
    EXPECT_EQ(resv.max, *(std::begin(v) + 2));

    auto resl = alg::minmax(l);

    EXPECT_EQ(resl.min, *(std::begin(l) + 2));
    EXPECT_EQ(resl.max, *(std::begin(l) + 3));

    resl = alg::minmax(l, pred);

    EXPECT_EQ(resl.min, *(std::begin(l) + 3));
    EXPECT_EQ(resl.max, *(std::begin(l) + 2));
}

TEST_F(minmax_test, ProjectionTest)
{
    auto res = alg::minmax(a, b, {}, p);

    EXPECT_EQ(res.min, b);
    EXPECT_EQ(res.max, a);

    auto res1 = alg::minmax(a, b, pred, p);
    
    EXPECT_EQ(res1.min, a);
    EXPECT_EQ(res1.max, b);

    auto resv = alg::minmax(v, {}, p);

    EXPECT_EQ(resv.min, *(std::begin(v) + 2));
    EXPECT_EQ(resv.max, *(std::begin(v) + 4));

    resv = alg::minmax(v, pred, p);

    EXPECT_EQ(resv.min, *(std::begin(v) + 4));
    EXPECT_EQ(resv.max, *(std::begin(v) + 2));

    auto resl = alg::minmax(l, {}, p);

    EXPECT_EQ(resl.min, *(std::begin(l) + 2));
    EXPECT_EQ(resl.max, *(std::begin(l) + 4));

    resl = alg::minmax(l, pred, p);

    EXPECT_EQ(resl.min, *(std::begin(l) + 4));
    EXPECT_EQ(resl.max, *(std::begin(l) + 2));
}
