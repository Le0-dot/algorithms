#include <vector>
#include <functional>

#include <gtest/gtest.h>

#include "non_modifying_operations.hpp"

class search_n_test : public ::testing::Test
{
protected:
    const std::vector<int> v{1, 2, 3, 3, 3, 1};
    const std::function<bool(int, int)> pred = [] (int i, int j) { return i % 3 == j % 3; };
    int counter = 0;
    const std::function<int(int)> proj = [this] (int i) { return i + (counter++ % 2); };
};

TEST_F(search_n_test, EmptyRange)
{
    auto range = alg::search_n(std::begin(v), std::begin(v), 3, 3);

    EXPECT_EQ(std::begin(range), std::begin(v));
    EXPECT_EQ(std::end(range), std::begin(v));

    range = alg::search_n(std::begin(v), std::end(v), 0, 3);

    EXPECT_EQ(std::begin(range), std::begin(v));
    EXPECT_EQ(std::end(range), std::begin(v));
}

TEST_F(search_n_test, BasicTest)
{
    auto range = alg::search_n(std::begin(v), std::end(v), 3, 3);

    EXPECT_EQ(std::begin(range), std::begin(v) + 2);
    EXPECT_EQ(std::end(range), std::begin(v) + 5);

    range = alg::search_n(std::begin(v), std::end(v), 3, 3, pred);

    EXPECT_EQ(std::begin(range), std::begin(v) + 2);
    EXPECT_EQ(std::end(range), std::begin(v) + 5);
    
    range = alg::search_n(std::begin(v), std::end(v), 3, 5, pred);

    EXPECT_EQ(std::begin(range), std::end(v));
    EXPECT_EQ(std::end(range), std::end(v));
}

TEST_F(search_n_test, RangeTest)
{
    auto range = alg::search_n(v, 3, 3);

    EXPECT_EQ(std::begin(range), std::begin(v) + 2);
    EXPECT_EQ(std::end(range), std::begin(v) + 5);

    range = alg::search_n(v, 3, 3, pred);

    EXPECT_EQ(std::begin(range), std::begin(v) + 2);
    EXPECT_EQ(std::end(range), std::begin(v) + 5);
    
    range = alg::search_n(v, 3, 5, pred);

    EXPECT_EQ(std::begin(range), std::end(v));
    EXPECT_EQ(std::end(range), std::end(v));
}

TEST_F(search_n_test, ProjectionTest)
{
    auto range = alg::search_n(v, 2, 3, {}, proj);

    EXPECT_EQ(std::begin(range), std::begin(v) + 1);
    EXPECT_EQ(std::end(range), std::begin(v) + 3);

    range = alg::search_n(v, 2, 1, pred, proj);

    EXPECT_EQ(std::begin(range), std::begin(v) + 4);
    EXPECT_EQ(std::end(range), std::begin(v) + 6);
}
