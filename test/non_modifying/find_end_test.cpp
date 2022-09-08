#include <vector>
#include <forward_list>
#include <functional>

#include <gtest/gtest.h>

#include "non_modifying.hpp"

class find_end_test : public ::testing::Test
{
protected:
    const std::vector<int> v{0, 1, 2, 3, 4, 2, 3, 4};
    const std::forward_list<int> l{0, 1, 2, 3, 4, 2, 3, 4};
    const std::vector<int> f{3, 4};
    const std::function<bool(int, int)> pred = [] (int i, int j) { return i % 3 == j % 3; };
    const std::function<int(int)> proj1 = [] (int i) { return i + 2; };
    const std::function<int(int)> proj2 = [] (int i) { return i - 1; };
};

TEST_F(find_end_test, EmptyRange)
{
    auto range = alg::find_end(std::begin(v), std::begin(v), std::begin(f), std::end(f));

    EXPECT_EQ(std::begin(range), std::begin(v));
    EXPECT_EQ(std::end(range), std::begin(v));

    range = alg::find_end(std::begin(v), std::end(v), std::begin(f), std::begin(f));

    EXPECT_EQ(std::begin(range), std::end(v));
    EXPECT_EQ(std::end(range), std::end(v));
}    	

TEST_F(find_end_test, BasicTest)
{
    auto range = alg::find_end(std::begin(v), std::end(v), std::begin(f), std::end(f));

    EXPECT_EQ(std::begin(range), std::begin(v) + 6);
    EXPECT_EQ(std::end(range), std::end(v));

    range = alg::find_end(std::begin(v), std::end(v), std::begin(f), std::end(f), pred);

    EXPECT_EQ(std::begin(range), std::begin(v) + 6);
    EXPECT_EQ(std::end(range), std::end(v));
}

TEST_F(find_end_test, RangeTest)
{
    auto range = alg::find_end(v, f);

    EXPECT_EQ(std::begin(range), std::begin(v) + 6);
    EXPECT_EQ(std::end(range), std::end(v));

    range = alg::find_end(v, f, pred);

    EXPECT_EQ(std::begin(range), std::begin(v) + 6);
    EXPECT_EQ(std::end(range), std::end(v));
}    	

TEST_F(find_end_test, ProjectionTest)
{
    auto range = alg::find_end(v, f, {}, proj1, proj2);

    EXPECT_EQ(std::begin(range), std::begin(v));
    EXPECT_EQ(std::end(range), std::begin(v) + 2);

    range = alg::find_end(v, f, pred, proj1, proj2);

    EXPECT_EQ(std::begin(range), std::begin(v) + 6);
    EXPECT_EQ(std::end(range), std::end(v));
}

TEST_F(find_end_test, EmptyRangeForward)
{
    auto range = alg::find_end(std::begin(l), std::begin(l), std::begin(f), std::end(f));

    EXPECT_EQ(std::begin(range), std::begin(l));
    EXPECT_EQ(std::end(range), std::begin(l));

    range = alg::find_end(std::begin(l), std::end(l), std::begin(f), std::begin(f));

    EXPECT_EQ(std::begin(range), std::end(l));
    EXPECT_EQ(std::end(range), std::end(l));
}    	

TEST_F(find_end_test, BasicTestForward)
{
    auto range = alg::find_end(std::begin(l), std::end(l), std::begin(f), std::end(f));

    EXPECT_EQ(std::begin(range), std::next(std::begin(l), 6));
    EXPECT_EQ(std::end(range), std::end(l));

    range = alg::find_end(std::begin(l), std::end(l), std::begin(f), std::end(f), pred);

    EXPECT_EQ(std::begin(range), std::next(std::begin(l), 6));
    EXPECT_EQ(std::end(range), std::end(l));
}

TEST_F(find_end_test, RangeTestForward)
{
    auto range = alg::find_end(l, f);

    EXPECT_EQ(std::begin(range), std::next(std::begin(l), 6));
    EXPECT_EQ(std::end(range), std::end(l));

    range = alg::find_end(l, f, pred);

    EXPECT_EQ(std::begin(range), std::next(std::begin(l), 6));
    EXPECT_EQ(std::end(range), std::end(l));
}

TEST_F(find_end_test, ProjectionTestForward)
{
    auto range = alg::find_end(l, f, {}, proj1, proj2);

    EXPECT_EQ(std::begin(range), std::begin(l));
    EXPECT_EQ(std::end(range), std::next(std::begin(l), 2));

    range = alg::find_end(l, f, pred, proj1, proj2);

    EXPECT_EQ(std::begin(range), std::next(std::begin(l), 6));
    EXPECT_EQ(std::end(range), std::end(l));
}
