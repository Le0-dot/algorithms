#include <vector>
#include <functional>

#include <gtest/gtest.h>

#include "non_modifying_operations.hpp"

class count_test : public ::testing::Test
{
protected:
    const std::vector<int> v{1, 2, 3, 1, 2, 1};
    const std::function<bool(int)> p = [] (int i) { return !(i & 1); };
};

TEST_F(count_test, EmptyRange)
{
    EXPECT_EQ(alg::count(std::begin(v), std::begin(v), 1), 0);

    EXPECT_EQ(alg::count_n(std::begin(v), 0, 1), 0);
}

TEST_F(count_test, BasicTest)
{
    EXPECT_EQ(alg::count(std::begin(v), std::end(v), 1), 3);
    EXPECT_EQ(alg::count(std::begin(v), std::end(v), 2), 2);
    EXPECT_EQ(alg::count(std::begin(v), std::end(v), 3), 1);

    EXPECT_EQ(alg::count_n(std::begin(v), std::size(v), 1), 3);
    EXPECT_EQ(alg::count_n(std::begin(v), std::size(v), 2), 2);
    EXPECT_EQ(alg::count_n(std::begin(v), std::size(v), 3), 1);
}

TEST_F(count_test, RangeTest)
{
    EXPECT_EQ(alg::count(v, 1), 3);
    EXPECT_EQ(alg::count(v, 2), 2);
    EXPECT_EQ(alg::count(v, 3), 1);

    EXPECT_EQ(alg::count_n(v, std::size(v), 1), 3);
    EXPECT_EQ(alg::count_n(v, std::size(v), 2), 2);
    EXPECT_EQ(alg::count_n(v, std::size(v), 3), 1);
}

TEST_F(count_test, ProjectionTest)
{
    const auto proj = [] (int i) { return i + 1; };

    EXPECT_EQ(alg::count(v, 1, proj), 0);
    EXPECT_EQ(alg::count(v, 2, proj), 3);
    EXPECT_EQ(alg::count(v, 3, proj), 2);

    EXPECT_EQ(alg::count_n(v, std::size(v), 1, proj), 0);
    EXPECT_EQ(alg::count_n(v, std::size(v), 2, proj), 3);
    EXPECT_EQ(alg::count_n(v, std::size(v), 3, proj), 2);
}

TEST_F(count_test, EmptyRangeIf)
{
    EXPECT_EQ(alg::count_if(std::begin(v), std::begin(v), p), 0);

    EXPECT_EQ(alg::count_if_n(std::begin(v), 0, p), 0);
}

TEST_F(count_test, BasicTestIf)
{
    EXPECT_EQ(alg::count_if(std::begin(v), std::end(v), p), 2);

    EXPECT_EQ(alg::count_if_n(std::begin(v), std::size(v), p), 2);
}

TEST_F(count_test, RangeTestIf)
{
    EXPECT_EQ(alg::count_if(v, p), 2);

    EXPECT_EQ(alg::count_if_n(v, std::size(v), p), 2);
}

TEST_F(count_test, ProjectionTestIf)
{
    const auto proj = [] (int i) { return i + 1; };

    EXPECT_EQ(alg::count_if(v, p, proj), 4);

    EXPECT_EQ(alg::count_if_n(v, std::size(v), p, proj), 4);
}
