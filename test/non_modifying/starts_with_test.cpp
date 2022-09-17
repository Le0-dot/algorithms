#include <vector>
#include <functional>

#include <gtest/gtest.h>

#include "non_modifying_operations.hpp"

class starts_with_test : public ::testing::Test
{
protected:
    const std::vector<int> v{1, 2, 3, 4};
    const std::vector<int> f{1, 2};
    const std::function<bool(int, int)> pred = [] (int i, int j) { return i % 3 == (j + 1) % 3; };
    const std::function<int(int)> proj1 = [] (int i) { return i + 3; };
    const std::function<int(int)> proj2 = [] (int i) { return i - 1; };
};

TEST_F(starts_with_test, EmptyRange)
{
    EXPECT_FALSE(alg::starts_with(std::begin(v), std::begin(v), std::begin(f), std::end(f)));
    EXPECT_TRUE(alg::starts_with(std::begin(v), std::end(v), std::begin(f), std::begin(f)));
}    	

TEST_F(starts_with_test, BasicTest)
{
    EXPECT_TRUE(alg::starts_with(std::begin(v), std::end(v), std::begin(f), std::end(f)));
    EXPECT_FALSE(alg::starts_with(std::begin(v), std::end(v), std::begin(f), std::end(f), pred));
}

TEST_F(starts_with_test, RangeTest)
{
    EXPECT_TRUE(alg::starts_with(v, f));
    EXPECT_FALSE(alg::starts_with(v, f, pred));
}    	

TEST_F(starts_with_test, ProjectionTest)
{
    EXPECT_FALSE(alg::starts_with(v, f, {}, proj1, proj2));
    EXPECT_TRUE(alg::starts_with(v, f, pred, proj1, proj2));
}

TEST_F(starts_with_test, EmptyRangeN)
{
    EXPECT_TRUE(alg::starts_with_n(std::begin(v), std::begin(f), 0));
}

TEST_F(starts_with_test, BasicTestN)
{
    EXPECT_TRUE(alg::starts_with_n(std::begin(v), std::begin(f), std::size(f)));
    EXPECT_FALSE(alg::starts_with_n(std::begin(v), std::begin(f), std::size(f), pred));
}

TEST_F(starts_with_test, RangeTestN)
{
    EXPECT_TRUE(alg::starts_with_n(v, f, std::size(f)));
    EXPECT_FALSE(alg::starts_with_n(v, f, std::size(f), pred));
}

TEST_F(starts_with_test, ProjectionTestN)
{
    EXPECT_FALSE(alg::starts_with_n(v, f, std::size(f), {}, proj1, proj2));
    EXPECT_TRUE(alg::starts_with_n(v, f, std::size(f), pred, proj1, proj2));
}
