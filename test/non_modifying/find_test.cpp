#include <vector>
#include <functional>

#include <gtest/gtest.h>

#include "non_modifying.hpp"

class find_test : public ::testing::Test
{
protected:
    const std::vector<int> v{1, 2, 3, 4};
    const std::function<bool(int)> pred = [] (int i) { return !(i % 3); };
    const std::function<bool(int)> pred2 = [] (int i) { return i != 3; };
    const std::function<int(int)> proj = [] (int i) { return i + 2; };
};

TEST_F(find_test, EmptyRange)
{
    EXPECT_EQ(alg::find(std::begin(v), std::begin(v), 4), std::begin(v));
}    	

TEST_F(find_test, BasicTest)
{
    EXPECT_EQ(alg::find(std::begin(v), std::end(v), 4), std::begin(v) + 3);
}

TEST_F(find_test, RangeTest)
{
    EXPECT_EQ(alg::find(v, 4), std::begin(v) + 3);
}    	

TEST_F(find_test, ProjectionTest)
{
    EXPECT_EQ(alg::find(v, 4, proj), std::begin(v) + 1);
}

TEST_F(find_test, EmptyRangeN)
{
    EXPECT_EQ(alg::find_n(std::begin(v), 0, 4), std::begin(v));
}

TEST_F(find_test, BasicTestN)
{
    EXPECT_EQ(alg::find_n(std::begin(v), 4, 4), std::begin(v) + 3);
}

TEST_F(find_test, RangeTestN)
{
    EXPECT_EQ(alg::find_n(v, 4, 4), std::begin(v) + 3);
}

TEST_F(find_test, ProjectionTestN)
{
    EXPECT_EQ(alg::find_n(v, 4, 4, proj), std::begin(v) + 1);
}

TEST_F(find_test, EmptyRangeIf)
{
    EXPECT_EQ(alg::find_if(std::begin(v), std::begin(v), pred), std::begin(v));
}    	

TEST_F(find_test, BasicTestIf)
{
    EXPECT_EQ(alg::find_if(std::begin(v), std::end(v), pred), std::begin(v) + 2);
}

TEST_F(find_test, RangeTestIf)
{
    EXPECT_EQ(alg::find_if(v, pred), std::begin(v) + 2);
}    	

TEST_F(find_test, ProjectionTestIf)
{
    EXPECT_EQ(alg::find_if(v, pred, proj), std::begin(v));
}

TEST_F(find_test, EmptyRangeIfN)
{
    EXPECT_EQ(alg::find_if_n(std::begin(v), 0, pred), std::begin(v));
}

TEST_F(find_test, BasicTestIfN)
{
    EXPECT_EQ(alg::find_if_n(std::begin(v), 4, pred), std::begin(v) + 2);
}

TEST_F(find_test, RangeTestIfN)
{
    EXPECT_EQ(alg::find_if_n(v, 4, pred), std::begin(v) + 2);
}

TEST_F(find_test, ProjectionTestIfN)
{
    EXPECT_EQ(alg::find_if_n(v, 4, pred, proj), std::begin(v));
}

TEST_F(find_test, EmptyRangeIfNot)
{
    EXPECT_EQ(alg::find_if_not(std::begin(v), std::begin(v), pred2), std::begin(v));
}    	

TEST_F(find_test, BasicTestIfNot)
{
    EXPECT_EQ(alg::find_if_not(std::begin(v), std::end(v), pred2), std::begin(v) + 2);
}

TEST_F(find_test, RangeTestIfNot)
{
    EXPECT_EQ(alg::find_if_not(v, pred2), std::begin(v) + 2);
}    	

TEST_F(find_test, ProjectionTestIfNot)
{
    EXPECT_EQ(alg::find_if_not(v, pred2, proj), std::begin(v));
}

TEST_F(find_test, EmptyRangeIfNotN)
{
    EXPECT_EQ(alg::find_if_not_n(std::begin(v), 0, pred2), std::begin(v));
}

TEST_F(find_test, BasicTestIfNotN)
{
    EXPECT_EQ(alg::find_if_not_n(std::begin(v), 4, pred2), std::begin(v) + 2);
}

TEST_F(find_test, RangeTestIfNotN)
{
    EXPECT_EQ(alg::find_if_not_n(v, 4, pred2), std::begin(v) + 2);
}

TEST_F(find_test, ProjectionTestIfNotN)
{
    EXPECT_EQ(alg::find_if_not_n(v, 4, pred2, proj), std::begin(v));
}
