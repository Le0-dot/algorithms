#pragma once

#include <ranges>
#include <iterator>
#include <functional>


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
	return equal(std::ranges::begin(range1), std::ranges::end(range1),
		std::ranges::begin(range2), std::ranges::end(range2),
		std::move(f), std::move(p1), std::move(p2));
    }


    //********************* equal_n ****************************

    template<std::input_iterator Iter1,
	std::input_iterator Iter2,
	typename Pred = std::ranges::equal_to,
	typename Proj1 = std::identity,
	typename Proj2 = std::identity>
    requires std::indirectly_comparable<Iter1, Iter2, Pred, Proj1, Proj2>
    [[nodiscard]] constexpr auto equal_n(Iter1 left1, size_t size1, Iter2 left2, size_t size2,
	    Pred f = {}, Proj1 p1 = {}, Proj2 p2 = {})
    {
	if(size1 != size2)
	    return false;

	for(; size1 > 0; ++left1, ++left2, --size1)
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
    [[nodiscard]] constexpr auto equal_n(Range1&& range1, size_t size1, Range2&& range2, size_t size2,
	    Pred f = {}, Proj1 p1 = {}, Proj2 p2 = {})
    {
	return equal_n(std::ranges::begin(range1), size1,
		std::ranges::begin(range2), size2,
		std::move(f), std::move(p1), std::move(p2));
    }


    //************* lexicographical_compare ******************



    //******** lexicographical_compare_three_way *************
    


}
