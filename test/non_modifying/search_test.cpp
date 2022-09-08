#include <vector>
#include <functional>

#include <gtest/gtest.h>

#include "non_modifying.hpp"

class search_test : public ::testing::Test
{
protected:
    const std::vector<int> v{1, 2, 3, 1, 2, 1};
    const std::vector<int> f{3, 1, 2};
    const std::function<bool(int, int)> pred = [] (int i, int j) { return i % 3 == j % 3; };
    const std::function<int(int)> proj1 = [] (int i) { return i + 1; };
    const std::function<int(int)> proj2 = [] (int i) { return i - 1; };
};

TEST_F(search_test, EmptyRange)
{
    auto range = alg::search(std::begin(v), std::begin(v), std::begin(f), std::end(f));

    EXPECT_EQ(std::begin(range), std::begin(v));
    EXPECT_EQ(std::end(range), std::begin(v));

    range = alg::search(std::begin(v), std::end(v), std::begin(f), std::begin(f));

    EXPECT_EQ(std::begin(range), std::begin(v));
    EXPECT_EQ(std::end(range), std::begin(v));
}

TEST_F(search_test, BasicTest)
{
    auto range = alg::search(std::begin(v), std::end(v), std::begin(f), std::end(f));

    EXPECT_EQ(std::begin(range), std::begin(v) + 2);
    EXPECT_EQ(std::end(range), std::begin(v) + 5);

    range = alg::search(std::begin(v), std::end(v), std::begin(f), std::end(f), pred);

    EXPECT_EQ(std::begin(range), std::begin(v) + 2);
    EXPECT_EQ(std::end(range), std::begin(v) + 5);
}

TEST_F(search_test, RangeTest)
{
    auto range = alg::search(v, f);

    EXPECT_EQ(std::begin(range), std::begin(v) + 2);
    EXPECT_EQ(std::end(range), std::begin(v) + 5);

    range = alg::search(v, f, pred);

    EXPECT_EQ(std::begin(range), std::begin(v) + 2);
    EXPECT_EQ(std::end(range), std::begin(v) + 5);
}

TEST_F(search_test, ProjectionTest)
{
    auto range = alg::search(v, f, {}, proj1, proj2);

    EXPECT_EQ(std::begin(range), std::end(v));
    EXPECT_EQ(std::end(range), std::end(v));

    range = alg::search(v, f, pred, proj1, proj2);

    EXPECT_EQ(std::begin(range), std::begin(v));
    EXPECT_EQ(std::end(range), std::begin(v) + 3);
}
