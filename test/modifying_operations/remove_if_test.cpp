#include <vector>
#include <functional>

#include <gtest/gtest.h>

#include "modifying_operations.hpp"

class remove_if_test : public ::testing::Test
{
protected:
    std::vector<int> v{1, 2, 3, 2};
    const std::function<bool(int)> f = [] (int i) { return !(i & 1); };
    const std::function<int(int)> p = [] (int i) { return i - 1; };
};


TEST_F(remove_if_test, EmptyRange)
{
    auto res = alg::remove_if(std::begin(v), std::begin(v), f);
    v.erase(std::begin(res), std::end(res));

    EXPECT_EQ(std::size(v), 4);
    EXPECT_EQ(v, (std::vector{1, 2, 3, 2}));
}

TEST_F(remove_if_test, BasicTest)
{
    auto res = alg::remove_if(std::begin(v), std::end(v), f);
    v.erase(std::begin(res), std::end(res));

    EXPECT_EQ(std::size(v), 2);
    EXPECT_EQ(v, (std::vector{1, 3}));
}

TEST_F(remove_if_test, RangeTest)
{
    auto res = alg::remove_if(v, f);
    v.erase(std::begin(res), std::end(res));

    EXPECT_EQ(std::size(v), 2);
    EXPECT_EQ(v, (std::vector{1, 3}));
}

TEST_F(remove_if_test, ProjectionTest)
{
    auto res = alg::remove_if(v, f, p);
    v.erase(std::begin(res), std::end(res));

    EXPECT_EQ(std::size(v), 2);
    EXPECT_EQ(v, (std::vector{2, 2}));
}

TEST_F(remove_if_test, EmptyRangeN)
{
    auto res = alg::remove_if_n(std::begin(v), 0, f);
    v.erase(std::begin(res), std::end(res));

    EXPECT_EQ(std::size(v), 4);
    EXPECT_EQ(v, (std::vector{1, 2, 3, 2}));
}

TEST_F(remove_if_test, BasicTestN)
{
    auto res = alg::remove_if_n(std::begin(v), std::size(v), f);
    v.erase(std::begin(res), std::end(res));

    EXPECT_EQ(std::size(v), 2);
    EXPECT_EQ(v, (std::vector{1, 3}));
}

TEST_F(remove_if_test, RangeTestN)
{
    auto res = alg::remove_if_n(v, std::size(v), f);
    v.erase(std::begin(res), std::end(res));

    EXPECT_EQ(std::size(v), 2);
    EXPECT_EQ(v, (std::vector{1, 3}));
}

TEST_F(remove_if_test, ProjectionTestN)
{
    auto res = alg::remove_if_n(v, std::size(v), f, p);
    v.erase(std::begin(res), std::end(res));

    EXPECT_EQ(std::size(v), 2);
    EXPECT_EQ(v, (std::vector{2, 2}));
}
