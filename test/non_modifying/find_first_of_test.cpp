#include <vector>
#include <functional>

#include <gtest/gtest.h>

#include "non_modifying.hpp"

class find_first_of_test : public ::testing::Test
{
protected:
    const std::vector<int> v{1, 2, 3, 4};
    const std::vector<int> f{3, 5};
    const std::function<bool(int, int)> pred = [] (int i, int j) { return i % 3 == j % 3; };
    const std::function<int(int)> proj1 = [] (int i) { return i + 2; };
    const std::function<int(int)> proj2 = [] (int i) { return i - 1; };
};

TEST_F(find_first_of_test, EmptyRange)
{
    EXPECT_EQ(alg::find_first_of(std::begin(v), std::begin(v), std::begin(f), std::end(f)), std::begin(v));
}    	

TEST_F(find_first_of_test, BasicTest)
{
    EXPECT_EQ(alg::find_first_of(std::begin(v), std::end(v), std::begin(f), std::end(f)), std::begin(v) + 2);
    EXPECT_EQ(alg::find_first_of(std::begin(v), std::end(v), std::begin(f), std::end(f), pred), std::begin(v) + 1);
}

TEST_F(find_first_of_test, RangeTest)
{
    EXPECT_EQ(alg::find_first_of(v, f), std::begin(v) + 2);
    EXPECT_EQ(alg::find_first_of(v, f, pred), std::begin(v) + 1);
}    	

TEST_F(find_first_of_test, ProjectionTest)
{
    EXPECT_EQ(alg::find_first_of(v, f, {}, proj1, proj2), std::begin(v) + 1);
    EXPECT_EQ(alg::find_first_of(v, f, pred, proj1, proj2), std::begin(v) + 1);
}

TEST_F(find_first_of_test, EmptyRangeN)
{
    EXPECT_EQ(alg::find_first_of_n(std::begin(v), 0, std::begin(f), std::size(f)), std::begin(v));
}

TEST_F(find_first_of_test, BasicTestN)
{
    EXPECT_EQ(alg::find_first_of_n(std::begin(v), std::size(v), std::begin(f), std::size(f)), std::begin(v) + 2);
    EXPECT_EQ(alg::find_first_of_n(std::begin(v), std::size(v), std::begin(f), std::size(f), pred), std::begin(v) + 1);
}

TEST_F(find_first_of_test, RangeTestN)
{
    EXPECT_EQ(alg::find_first_of_n(v, std::size(v), f, std::size(f)), std::begin(v) + 2);
    EXPECT_EQ(alg::find_first_of_n(v, std::size(v), f, std::size(f), pred), std::begin(v) + 1);
}

TEST_F(find_first_of_test, ProjectionTestN)
{
    EXPECT_EQ(alg::find_first_of_n(v, std::size(v), f, std::size(f), {}, proj1, proj2), std::begin(v) + 1);
    EXPECT_EQ(alg::find_first_of_n(v, std::size(v), f, std::size(f), pred, proj1, proj2), std::begin(v) + 1);
}
