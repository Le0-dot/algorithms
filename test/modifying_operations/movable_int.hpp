#pragma once

#include <vector>

#include "comparison_operations.hpp"

class movable_int
{
private:
    int val;

public:
    movable_int(int v) : val{v} {}

    movable_int(const movable_int& other)
    {
	if(this != &other)
	    val = other.val;
    }


    movable_int(movable_int&& other)
    {
	if(this != &other) {
	    val = other.val;
	    other.val = 0;
	}
    }

    movable_int& operator=(const movable_int& other)
    {
	if(this != &other)
	    val = other.val;
	return *this;
    }

    movable_int& operator=(movable_int&& other)
    {
	if(this != &other) {
	    val = other.val;
	    other.val = 0;
	}
	return *this;
    }

    operator int() { return val; }
};

inline constexpr bool operator==(const std::vector<movable_int>& v1, const std::vector<int>& v2)
{
    return alg::equal(v1, v2, [] (movable_int a, int b) { return a == b;});
}
