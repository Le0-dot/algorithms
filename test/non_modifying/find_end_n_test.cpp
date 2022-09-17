#include <vector>
#include <forward_list>
#include <list>
#include <functional>

#include <gtest/gtest.h>

#include "non_modifying_operations.hpp"

class find_end_n_test : public ::testing::Test
{
protected:
    const std::vector<int> v{1, 2, 2, 3, 2, 2, 1};
    const std::forward_list<int> fl{1, 2, 2, 3, 2, 2, 1};
    const std::list<int> l{1, 2, 2, 3, 2, 2, 1};
    const std::function<bool(int, int)> pred = [] (int i, int j) { return i % 3 == j % 3; };
    const std::function<int(int)> proj = [] (int i) { return i * i; };
};

TEST_F(find_end_n_test, EmptyRangeRandomAccess)
{
    auto range = alg::find_end_n(std::begin(v), std::begin(v), 2, 2);

    EXPECT_EQ(std::begin(range), std::begin(v));
    EXPECT_EQ(std::end(range), std::begin(v));

    range = alg::find_end_n(std::begin(v), std::end(v), 0, 2);

    EXPECT_EQ(std::begin(range), std::end(v));
    EXPECT_EQ(std::end(range), std::end(v));
}

TEST_F(find_end_n_test, BasicTestRandomAccess)
{
    auto range = alg::find_end_n(std::begin(v), std::end(v), 2, 2);

    EXPECT_EQ(std::begin(range), std::begin(v) + 4);
    EXPECT_EQ(std::end(range), std::begin(v) + 6);

    range = alg::find_end_n(std::begin(v), std::end(v), 2, 2, pred);

    EXPECT_EQ(std::begin(range), std::begin(v) + 4);
    EXPECT_EQ(std::end(range), std::begin(v) + 6);
    
    range = alg::find_end_n(std::begin(v), std::end(v), 2, 1, pred);

    EXPECT_EQ(std::begin(range), std::begin(v));
    EXPECT_EQ(std::end(range), std::begin(v));
}

TEST_F(find_end_n_test, RangeTestRandomAccess)
{
    auto range = alg::find_end_n(v, 2, 2);

    EXPECT_EQ(std::begin(range), std::begin(v) + 4);
    EXPECT_EQ(std::end(range), std::begin(v) + 6);

    range = alg::find_end_n(v, 2, 2, pred);

    EXPECT_EQ(std::begin(range), std::begin(v) + 4);
    EXPECT_EQ(std::end(range), std::begin(v) + 6);
    
    range = alg::find_end_n(v, 2, 1, pred);

    EXPECT_EQ(std::begin(range), std::begin(v));
    EXPECT_EQ(std::end(range), std::begin(v));
}

TEST_F(find_end_n_test, ProjectionTestRandomAccess)
{
    auto range = alg::find_end_n(v, 2, 4, {}, proj);

    EXPECT_EQ(std::begin(range), std::begin(v) + 4);
    EXPECT_EQ(std::end(range), std::begin(v) + 6);

    range = alg::find_end_n(v, 3, 1, pred, proj);

    EXPECT_EQ(std::begin(range), std::begin(v) + 4);
    EXPECT_EQ(std::end(range), std::begin(v) + 7);
}

TEST_F(find_end_n_test, EmptyRangeForward)
{
    auto range = alg::find_end_n(std::begin(fl), std::begin(fl), 2, 2);

    EXPECT_EQ(std::begin(range), std::begin(fl));
    EXPECT_EQ(std::end(range), std::begin(fl));

    range = alg::find_end_n(std::begin(fl), std::end(fl), 0, 2);

    EXPECT_EQ(std::begin(range), std::end(fl));
    EXPECT_EQ(std::end(range), std::end(fl));
}

TEST_F(find_end_n_test, BasicTestForward)
{
    auto range = alg::find_end_n(std::begin(fl), std::end(fl), 2, 2);
    auto begin = std::next(std::begin(fl), 4);
    auto end = std::next(std::begin(fl), 6);

    EXPECT_EQ(std::begin(range), begin);
    EXPECT_EQ(std::end(range), end);

    range = alg::find_end_n(std::begin(fl), std::end(fl), 2, 2, pred);

    EXPECT_EQ(std::begin(range), begin);
    EXPECT_EQ(std::end(range), end);
    
    range = alg::find_end_n(std::begin(fl), std::end(fl), 2, 1, pred);
    begin = std::begin(fl);
    end = std::begin(fl);

    EXPECT_EQ(std::begin(range), begin);
    EXPECT_EQ(std::end(range), end);
}

TEST_F(find_end_n_test, RangeTestForward)
{
    auto range = alg::find_end_n(fl, 2, 2);
    auto begin = std::next(std::begin(fl), 4);
    auto end = std::next(std::begin(fl), 6);

    EXPECT_EQ(std::begin(range), begin);
    EXPECT_EQ(std::end(range), end);

    range = alg::find_end_n(fl, 2, 2, pred);

    EXPECT_EQ(std::begin(range), begin);
    EXPECT_EQ(std::end(range), end);
    
    range = alg::find_end_n(fl, 2, 1, pred);
    begin = std::begin(fl);
    end = std::begin(fl);

    EXPECT_EQ(std::begin(range), begin);
    EXPECT_EQ(std::end(range), end);
}

TEST_F(find_end_n_test, ProjectionTestForward)
{
    auto range = alg::find_end_n(fl, 2, 4, {}, proj);
    auto begin = std::next(std::begin(fl), 4);
    auto end = std::next(std::begin(fl), 6);

    EXPECT_EQ(std::begin(range), begin);
    EXPECT_EQ(std::end(range), end);

    range = alg::find_end_n(fl, 3, 1, pred, proj);
    begin = std::next(std::begin(fl), 4);
    end = std::next(std::begin(fl), 7);

    EXPECT_EQ(std::begin(range), begin);
    EXPECT_EQ(std::end(range), end);
}

TEST_F(find_end_n_test, EmptyRangeBidirectional)
{
    auto range = alg::find_end_n(std::begin(l), std::begin(l), 2, 2);

    EXPECT_EQ(std::begin(range), std::begin(l));
    EXPECT_EQ(std::end(range), std::begin(l));

    range = alg::find_end_n(std::begin(l), std::end(l), 0, 2);

    EXPECT_EQ(std::begin(range), std::end(l));
    EXPECT_EQ(std::end(range), std::end(l));
}

TEST_F(find_end_n_test, BasicTestBidirectional)
{
    auto range = alg::find_end_n(std::begin(l), std::end(l), 2, 2);
    auto begin = std::next(std::begin(l), 4);
    auto end = std::next(std::begin(l), 6);

    EXPECT_EQ(std::begin(range), begin);
    EXPECT_EQ(std::end(range), end);

    range = alg::find_end_n(std::begin(l), std::end(l), 2, 2, pred);

    EXPECT_EQ(std::begin(range), begin);
    EXPECT_EQ(std::end(range), end);
    
    range = alg::find_end_n(std::begin(l), std::end(l), 2, 1, pred);
    begin = std::begin(l);
    end = std::begin(l);

    EXPECT_EQ(std::begin(range), begin);
    EXPECT_EQ(std::end(range), end);
}

TEST_F(find_end_n_test, RangeTestBidirectional)
{
    auto range = alg::find_end_n(l, 2, 2);
    auto begin = std::next(std::begin(l), 4);
    auto end = std::next(std::begin(l), 6);

    EXPECT_EQ(std::begin(range), begin);
    EXPECT_EQ(std::end(range), end);

    range = alg::find_end_n(l, 2, 2, pred);

    EXPECT_EQ(std::begin(range), begin);
    EXPECT_EQ(std::end(range), end);
    
    range = alg::find_end_n(l, 2, 1, pred);
    begin = std::begin(l);
    end = std::begin(l);

    EXPECT_EQ(std::begin(range), begin);
    EXPECT_EQ(std::end(range), end);
}

TEST_F(find_end_n_test, ProjectionTestBidirectional)
{
    auto range = alg::find_end_n(l, 2, 4, {}, proj);
    auto begin = std::next(std::begin(l), 4);
    auto end = std::next(std::begin(l), 6);

    EXPECT_EQ(std::begin(range), begin);
    EXPECT_EQ(std::end(range), end);

    range = alg::find_end_n(l, 3, 1, pred, proj);
    begin = std::next(std::begin(l), 4);
    end = std::next(std::begin(l), 7);

    EXPECT_EQ(std::begin(range), begin);
    EXPECT_EQ(std::end(range), end);
}
