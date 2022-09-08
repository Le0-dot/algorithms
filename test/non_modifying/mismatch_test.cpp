#include <vector>
#include <functional>

#include <gtest/gtest.h>

#include "non_modifying.hpp"

class mismatch_test : public ::testing::Test
{
protected:
    const std::vector<int> v1{1, 2, 3, 4};
    const std::vector<int> v2{1, 2, 3, 1};
    const std::function<int(int)> proj1 = [] (int i) { return i + 1; };
    const std::function<int(int)> proj2 = [] (int i) { return i + 2; };
};

TEST_F(mismatch_test, EmptyRange)
{
    auto [it1, it2] = alg::mismatch(std::begin(v1), std::begin(v1), std::begin(v2), std::begin(v2));
    	
    EXPECT_EQ(it1, std::begin(v1));
    EXPECT_EQ(it2, std::begin(v2));
}

TEST_F(mismatch_test, BasicTest)
{
    {
	auto [it1, it2] = alg::mismatch(std::begin(v1), std::end(v1), std::begin(v2), std::end(v2));

	EXPECT_EQ(it1, std::begin(v1) + 3);
    	EXPECT_EQ(it2, std::begin(v2) + 3);
    }

    {
	auto [it1, it2] = alg::mismatch(std::begin(v1), std::end(v1), std::begin(v2), std::end(v2), std::ranges::less{});

	EXPECT_EQ(it1, std::begin(v1));
    	EXPECT_EQ(it2, std::begin(v2));
    }
}

TEST_F(mismatch_test, RangeTest)
{
    auto [it1, it2] = alg::mismatch(v1, v2);
    
    EXPECT_EQ(it1, std::begin(v1) + 3);
    EXPECT_EQ(it2, std::begin(v2) + 3);
}

TEST_F(mismatch_test, ProjectionTest)
{
    auto [it1, it2] = alg::mismatch(v1, v2, std::ranges::less{}, proj1, proj2);

    EXPECT_EQ(it1, std::begin(v1) + 3);
    EXPECT_EQ(it2, std::begin(v2) + 3);
}

TEST_F(mismatch_test, EmptyRangeN)
{
    auto [it1, it2] = alg::mismatch_n(std::begin(v1), std::begin(v2), 0);
   	
    EXPECT_EQ(it1, std::begin(v1));
    EXPECT_EQ(it2, std::begin(v2));
}

TEST_F(mismatch_test, BasicTestN)
{
    {
	auto [it1, it2] = alg::mismatch_n(std::begin(v1), std::begin(v2), std::size(v1));

	EXPECT_EQ(it1, std::begin(v1) + 3);
    	EXPECT_EQ(it2, std::begin(v2) + 3);
    }

    {
	auto [it1, it2] = alg::mismatch_n(std::begin(v1), std::begin(v2), std::size(v1), std::ranges::less{});

	EXPECT_EQ(it1, std::begin(v1));
    	EXPECT_EQ(it2, std::begin(v2));
    }
}

TEST_F(mismatch_test, RangeTestN)
{
    auto [it1, it2] = alg::mismatch_n(v1, v2, std::size(v1));
    
    EXPECT_EQ(it1, std::begin(v1) + 3);
    EXPECT_EQ(it2, std::begin(v2) + 3);
}

TEST_F(mismatch_test, ProjectionTestN)
{
    auto [it1, it2] = alg::mismatch_n(v1, v2, 2, std::ranges::less{}, proj1, proj2);

    EXPECT_EQ(it1, std::begin(v1) + 2);
    EXPECT_EQ(it2, std::begin(v2) + 2);
}
