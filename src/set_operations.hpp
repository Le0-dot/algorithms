#pragma once

#include <ranges>
#include <functional>
#include <iterator>

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


}
