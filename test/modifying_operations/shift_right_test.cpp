#include <vector>
#include <functional>

#include <gtest/gtest.h>

#include "modifying_operations.hpp"

#include "movable_int.hpp"

class shift_right_test : public ::testing::Test
{
protected:
    std::vector<movable_int> v{1, 2, 3};
};


TEST_F(shift_right_test, EmptyRange)
{
    auto res = alg::shift_right(std::begin(v), std::begin(v), 1);

    EXPECT_EQ(v, (std::vector{1, 2, 3}));
    EXPECT_EQ(std::begin(res), std::begin(v));
    EXPECT_EQ(std::end(res), std::begin(v));

    res = alg::shift_right(std::begin(v), std::end(v), 0);

    EXPECT_EQ(v, (std::vector{1, 2, 3}));
    EXPECT_EQ(std::begin(res), std::end(v));
    EXPECT_EQ(std::end(res), std::end(v));
}

TEST_F(shift_right_test, BasicTest)
{
    auto res = alg::shift_right(std::begin(v), std::end(v), 1);

    EXPECT_EQ(v, (std::vector{0, 1, 2}));
    EXPECT_EQ(std::begin(res), std::begin(v) + 1);
    EXPECT_EQ(std::end(res), std::end(v));
}

TEST_F(shift_right_test, RangeTest)
{
    auto res = alg::shift_right(v, 1);

    EXPECT_EQ(v, (std::vector{0, 1, 2}));
    EXPECT_EQ(std::begin(res), std::begin(v) + 1);
    EXPECT_EQ(std::end(res), std::end(v));
}
