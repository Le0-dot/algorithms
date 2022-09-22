#include <vector>
#include <functional>

#include <gtest/gtest.h>

#include "modifying_operations.hpp"

class remove_test : public ::testing::Test
{
protected:
    std::vector<int> v{1, 2, 3, 2};
    const int i = 2; 
    const std::function<int(int)> p = [] (int i) { return i - 1; };
};


TEST_F(remove_test, EmptyRange)
{
    auto res = alg::remove(std::begin(v), std::begin(v), i);
    v.erase(std::begin(res), std::end(res));

    EXPECT_EQ(std::size(v), 4);
    EXPECT_EQ(v, (std::vector<int>{1, 2, 3, 2}));
}

TEST_F(remove_test, BasicTest)
{
    auto res = alg::remove(std::begin(v), std::end(v), i);
    v.erase(std::begin(res), std::end(res));

    EXPECT_EQ(std::size(v), 2);
    EXPECT_EQ(v, (std::vector<int>{1, 3}));
}

TEST_F(remove_test, RangeTest)
{
    auto res = alg::remove(v, i);
    v.erase(std::begin(res), std::end(res));

    EXPECT_EQ(std::size(v), 2);
    EXPECT_EQ(v, (std::vector<int>{1, 3}));
}

TEST_F(remove_test, ProjectionTest)
{
    auto res = alg::remove(v, i, p);
    v.erase(std::begin(res), std::end(res));

    EXPECT_EQ(std::size(v), 3);
    EXPECT_EQ(v, (std::vector<int>{1, 2, 2}));
}

TEST_F(remove_test, EmptyRangeN)
{
    auto res = alg::remove_n(std::begin(v), 0, i);
    v.erase(std::begin(res), std::end(res));

    EXPECT_EQ(std::size(v), 4);
    EXPECT_EQ(v, (std::vector<int>{1, 2, 3, 2}));
}

TEST_F(remove_test, BasicTestN)
{
    auto res = alg::remove_n(std::begin(v), std::size(v), i);
    v.erase(std::begin(res), std::end(res));

    EXPECT_EQ(std::size(v), 2);
    EXPECT_EQ(v, (std::vector<int>{1, 3}));
}

TEST_F(remove_test, RangeTestN)
{
    auto res = alg::remove_n(v, std::size(v), i);
    v.erase(std::begin(res), std::end(res));

    EXPECT_EQ(std::size(v), 2);
    EXPECT_EQ(v, (std::vector<int>{1, 3}));
}

TEST_F(remove_test, ProjectionTestN)
{
    auto res = alg::remove_n(v, std::size(v), i, p);
    v.erase(std::begin(res), std::end(res));

    EXPECT_EQ(std::size(v), 3);
    EXPECT_EQ(v, (std::vector<int>{1, 2, 2}));
}
