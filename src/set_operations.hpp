#pragma once

#include <ranges>
#include <functional>
#include <iterator>
#include <algorithm>

#include "modifying_operations.hpp"

namespace alg
{

    //****************** includes *********************

    template<std::input_iterator Iter1, std::sentinel_for<Iter1> Sent1,
	std::input_iterator Iter2, std::sentinel_for<Iter2> Sent2,
	typename Proj1 = std::identity, typename Proj2 = std::identity,
	std::indirect_strict_weak_order<
	    std::projected<Iter1, Proj1>,
	    std::projected<Iter2, Proj2>> Comp = std::ranges::less>
    [[nodiscard]] constexpr auto includes(Iter1 left1, Sent1 right1, Iter2 left2, Sent2 right2,
	    Comp f = {}, Proj1 p1 = {}, Proj2 p2 = {})
    {
	for (; left2 != right2; ++left1) {
	    if (left1 == right1 || std::invoke(f, std::invoke(p2, *left2), std::invoke(p1, *left1)))
		return false;
	    if (!std::invoke(f, std::invoke(p1, *left1), std::invoke(p2, *left2)))
		++left2;
	}
	return true;
    }

    template<std::ranges::input_range Range1,
	std::ranges::input_range Range2,
	typename Proj1 = std::identity, typename Proj2 = std::identity,
	std::indirect_strict_weak_order<
	    std::projected<std::ranges::iterator_t<Range1>, Proj1>,
	    std::projected<std::ranges::iterator_t<Range2>, Proj2>> Comp = std::ranges::less>
    [[nodiscard]] constexpr auto includes(Range1&& range1, Range2&& range2,
	    Comp f = {}, Proj1 p1 = {}, Proj2 p2 = {}) -> bool
    {
	return ::alg::includes(std::begin(range1), std::end(range1),
		std::begin(range2), std::end(range2),
		std::move(f), std::move(p1), std::move(p2));
    }


    //**************** set_diffrence *******************
    
    template<std::input_iterator Iter1, std::sentinel_for<Iter1> Sent1,
	std::input_iterator Iter2, std::sentinel_for<Iter2> Sent2,
	std::weakly_incrementable Out, typename Comp = std::ranges::less,
	typename Proj1 = std::identity, typename Proj2 = std::identity>
    requires std::mergeable<Iter1, Iter2, Out, Comp, Proj1, Proj2>
    constexpr auto set_difference(Iter1 left1, Sent1 right1, Iter2 left2, Sent2 right2,
	Out out, Comp f = {}, Proj1 p1 = {}, Proj2 p2 = {}) -> std::ranges::in_out_result<Iter1, Out>
    {
	while(left1 != right1 && left2 != right2) {
	    if(std::invoke(f, std::invoke(p1, *left1), std::invoke(p2, *left2)))
		*out++ = *left1++;
	    else if(std::invoke(f, std::invoke(p2, *left2), std::invoke(p1, *left1)))
		++left2;
	    else
		++left1, ++left2;
	}
	return ::alg::copy(std::move(left1), std::move(right1), std::move(out));
    }


    template<std::ranges::input_range Range1,
	std::ranges::input_range Range2,
	std::weakly_incrementable Out, typename Comp = std::ranges::less,
	typename Proj1 = std::identity, typename Proj2 = std::identity>
    requires std::mergeable<
	std::ranges::iterator_t<Range1>,
	std::ranges::iterator_t<Range2>,
	Out, Comp, Proj1, Proj2>
    constexpr auto set_difference(Range1&& range1, Range2&& range2,
	Out out, Comp f = {}, Proj1 p1 = {}, Proj2 p2 = {}) -> std::ranges::in_out_result<std::ranges::borrowed_iterator_t<Range1>, Out>
    {
	return ::alg::set_difference(std::begin(range1), std::end(range1), std::begin(range2), std::end(range2),
	    std::move(out), std::move(f), std::move(p1), std::move(p2));
    }


    //************* set_intersection ********************
    
    template<std::input_iterator Iter1, std::sentinel_for<Iter1> Sent1,
	std::input_iterator Iter2, std::sentinel_for<Iter2> Sent2,
	std::weakly_incrementable Out, typename Comp = std::ranges::less,
	typename Proj1 = std::identity, typename Proj2 = std::identity>
    requires std::mergeable<Iter1, Iter2, Out, Comp, Proj1, Proj2>
    constexpr auto set_intersection(Iter1 left1, Sent1 right1, Iter2 left2, Sent2 right2,
	Out out, Comp f = {}, Proj1 p1 = {}, Proj2 p2 = {}) -> std::ranges::in_in_out_result<Iter1, Iter2, Out>
    {
	while(left1 != right1 && left2 != right2) {
	    if(std::invoke(f, std::invoke(p1, *left1), std::invoke(p2, *left2)))
		++left1;
	    else if(std::invoke(f, std::invoke(p2, *left2), std::invoke(p1, *left1)))
		++left2;
	    else {
		*out++ = *left1++;
		++left2;
	    }
	}
	return {std::ranges::next(std::move(left1), std::move(right1)),
		std::ranges::next(std::move(left2), std::move(right2)),
		std::move(out)};
    }

    template<std::ranges::input_range Range1,
	std::ranges::input_range Range2,
	std::weakly_incrementable Out, typename Comp = std::ranges::less,
	typename Proj1 = std::identity, typename Proj2 = std::identity>
    requires std::mergeable<
	std::ranges::iterator_t<Range1>,
	std::ranges::iterator_t<Range2>,
	Out, Comp, Proj1, Proj2>
    constexpr auto set_intersection(Range1&& range1, Range2&& range2,
	Out out, Comp f = {}, Proj1 p1 = {}, Proj2 p2 = {}) -> std::ranges::in_in_out_result<
	    std::ranges::borrowed_iterator_t<Range1>, 
	    std::ranges::borrowed_iterator_t<Range2>, 
	    Out>
    {
	return ::alg::set_intersection(std::begin(range1), std::end(range1), std::begin(range2), std::end(range2),
	    std::move(out), std::move(f), std::move(p1), std::move(p2));
    }


    //****************** set_union *********************
    
    template<std::input_iterator Iter1, std::sentinel_for<Iter1> Sent1,
	std::input_iterator Iter2, std::sentinel_for<Iter2> Sent2,
	std::weakly_incrementable Out, typename Comp = std::ranges::less,
	typename Proj1 = std::identity, typename Proj2 = std::identity>
    requires std::mergeable<Iter1, Iter2, Out, Comp, Proj1, Proj2>
    constexpr auto set_union(Iter1 left1, Sent1 right1, Iter2 left2, Sent2 right2,
	Out out, Comp f = {}, Proj1 p1 = {}, Proj2 p2 = {}) -> std::ranges::in_in_out_result<Iter1, Iter2, Out>
    {
	while(left1 != right1 && left2 != right2) {
	    if(std::invoke(f, std::invoke(p1, *left1), std::invoke(p2, *left2)))
		*out++ = *left1++;
	    else if(std::invoke(f, std::invoke(p2, *left2), std::invoke(p1, *left1)))
		*out++ = *left2++;
	    else {
		*out++ = *left1++;
		++left2;
	    }
	}
	auto res1 = ::alg::copy(std::move(left1), std::move(right1), std::move(out));
	auto res2 = ::alg::copy(std::move(left2), std::move(right2), std::move(res1.out));
	return {std::move(res1.in), std::move(res2.in), std::move(res2.out)};
    }

    template<std::ranges::input_range Range1,
	std::ranges::input_range Range2,
	std::weakly_incrementable Out, typename Comp = std::ranges::less,
	typename Proj1 = std::identity, typename Proj2 = std::identity>
    requires std::mergeable<
	std::ranges::iterator_t<Range1>,
	std::ranges::iterator_t<Range2>,
	Out, Comp, Proj1, Proj2>
    constexpr auto set_union(Range1&& range1, Range2&& range2,
	Out out, Comp f = {}, Proj1 p1 = {}, Proj2 p2 = {}) -> std::ranges::in_in_out_result<
	    std::ranges::borrowed_iterator_t<Range1>, 
	    std::ranges::borrowed_iterator_t<Range2>, 
	    Out>
    {
	return ::alg::set_union(std::begin(range1), std::end(range1), std::begin(range2), std::end(range2),
	    std::move(out), std::move(f), std::move(p1), std::move(p2));
    }


    //************** set_symmetric_difference *******************
    
    template<std::input_iterator Iter1, std::sentinel_for<Iter1> Sent1,
	std::input_iterator Iter2, std::sentinel_for<Iter2> Sent2,
	std::weakly_incrementable Out, typename Comp = std::ranges::less,
	typename Proj1 = std::identity, typename Proj2 = std::identity>
    requires std::mergeable<Iter1, Iter2, Out, Comp, Proj1, Proj2>
    constexpr auto set_symmetric_difference(Iter1 left1, Sent1 right1, Iter2 left2, Sent2 right2,
	Out out, Comp f = {}, Proj1 p1 = {}, Proj2 p2 = {}) -> std::ranges::in_in_out_result<Iter1, Iter2, Out>
    {
	while(left1 != right1 && left2 != right2) {
	    if(std::invoke(f, std::invoke(p1, *left1), std::invoke(p2, *left2)))
		*out++ = *left1++;
	    else if(std::invoke(f, std::invoke(p2, *left2), std::invoke(p1, *left1)))
		*out++ = *left2++;
	    else {
		++left1;
		++left2;
	    }
	}
	auto res1 = ::alg::copy(std::move(left1), std::move(right1), std::move(out));
	auto res2 = ::alg::copy(std::move(left2), std::move(right2), std::move(res1.out));
	return {std::move(res1.in), std::move(res2.in), std::move(res2.out)};
    }

    template<std::ranges::input_range Range1,
	std::ranges::input_range Range2,
	std::weakly_incrementable Out, typename Comp = std::ranges::less,
	typename Proj1 = std::identity, typename Proj2 = std::identity>
    requires std::mergeable<
	std::ranges::iterator_t<Range1>,
	std::ranges::iterator_t<Range2>,
	Out, Comp, Proj1, Proj2>
    constexpr auto set_symmetric_difference(Range1&& range1, Range2&& range2,
	Out out, Comp f = {}, Proj1 p1 = {}, Proj2 p2 = {}) -> std::ranges::in_in_out_result<
	    std::ranges::borrowed_iterator_t<Range1>, 
	    std::ranges::borrowed_iterator_t<Range2>, 
	    Out>
    {
	return ::alg::set_symmetric_difference(std::begin(range1), std::end(range1), std::begin(range2), std::end(range2),
	    std::move(out), std::move(f), std::move(p1), std::move(p2));
    }


}
