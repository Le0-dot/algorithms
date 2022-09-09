#pragma once

#include <ranges>
#include <iterator>
#include <functional>
#include <compare>

#include "utility_concepts.hpp"

namespace alg
{

    //********************* equal ****************************

    template<std::input_iterator Iter1, std::sentinel_for<Iter1> Sent1,
	std::input_iterator Iter2, std::sentinel_for<Iter2> Sent2,
	typename Pred = std::ranges::equal_to,
	typename Proj1 = std::identity,
	typename Proj2 = std::identity>
    requires std::indirectly_comparable<Iter1, Iter2, Pred, Proj1, Proj2>
    [[nodiscard]] constexpr auto equal(Iter1 left1, Sent1 right1, Iter2 left2, Sent2 right2,
	    Pred f = {}, Proj1 p1 = {}, Proj2 p2 = {})
    {
	if constexpr(std::sized_sentinel_for<Sent1, Iter1> && std::sized_sentinel_for<Sent2, Iter2>)
	    if(std::ranges::distance(left1, right1) != std::ranges::distance(left2, right2))
		return false;

	for(; left1 != right1 && left2 != right2; ++left1, ++left2)
	    if(!std::invoke(f, std::invoke(p1, *left1), std::invoke(p2, *left2)))
		return false;
	return !(left1 == right1 ^ left2 == right2);
    }

    template<std::ranges::input_range Range1,
	std::ranges::input_range Range2,
	typename Pred = std::ranges::equal_to,
	typename Proj1 = std::identity,
	typename Proj2 = std::identity>
    requires std::indirectly_comparable<
	std::ranges::iterator_t<Range1>,
	std::ranges::iterator_t<Range2>,
	Pred, Proj1, Proj2>
    [[nodiscard]] constexpr auto equal(Range1&& range1, Range2&& range2,
	    Pred f = {}, Proj1 p1 = {}, Proj2 p2 = {})
    {
	return equal(std::begin(range1), std::end(range1),
		std::begin(range2), std::end(range2),
		std::move(f), std::move(p1), std::move(p2));
    }


    //********************* equal_n ****************************

    template<std::input_iterator Iter1,
	std::input_iterator Iter2,
	typename Pred = std::ranges::equal_to,
	typename Proj1 = std::identity,
	typename Proj2 = std::identity>
    requires std::indirectly_comparable<Iter1, Iter2, Pred, Proj1, Proj2>
    [[nodiscard]] constexpr auto equal_n(Iter1 left1, Iter2 left2, size_t size,
	    Pred f = {}, Proj1 p1 = {}, Proj2 p2 = {})
    {
	for(; size > 0; ++left1, ++left2, --size)
	    if(!std::invoke(f, std::invoke(p1, *left1), std::invoke(p2, *left2)))
		return false;
	return true;
    }

    template<std::ranges::input_range Range1,
	std::ranges::input_range Range2,
	typename Pred = std::ranges::equal_to,
	typename Proj1 = std::identity,
	typename Proj2 = std::identity>
    requires std::indirectly_comparable<
	std::ranges::iterator_t<Range1>,
	std::ranges::iterator_t<Range2>,
	Pred, Proj1, Proj2>
    [[nodiscard]] constexpr auto equal_n(Range1&& range1, Range2&& range2, size_t size,
	    Pred f = {}, Proj1 p1 = {}, Proj2 p2 = {})
    {
	return equal_n(std::begin(range1), std::begin(range2), size,
		std::move(f), std::move(p1), std::move(p2));
    }


    //************* lexicographical_compare ******************

    template<std::input_iterator Iter1, std::sentinel_for<Iter1> Sent1,
	std::input_iterator Iter2, std::sentinel_for<Iter2> Sent2,
	typename Proj1 = std::identity,
	typename Proj2 = std::identity,
	std::indirect_strict_weak_order<
	    std::projected<Iter1, Proj1>,
	    std::projected<Iter2, Proj2>> Comp = std::ranges::less>
    [[nodiscard]] constexpr auto lexicographical_compare(Iter1 left1, Sent1 right1, Iter2 left2, Sent2 right2,
	    Comp f = {}, Proj1 p1 = {}, Proj2 p2 = {})
    {
	for(; (left1 != right1) && (left2 != right2); ++left1, ++left2) {
	    if(std::invoke(f, std::invoke(p1, *left1), std::invoke(p2, *left2)))
		    return true;
	    if(std::invoke(f, std::invoke(p2, *left2), std::invoke(p1, *left1)))
		    return false;
	}

	return (left1 == right1) && (left2 != right2);
    }

    template<std::ranges::input_range Range1,
	std::ranges::input_range Range2,
	typename Proj1 = std::identity,
	typename Proj2 = std::identity,
	std::indirect_strict_weak_order<
	    std::projected<std::ranges::iterator_t<Range1>, Proj1>,
	    std::projected<std::ranges::iterator_t<Range2>, Proj2>> Comp = std::ranges::less>
    [[nodiscard]] constexpr auto lexicographical_compare(Range1 range1, Range2 range2,
	    Comp f = {}, Proj1 p1 = {}, Proj2 p2 = {})
    {
	return lexicographical_compare(std::begin(range1), std::end(range1),
		std::begin(range2), std::end(range2),
		std::move(f), std::move(p1), std::move(p2));
    }


    //************* lexicographical_compare_n ******************

    template<std::input_iterator Iter1,
	std::input_iterator Iter2,
	typename Proj1 = std::identity,
	typename Proj2 = std::identity,
	std::indirect_strict_weak_order<
	    std::projected<Iter1, Proj1>,
	    std::projected<Iter2, Proj2>> Comp = std::ranges::less>
    [[nodiscard]] constexpr auto lexicographical_compare_n(Iter1 left1, Iter2 left2, size_t size,
	    Comp f = {}, Proj1 p1 = {}, Proj2 p2 = {})
    {
	for(; size > 0; ++left1, ++left2, --size) {
	    if(std::invoke(f, std::invoke(p1, *left1), std::invoke(p2, *left2)))
		    return true;
	    if(std::invoke(f, std::invoke(p2, *left2), std::invoke(p1, *left1)))
		    return false;
	}

	return false;
    }

    template<std::ranges::input_range Range1,
	std::ranges::input_range Range2,
	typename Proj1 = std::identity,
	typename Proj2 = std::identity,
	std::indirect_strict_weak_order<
	    std::projected<std::ranges::iterator_t<Range1>, Proj1>,
	    std::projected<std::ranges::iterator_t<Range2>, Proj2>> Comp = std::ranges::less>
    [[nodiscard]] constexpr auto lexicographical_compare_n(Range1 range1, Range2 range2, size_t size,
	    Comp f = {}, Proj1 p1 = {}, Proj2 p2 = {})
    {
	return lexicographical_compare_n(std::begin(range1), std::begin(range2),
		size, std::move(f), std::move(p1), std::move(p2));
    }


    //******** lexicographical_compare_three_way *************

    template<std::input_iterator Iter1, std::sentinel_for<Iter1> Sent1,
	std::input_iterator Iter2, std::sentinel_for<Iter2> Sent2,
	typename Comp = std::compare_three_way,
	typename Proj1 = std::identity,
	typename Proj2 = std::identity>
    requires concepts::indirectly_comparable_three_way<Iter1, Iter2, Comp, Proj1, Proj2>
    [[nodiscard]] constexpr auto lexicographical_compare_three_way(Iter1 left1, Sent1 right1, Iter2 left2, Sent2 right2,
	    Comp f = {}, Proj1 p1 = {}, Proj2 p2 = {})
    {
	for(; (left1 != right1) && (left2 != right2); ++left1, ++left2)
	    if(auto c = std::invoke(f, std::invoke(p1, *left1), std::invoke(p2, *left2)); c != 0)
		return c;

	return (left1 != right1) ? std::strong_ordering::greater :
	       (left2 != right2) ? std::strong_ordering::less :
				   std::strong_ordering::equal;
    }

    template<std::ranges::input_range Range1,
	std::ranges::input_range Range2,
	typename Comp = std::compare_three_way,
	typename Proj1 = std::identity,
	typename Proj2 = std::identity>
    requires concepts::indirectly_comparable_three_way<std::ranges::iterator_t<Range1>,
	std::ranges::iterator_t<Range2>,
	Comp, Proj1, Proj2>
    [[nodiscard]] constexpr auto lexicographical_compare_three_way(Range1 range1, Range2 range2,
	    Comp f = {}, Proj1 p1 = {}, Proj2 p2 = {})
    {
	return lexicographical_compare_three_way(std::begin(range1), std::end(range1),
		std::begin(range2), std::end(range2),
		std::move(f), std::move(p1), std::move(p2));
    }


    //******** lexicographical_compare_three_way_n *************

    template<std::input_iterator Iter1,
	std::input_iterator Iter2,
	typename Comp = std::compare_three_way,
	typename Proj1 = std::identity,
	typename Proj2 = std::identity>
    requires concepts::indirectly_comparable_three_way<Iter1, Iter2, Comp, Proj1, Proj2>
    [[nodiscard]] constexpr auto lexicographical_compare_three_way_n(Iter1 left1, Iter2 left2, size_t size,
	    Comp f = {}, Proj1 p1 = {}, Proj2 p2 = {})
    {
	for(; size > 0; ++left1, ++left2, --size)
	    if(auto c = std::invoke(f, std::invoke(p1, *left1), std::invoke(p2, *left2)); c != 0)
		return c;

	return std::strong_ordering::equal;
    }

    template<std::ranges::input_range Range1,
	std::ranges::input_range Range2,
	typename Comp = std::compare_three_way,
	typename Proj1 = std::identity,
	typename Proj2 = std::identity>
    requires concepts::indirectly_comparable_three_way<std::ranges::iterator_t<Range1>,
	std::ranges::iterator_t<Range2>,
	Comp, Proj1, Proj2>
    [[nodiscard]] constexpr auto lexicographical_compare_three_way_n(Range1 range1, Range2 range2, size_t size,
	    Comp f = {}, Proj1 p1 = {}, Proj2 p2 = {})
    {
	return lexicographical_compare_three_way_n(std::begin(range1), std::begin(range2), size,
		std::move(f), std::move(p1), std::move(p2));
    }


}
