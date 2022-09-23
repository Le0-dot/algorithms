#pragma once

#include <functional>
#include <ranges>
#include <iterator>

#include "comparison_operations.hpp"

namespace alg
{

    //****************** for_each *********************

    template<std::input_iterator Iter1,
	std::sentinel_for<Iter1> Iter2,
	typename Proj = std::identity,
	std::indirectly_unary_invocable<std::projected<Iter1, Proj>> UnaryOp>
    constexpr auto for_each(Iter1 left, Iter2 right, UnaryOp f, Proj p = {}) -> void
    {
        for(; left != right; ++left)
	    std::invoke(f, std::invoke(p, *left));
    }

    template<std::ranges::input_range Range,
	typename Proj = std::identity,
	std::indirectly_unary_invocable<std::projected<std::ranges::iterator_t<Range>, Proj>> UnaryOp>
    auto for_each(Range&& range, UnaryOp f, Proj p = {}) -> void
    {
	for_each(std::begin(range), std::end(range), std::move(f), std::move(p));
    }


    //***************** for_each_n ********************

    template<std::input_iterator Iter1,
	typename Proj = std::identity,
	std::indirectly_unary_invocable<std::projected<Iter1, Proj>> UnaryOp>
    auto for_each_n(Iter1 left, size_t size, UnaryOp f, Proj p = {}) -> void
    {
        for(; size > 0; ++left, --size)
	    std::invoke(f, std::invoke(p, *left));
    }

    template<std::ranges::input_range Range,
	typename Proj = std::identity,
	std::indirectly_unary_invocable<std::projected<std::ranges::iterator_t<Range>, Proj>> UnaryOp>
    auto for_each_n(Range&& range, size_t size, UnaryOp f, Proj p = {}) -> void
    {
	for_each_n(std::begin(range), size, std::move(f), std::move(p));
    }

    //******************* count ***********************

    template<std::input_iterator Iter1,
	std::sentinel_for<Iter1> Iter2,
	typename T,
	typename Proj = std::identity>
    requires std::indirect_binary_predicate<std::ranges::equal_to,
	std::projected<Iter1, Proj>,
	const T*>
    [[nodiscard]] constexpr auto count(Iter1 left, Iter2 right, const T& value, Proj p = {})
    {
	typename std::iterator_traits<Iter1>::difference_type counter = 0;
	for(; left != right; ++left)
	    if(std::invoke(p, *left) == value)
		++counter;
	return counter;
    }

    template<std::ranges::input_range Range,
	typename T,
	typename Proj = std::identity>
    requires std::indirect_binary_predicate<std::ranges::equal_to,
	std::projected<std::ranges::iterator_t<Range>, Proj>,
	const T*>
    [[nodiscard]] constexpr auto count(Range&& range, const T& value, Proj p = {})
    {
	return count(std::begin(range), std::end(range), std::move(value), std::move(p));
    }

    //****************** count_n **********************

    template<std::input_iterator Iter1,
	typename T,
	typename Proj = std::identity>
    requires std::indirect_binary_predicate<std::ranges::equal_to,
	std::projected<Iter1, Proj>,
	const T*>
    [[nodiscard]] constexpr auto count_n(Iter1 left, size_t size, const T& value, Proj p = {})
    {
	typename std::iterator_traits<Iter1>::difference_type counter = 0;
	for(; size > 0; ++left, --size)
	    if(std::invoke(p, *left) == value)
		++counter;
	return counter;
    }

    template<std::ranges::input_range Range,
	typename T,
	typename Proj = std::identity>
    requires std::indirect_binary_predicate<std::ranges::equal_to,
	std::projected<std::ranges::iterator_t<Range>, Proj>,
	const T*>
    [[nodiscard]] constexpr auto count_n(Range&& range, size_t size, const T& value, Proj p = {}) 
    {
	return count_n(std::begin(range), size, std::move(value), std::move(p));
    }


    //****************** count_if *********************

    template<std::input_iterator Iter1,
	std::sentinel_for<Iter1> Iter2,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<Iter1, Proj>> Pred>
    [[nodiscard]] constexpr auto count_if(Iter1 left, Iter2 right, Pred f, Proj p = {})
    {
	typename std::iterator_traits<Iter1>::difference_type counter = 0;
	for(; left != right; ++left)
	    if(std::invoke(f, std::invoke(p, *left)))
		++counter;
	return counter;
    }

    template<std::ranges::input_range Range,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<std::ranges::iterator_t<Range>, Proj>> Pred>
    [[nodiscard]] constexpr auto count_if(Range&& range, Pred f, Proj p = {})
    {
	return count_if(std::begin(range), std::end(range), std::move(f), std::move(p));
    }

    
    //***************** count_if_n ********************

    template<std::input_iterator Iter1,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<Iter1, Proj>> Pred>
    [[nodiscard]] constexpr auto count_if_n(Iter1 left, size_t size, Pred f, Proj p = {})
    {
	typename std::iterator_traits<Iter1>::difference_type counter = 0;
	for(; size > 0; ++left, --size)
	    if(std::invoke(f, std::invoke(p, *left)))
		++counter;
	return counter;
    }

    template<std::ranges::input_range Range,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<std::ranges::iterator_t<Range>, Proj>> Pred>
    [[nodiscard]] constexpr auto count_if_n(Range&& range, size_t size, Pred f, Proj p = {})
    {
	return count_if_n(std::begin(range), size, std::move(f), std::move(p));
    }

    //****************** mismatch *********************

    template<std::input_iterator Iter1, std::sentinel_for<Iter1> Sent1,
	std::input_iterator Iter2, std::sentinel_for<Iter2> Sent2,
	typename Pred = std::ranges::equal_to,
	typename Proj1 = std::identity, typename Proj2 = std::identity>
    requires std::indirectly_comparable<Iter1, Iter2, Pred, Proj1, Proj2>
    [[nodiscard]] constexpr auto mismatch(Iter1 left1, Sent1 right1, Iter2 left2, Sent2 right2,
	    Pred p = {}, Proj1 proj1 = {}, Proj2 proj2 = {}) 
	    -> std::ranges::in_in_result<Iter1, Iter2>
    {
	for(; left1 != right1 && left2 != right2; ++left1, ++left2)
	    if(!std::invoke(p, std::invoke(proj1, *left1), std::invoke(proj2, *left2)))
		break;
	return {left1, left2};
    }

    template<std::ranges::input_range Range1,
	std::ranges::input_range Range2,
	typename Pred = std::ranges::equal_to,
	typename Proj1 = std::identity, typename Proj2 = std::identity>
    requires std::indirectly_comparable<
	std::ranges::iterator_t<Range1>, std::ranges::iterator_t<Range2>,
	Pred, Proj1, Proj2>
    [[nodiscard]] constexpr auto mismatch(Range1&& range1, Range2&& range2,
	    Pred p = {}, Proj1 proj1 = {}, Proj2 proj2 = {}) 
	    -> std::ranges::in_in_result<
		std::ranges::borrowed_iterator_t<Range1>,
		std::ranges::borrowed_iterator_t<Range2>>
    {
	return mismatch(std::begin(range1), std::end(range1),
		std::begin(range2), std::end(range2),
		std::move(p), std::move(proj1), std::move(proj2));
    }

    //****************** mismatch_n *********************

    template<std::input_iterator Iter1,
	std::input_iterator Iter2,
	typename Pred = std::ranges::equal_to,
	typename Proj1 = std::identity, typename Proj2 = std::identity>
    requires std::indirectly_comparable<Iter1, Iter2, Pred, Proj1, Proj2>
    [[nodiscard]] constexpr auto mismatch_n(Iter1 left1, Iter2 left2, size_t size,
	    Pred p = {}, Proj1 proj1 = {}, Proj2 proj2 = {}) 
	    -> std::ranges::in_in_result<Iter1, Iter2>
    {
	for(; size > 0; ++left1, ++left2, --size)
	    if(!std::invoke(p, std::invoke(proj1, *left1), std::invoke(proj2, *left2)))
		break;
	return {left1, left2};
    }

    template<std::ranges::input_range Range1,
	std::ranges::input_range Range2,
	typename Pred = std::ranges::equal_to,
	typename Proj1 = std::identity, typename Proj2 = std::identity>
    requires std::indirectly_comparable<
	std::ranges::iterator_t<Range1>, std::ranges::iterator_t<Range2>,
	Pred, Proj1, Proj2>
    [[nodiscard]] constexpr auto mismatch_n(Range1&& range1, Range2&& range2, size_t size,
	    Pred p = {}, Proj1 proj1 = {}, Proj2 proj2 = {}) 
	    -> std::ranges::in_in_result<
		std::ranges::borrowed_iterator_t<Range1>,
		std::ranges::borrowed_iterator_t<Range2>>
    {
	return mismatch_n(std::begin(range1), std::begin(range2), size,
		std::move(p), std::move(proj1), std::move(proj2));
    }


    //******************** find ***********************

    template<std::input_iterator Iter1,
	std::sentinel_for<Iter1> Iter2,
	typename T,
	typename Proj = std::identity>
    requires std::indirect_binary_predicate<
	std::ranges::equal_to,
	std::projected<Iter1, Proj>,
	const T*>
    [[nodiscard]] constexpr auto find(Iter1 left, Iter2 right, const T& value, Proj p = {})
    {
	for(; left != right; ++left)
	    if(std::invoke(p, *left) == value)
		break;
	return left;
    }

    template<std::ranges::input_range Range,
	typename T,
	typename Proj = std::identity>
    requires std::indirect_binary_predicate<
	std::ranges::equal_to,
	std::projected<std::ranges::iterator_t<Range>, Proj>,
	const T*>
    [[nodiscard]] constexpr auto find(Range&& range, const T& value, Proj p = {})
	-> std::ranges::borrowed_iterator_t<Range>
    {
	return find(std::begin(range), std::end(range),
		value, std::move(p));
    }


    //******************* find_n **********************

    template<std::input_iterator Iter1,
	typename T,
	typename Proj = std::identity>
    requires std::indirect_binary_predicate<
	std::ranges::equal_to,
	std::projected<Iter1, Proj>,
	const T*>
    [[nodiscard]] constexpr auto find_n(Iter1 left, size_t size, const T& value, Proj p = {})
    {
	for(; size > 0; ++left, --size)
	    if(std::invoke(p, *left) == value)
		break;
	return left;
    }

    template<std::ranges::input_range Range,
	typename T,
	typename Proj = std::identity>
    requires std::indirect_binary_predicate<
	std::ranges::equal_to,
	std::projected<std::ranges::iterator_t<Range>, Proj>,
	const T*>
    [[nodiscard]] constexpr auto find_n(Range&& range, size_t size, const T& value, Proj p = {})
	-> std::ranges::borrowed_iterator_t<Range>
    {
	return find_n(std::begin(range), size, value, std::move(p));
    }


    //******************* find_if **********************
    
    template<std::input_iterator Iter1,
	std::sentinel_for<Iter1> Iter2,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<Iter1, Proj>> Pred>
    [[nodiscard]] constexpr auto find_if(Iter1 left, Iter2 right, Pred f, Proj p = {})
    {
	for(; left != right; ++left)
	    if(std::invoke(f, std::invoke(p, *left)))
		break;
	return left;
    }

    template<std::ranges::input_range Range,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<std::ranges::iterator_t<Range>, Proj>> Pred>
    [[nodiscard]] constexpr auto find_if(Range&& range, Pred f, Proj p = {})
	-> std::ranges::borrowed_iterator_t<Range>
    {
	return find_if(std::begin(range), std::end(range),
		std::move(f), std::move(p));
    }

    
    //****************** find_if_n *********************
    
    template<std::input_iterator Iter1,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<Iter1, Proj>> Pred>
    [[nodiscard]] constexpr auto find_if_n(Iter1 left, size_t size, Pred f, Proj p = {})
    {
	for(; size > 0; ++left, --size)
	    if(std::invoke(f, std::invoke(p, *left)))
		break;
	return left;
    }

    template<std::ranges::input_range Range,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<std::ranges::iterator_t<Range>, Proj>> Pred>
    [[nodiscard]] constexpr auto find_if_n(Range&& range, size_t size, Pred f, Proj p = {})
	-> std::ranges::borrowed_iterator_t<Range>
    {
	return find_if_n(std::begin(range), size, std::move(f), std::move(p));
    }


    //******************* find_if_not **********************
    
    template<std::input_iterator Iter1,
	std::sentinel_for<Iter1> Iter2,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<Iter1, Proj>> Pred>
    [[nodiscard]] constexpr auto find_if_not(Iter1 left, Iter2 right, Pred f, Proj p = {})
    {
	for(; left != right; ++left)
	    if(!std::invoke(f, std::invoke(p, *left)))
		break;
	return left;
    }

    template<std::ranges::input_range Range,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<std::ranges::iterator_t<Range>, Proj>> Pred>
    [[nodiscard]] constexpr auto find_if_not(Range&& range, Pred f, Proj p = {})
	-> std::ranges::borrowed_iterator_t<Range>
    {
	return find_if_not(std::begin(range), std::end(range),
		std::move(f), std::move(p));
    }

    
    //****************** find_if_not_n *********************
    
    template<std::input_iterator Iter1,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<Iter1, Proj>> Pred>
    [[nodiscard]] constexpr auto find_if_not_n(Iter1 left, size_t size, Pred f, Proj p = {})
    {
	for(; size > 0; ++left, --size)
	    if(!std::invoke(f, std::invoke(p, *left)))
		break;
	return left;
    }

    template<std::ranges::input_range Range,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<std::ranges::iterator_t<Range>, Proj>> Pred>
    [[nodiscard]] constexpr auto find_if_not_n(Range&& range, size_t size, Pred f, Proj p = {})
	-> std::ranges::borrowed_iterator_t<Range>
    {
	return find_if_not_n(std::begin(range), size, std::move(f), std::move(p));
    }


    //********************* all_of **************************

    template<std::input_iterator Iter1,
	std::sentinel_for<Iter1> Iter2,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<Iter1, Proj>> Pred>
    [[nodiscard]] constexpr auto all_of(Iter1 left, Iter2 right, Pred f, Proj p = {}) -> bool
    {
	return find_if_not(left, right, std::move(f), std::move(p)) == right;
    }

    template<std::ranges::input_range Range,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<std::ranges::iterator_t<Range>, Proj>> Pred>
    [[nodiscard]] constexpr auto all_of(Range&& range, Pred f, Proj p = {}) -> bool
    {
	return all_of(std::begin(range), std::end(range),
		std::move(f), std::move(p));
    }

    
    //********************* all_of_n **************************

    template<std::input_iterator Iter1,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<Iter1, Proj>> Pred>
    [[nodiscard]] constexpr auto all_of_n(Iter1 left, size_t size, Pred f, Proj p = {}) -> bool
    {
	return find_if_not_n(left, size, std::move(f), std::move(p)) == left + size;
    }

    template<std::ranges::input_range Range,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<std::ranges::iterator_t<Range>, Proj>> Pred>
    [[nodiscard]] constexpr auto all_of_n(Range&& range, size_t size, Pred f, Proj p = {}) -> bool
    {
	return all_of_n(std::begin(range), size, std::move(f), std::move(p));
    }


    //********************* any_of **************************

    template<std::input_iterator Iter1,
	std::sentinel_for<Iter1> Iter2,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<Iter1, Proj>> Pred>
    [[nodiscard]] constexpr auto any_of(Iter1 left, Iter2 right, Pred f, Proj p = {}) -> bool
    {
	return find_if(left, right, std::move(f), std::move(p)) != right;
    }

    template<std::ranges::input_range Range,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<std::ranges::iterator_t<Range>, Proj>> Pred>
    [[nodiscard]] constexpr auto any_of(Range&& range, Pred f, Proj p = {}) -> bool
    {
	return any_of(std::begin(range), std::end(range),
		std::move(f), std::move(p));
    }

    
    //******************** any_of_n *************************

    template<std::input_iterator Iter1,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<Iter1, Proj>> Pred>
    [[nodiscard]] constexpr auto any_of_n(Iter1 left, size_t size, Pred f, Proj p = {}) -> bool
    {
	return find_if_n(left, size, std::move(f), std::move(p)) != left + size;
    }

    template<std::ranges::input_range Range,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<std::ranges::iterator_t<Range>, Proj>> Pred>
    [[nodiscard]] constexpr auto any_of_n(Range&& range, size_t size, Pred f, Proj p = {}) -> bool
    {
	return any_of_n(std::begin(range), size, std::move(f), std::move(p));
    }


    //********************* none_of *************************

    template<std::input_iterator Iter1,
	std::sentinel_for<Iter1> Iter2,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<Iter1, Proj>> Pred>
    [[nodiscard]] constexpr auto none_of(Iter1 left, Iter2 right, Pred f, Proj p = {}) -> bool
    {
	return find_if(left, right, std::move(f), std::move(p)) == right;
    }

    template<std::ranges::input_range Range,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<std::ranges::iterator_t<Range>, Proj>> Pred>
    [[nodiscard]] constexpr auto none_of(Range&& range, Pred f, Proj p = {}) -> bool
    {
	return none_of(std::begin(range), std::end(range),
		std::move(f), std::move(p));
    }

    
    //******************** none_of_n ************************

    template<std::input_iterator Iter1,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<Iter1, Proj>> Pred>
    [[nodiscard]] constexpr auto none_of_n(Iter1 left, size_t size, Pred f, Proj p = {}) -> bool
    {
	return find_if_n(left, size, std::move(f), std::move(p)) == left + size;
    }

    template<std::ranges::input_range Range,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<std::ranges::iterator_t<Range>, Proj>> Pred>
    [[nodiscard]] constexpr auto none_of_n(Range&& range, size_t size, Pred f, Proj p = {}) -> bool
    {
	return none_of_n(std::begin(range), size, std::move(f), std::move(p));
    }


    //****************** find_first_of ***********************
    
    template<std::input_iterator Iter1, std::sentinel_for<Iter1> Sent1,
	std::forward_iterator Iter2, std::sentinel_for<Iter2> Sent2,
	typename Pred = std::ranges::equal_to,
	typename Proj1 = std::identity,
	typename Proj2 = std::identity>
    requires std::indirectly_comparable<Iter1, Iter2, Pred, Proj1, Proj2>
    [[nodiscard]] constexpr auto find_first_of(Iter1 left1, Sent1 right1, Iter2 left2, Sent2 right2,
	    Pred f = {}, Proj1 p1 = {}, Proj2 p2 = {}) -> Iter1
    {
	for(; left1 != right1; ++left1)
	    for(auto it = left2; it != right2; ++it)
		if(std::invoke(f, std::invoke(p1, *left1), std::invoke(p2, *it)))
		    return left1;
	return left1;
    }

    template<std::ranges::input_range Range1,
	std::ranges::forward_range Range2,
	typename Pred = std::ranges::equal_to,
	typename Proj1 = std::identity,
	typename Proj2 = std::identity>
    requires std::indirectly_comparable<std::ranges::iterator_t<Range1>,
	std::ranges::iterator_t<Range2>,
	Pred, Proj1, Proj2>
    [[nodiscard]] constexpr auto find_first_of(Range1&& range1, Range2&& range2,
	    Pred f = {}, Proj1 p1 = {}, Proj2 p2 = {}) -> std::ranges::borrowed_iterator_t<Range1> 
    {
	return find_first_of(std::begin(range1), std::end(range1),
		std::begin(range2), std::end(range2),
		std::move(f), std::move(p1), std::move(p2));
    }


    //***************** find_first_of_n **********************
    
    template<std::input_iterator Iter1,
	std::forward_iterator Iter2,
	typename Pred = std::ranges::equal_to,
	typename Proj1 = std::identity,
	typename Proj2 = std::identity>
    requires std::indirectly_comparable<Iter1, Iter2, Pred, Proj1, Proj2>
    [[nodiscard]] constexpr auto find_first_of_n(Iter1 left1, size_t size1, Iter2 left2, size_t size2,
	    Pred f = {}, Proj1 p1 = {}, Proj2 p2 = {}) -> Iter1
    {
	for(size_t s = size2; size1 > 0; ++left1, --size1, s = size2)
	    for(auto it = left2; s > 0; ++it, --s)
		if(std::invoke(f, std::invoke(p1, *left1), std::invoke(p2, *it)))
		    return left1;
	return left1;
    }

    template<std::ranges::input_range Range1,
	std::ranges::forward_range Range2,
	typename Pred = std::ranges::equal_to,
	typename Proj1 = std::identity,
	typename Proj2 = std::identity>
    requires std::indirectly_comparable<std::ranges::iterator_t<Range1>,
	std::ranges::iterator_t<Range2>,
	Pred, Proj1, Proj2>
    [[nodiscard]] constexpr auto find_first_of_n(Range1&& range1, size_t size1, Range2&& range2, size_t size2,
	    Pred f = {}, Proj1 p1 = {}, Proj2 p2 = {}) -> std::ranges::borrowed_iterator_t<Range1> 
    {
	return find_first_of_n(std::begin(range1), size1,
		std::begin(range2), size2,
		std::move(f), std::move(p1), std::move(p2));
    }


    //******************* starts_with ************************

    template<std::input_iterator Iter1, std::sentinel_for<Iter1> Sent1,
	std::input_iterator Iter2, std::sentinel_for<Iter2> Sent2,
	typename Pred = std::ranges::equal_to,
	typename Proj1 = std::identity,
	typename Proj2 = std::identity>
    requires std::indirectly_comparable<Iter1, Iter2, Pred, Proj1, Proj2>
    [[nodiscard]] constexpr auto starts_with(Iter1 left1, Sent1 right1, Iter2 left2, Sent2 right2,
	    Pred f = {}, Proj1 p1 = {}, Proj2 p2 = {})
    {
	return mismatch(std::move(left1), right1, std::move(left2), right2,
		std::move(f), std::move(p1), std::move(p2)
	    ).in2 == right2;
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
    [[nodiscard]] constexpr auto starts_with(Range1&& range1, Range2&& range2,
	    Pred f = {}, Proj1 p1 = {}, Proj2 p2 = {})
    {
	return starts_with(std::begin(range1), std::end(range1),
		std::begin(range2), std::end(range2),
		std::move(f), std::move(p1), std::move(p2));
    }


    //******************* starts_with_n ************************

    template<std::input_iterator Iter1,
	std::forward_iterator Iter2,
	typename Pred = std::ranges::equal_to,
	typename Proj1 = std::identity,
	typename Proj2 = std::identity>
    requires std::indirectly_comparable<Iter1, Iter2, Pred, Proj1, Proj2>
    [[nodiscard]] constexpr auto starts_with_n(Iter1 left1, Iter2 left2, size_t size,
	    Pred f = {}, Proj1 p1 = {}, Proj2 p2 = {})
    {
	return mismatch_n(std::move(left1), left2, size,
		std::move(f), std::move(p1), std::move(p2)
	    ).in2 == left2 + size;
    }

    template<std::ranges::input_range Range1,
	std::ranges::forward_range Range2,
	typename Pred = std::ranges::equal_to,
	typename Proj1 = std::identity,
	typename Proj2 = std::identity>
    requires std::indirectly_comparable<
	std::ranges::iterator_t<Range1>,
	std::ranges::iterator_t<Range2>,
	Pred, Proj1, Proj2>
    [[nodiscard]] constexpr auto starts_with_n(Range1&& range1, Range2&& range2, size_t size,
	    Pred f = {}, Proj1 p1 = {}, Proj2 p2 = {})
    {
	return starts_with_n(std::begin(range1),
		std::begin(range2), size,
		std::move(f), std::move(p1), std::move(p2));
    }


    //******************** ends_with *************************

    template<std::input_iterator Iter1, std::sentinel_for<Iter1> Sent1,
	std::input_iterator Iter2, std::sentinel_for<Iter2> Sent2,
	typename Pred = std::ranges::equal_to,
	typename Proj1 = std::identity,
	typename Proj2 = std::identity>
    requires (std::forward_iterator<Iter1> || std::sized_sentinel_for<Sent1, Iter1>) &&
	(std::forward_iterator<Iter2> || std::sized_sentinel_for<Sent2, Iter2>)
    [[nodiscard]] constexpr auto ends_with(Iter1 left1, Sent1 right1, Iter2 left2, Sent2 right2,
	    Pred f = {}, Proj1 p1 = {}, Proj2 p2 = {})
    {
	const auto size1 = std::distance(left1, right1);
	const auto size2 = std::distance(left2, right2);

	if(size2 > size1)
	    return false;

	std::advance(left1, size1 - size2);
	return equal(std::move(left1), std::move(right1),
		std::move(left2), std::move(right2),
		std::move(f), std::move(p1), std::move(p2));
    }

    template<std::ranges::input_range Range1,
	std::ranges::input_range Range2,
	typename Pred = std::ranges::equal_to,
	typename Proj1 = std::identity,
	typename Proj2 = std::identity>
    requires (std::ranges::forward_range<Range1> || std::ranges::sized_range<Range1>) &&
	(std::ranges::forward_range<Range2> || std::ranges::sized_range<Range2>)
    [[nodiscard]] constexpr auto ends_with(Range1&& range1, Range2&& range2,
	    Pred f = {}, Proj1 p1 = {}, Proj2 p2 = {})
    {
	return ends_with(std::begin(range1), std::end(range1),
		std::begin(range2), std::end(range2),
		std::move(f), std::move(p1), std::move(p2));
    }


    //******************** ends_with_n *************************

    template<std::input_iterator Iter1,
	std::input_iterator Iter2,
	typename Pred = std::ranges::equal_to,
	typename Proj1 = std::identity,
	typename Proj2 = std::identity>
    [[nodiscard]] constexpr auto ends_with_n(Iter1 left1, size_t size1, Iter2 left2, size_t size2,
	    Pred f = {}, Proj1 p1 = {}, Proj2 p2 = {})
    {
	if(size2 > size1)
	    return false;

	std::advance(left1, size1 - size2);
	// size1 = size1 - (size1 - size2) = size1 - size1 + size2 = size2
	return equal_n(std::move(left1), std::move(left2), size2,
		std::move(f), std::move(p1), std::move(p2));
    }

    template<std::ranges::input_range Range1,
	std::ranges::input_range Range2,
	typename Pred = std::ranges::equal_to,
	typename Proj1 = std::identity,
	typename Proj2 = std::identity>
    [[nodiscard]] constexpr auto ends_with_n(Range1&& range1, size_t size1, Range2&& range2, size_t size2,
	    Pred f = {}, Proj1 p1 = {}, Proj2 p2 = {})
    {
	return ends_with_n(std::begin(range1), size1,
		std::begin(range2), size2,
		std::move(f), std::move(p1), std::move(p2));
    }


    //****************** adjacent_find ***********************
    
    template<std::forward_iterator Iter1, std::sentinel_for<Iter1> Iter2,
	typename Proj = std::identity,
	std::indirect_binary_predicate<
	    std::projected<Iter1, Proj>,
	    std::projected<Iter1, Proj>> Pred = std::ranges::equal_to>
    [[nodiscard]] constexpr auto adjacent_find(Iter1 left, Iter2 right, Pred f = {}, Proj p = {})
    {
	if(left == right)
	    return left;

	auto adjacent = std::next(left);
	for(; adjacent != right; ++left, ++adjacent)
	    if(std::invoke(f, std::invoke(p, *left), std::invoke(p, *adjacent)))
		return left;
	return adjacent;
    }

    template<std::ranges::forward_range Range,
	typename Proj = std::identity,
	std::indirect_binary_predicate<
	    std::projected<std::ranges::iterator_t<Range>, Proj>,
	    std::projected<std::ranges::iterator_t<Range>, Proj>> Pred = std::ranges::equal_to>
    [[nodiscard]] constexpr auto adjacent_find(Range&& range, Pred f = {}, Proj p = {})
	-> std::ranges::borrowed_iterator_t<Range>
    {
	return adjacent_find(std::begin(range), std::end(range),
		std::move(f), std::move(p));
    }


    //***************** adjacent_find_n **********************

    template<std::forward_iterator Iter1,
	typename Proj = std::identity,
	std::indirect_binary_predicate<
	    std::projected<Iter1, Proj>,
	    std::projected<Iter1, Proj>> Pred = std::ranges::equal_to>
    [[nodiscard]] constexpr auto adjacent_find_n(Iter1 left, size_t size, Pred f = {}, Proj p = {})
    {
	if(!size)
	    return left;

	auto adjacent = std::next(left);
	for(--size; size > 0; ++left, ++adjacent, --size)
	    if(std::invoke(f, std::invoke(p, *left), std::invoke(p, *adjacent)))
		return left;
	return adjacent;
    }

    template<std::ranges::forward_range Range,
	typename Proj = std::identity,
	std::indirect_binary_predicate<
	    std::projected<std::ranges::iterator_t<Range>, Proj>,
	    std::projected<std::ranges::iterator_t<Range>, Proj>> Pred = std::ranges::equal_to>
    [[nodiscard]] constexpr auto adjacent_find_n(Range&& range, size_t size, Pred f = {}, Proj p = {})
	-> std::ranges::borrowed_iterator_t<Range>
    {
	return adjacent_find_n(std::begin(range), size,
		std::move(f), std::move(p));
    }


    //********************* search ***************************

    template<std::forward_iterator Iter1, std::sentinel_for<Iter1> Sent1,
	std::forward_iterator Iter2, std::sentinel_for<Iter2> Sent2,
	typename Pred = std::ranges::equal_to,
	typename Proj1 = std::identity,
	typename Proj2 = std::identity>
    requires std::indirectly_comparable<Iter1, Iter2, Pred, Proj1, Proj2>
    [[nodiscard]] constexpr auto search(Iter1 left1, Sent1 right1, Iter2 left2, Sent2 right2,
	    Pred f = {}, Proj1 p1 = {}, Proj2 p2 = {}) -> std::ranges::subrange<Iter1>
    {
	for(;; ++left1) {
	    auto it1 = left1;
	    for(auto it2 = left2;; ++it1, ++it2) {
		if(it2 == right2)
		    return {left1, it1};
		if(it1 == right1)
		    return {it1, it1};
		if(!std::invoke(f, std::invoke(p1, *it1), std::invoke(p2, *it2)))
		    break;
	    }
	}
    }

    template<std::ranges::forward_range Range1,
	std::ranges::forward_range Range2,
	typename Pred = std::ranges::equal_to,
	typename Proj1 = std::identity,
	typename Proj2 = std::identity>
    requires std::indirectly_comparable<
	std::ranges::iterator_t<Range1>,
	std::ranges::iterator_t<Range2>,
	Pred, Proj1, Proj2>
    [[nodiscard]] constexpr auto search(Range1&& range1, Range2&& range2,
	    Pred f = {}, Proj1 p1 = {}, Proj2 p2 = {}) -> std::ranges::borrowed_subrange_t<Range1>
    {
	return search(std::begin(range1), std::end(range1),
		std::begin(range2), std::end(range2),
		std::move(f), std::move(p1), std::move(p2));
    }


    //******************** search_n **************************
    
    template<std::forward_iterator Iter1,
	std::sentinel_for<Iter1> Iter2,
	typename T,
	typename Pred = std::ranges::equal_to,
	typename Proj = std::identity>
    requires std::indirectly_comparable<Iter1, const T*, Pred, Proj>
    [[nodiscard]] constexpr auto search_n(Iter1 left, Iter2 right, std::iter_difference_t<Iter1> count,
	    const T& val, Pred f = {}, Proj p = {}) -> std::ranges::subrange<Iter1>
    {
	if(count <= 0)
	    return {left, left};

	for(; left != right; ++left) {
	    if(std::invoke(f, std::invoke(p, *left), val)) {
		auto start = left;
		std::iter_difference_t<Iter1> n{1};
		for(;;) {
		    if(n++ == count)
			return {start, std::next(left)};
		    if(++left == right)
			return {left, left};
		    if(!std::invoke(f, std::invoke(p, *left), val))
			break;
		}
	    }
	}

	return {left, left};
    }

    template<std::ranges::forward_range Range,
	typename T,
	typename Pred = std::ranges::equal_to,
	typename Proj = std::identity>
    requires std::indirectly_comparable<std::ranges::iterator_t<Range>, const T*, Pred, Proj>
    [[nodiscard]] constexpr auto search_n(Range&& range, std::ranges::range_difference_t<Range> count,
	    const T& val, Pred f = {}, Proj p = {}) -> std::ranges::borrowed_subrange_t<Range>
    {
	return search_n(std::begin(range), std::end(range), std::move(count),
		val, std::move(f), std::move(p));
    }


    //******************** find_end **************************

    template<std::forward_iterator Iter1, std::sentinel_for<Iter1> Sent1,
	std::forward_iterator Iter2, std::sentinel_for<Iter2> Sent2,
	typename Pred = std::ranges::equal_to,
	typename Proj1 = std::identity,
	typename Proj2 = std::identity>
    requires std::indirectly_comparable<Iter1, Iter2, Pred, Proj1, Proj2>
    [[nodiscard]] constexpr auto find_end(Iter1 left1, Sent1 right1, Iter2 left2, Sent2 right2,
	    Pred f = {}, Proj1 p1 = {}, Proj2 p2 = {}) -> std::ranges::subrange<Iter1>
    {
	if constexpr(std::bidirectional_iterator<Iter1> && std::bidirectional_iterator<Iter2>) {

	    auto reverse = search(std::reverse_iterator(right1), std::reverse_iterator(left1),
		    std::reverse_iterator(right2), std::reverse_iterator(left2),
		    std::move(f), std::move(p1), std::move(p2));
	    return {std::end(reverse).base(), std::begin(reverse).base()};

	}

	if(left2 == right2) {
	    auto last = std::ranges::next(left1, right1);
	    return {last, last};
	}

	std::ranges::subrange<Iter1> result{}, new_result{left1, left1};

	do {
	    result = std::move(new_result);
	    new_result = search(std::end(result), right1, left2, right2, f, p1, p2);
	} while(!new_result.empty());

	return result;
    }

    template<std::ranges::forward_range Range1,
	std::ranges::forward_range Range2,
	typename Pred = std::ranges::equal_to,
	typename Proj1 = std::identity,
	typename Proj2 = std::identity>
    requires std::indirectly_comparable<
	std::ranges::iterator_t<Range1>,
	std::ranges::iterator_t<Range2>,
	Pred, Proj1, Proj2>
    [[nodiscard]] constexpr auto find_end(Range1&& range1, Range2&& range2,
	    Pred f = {}, Proj1 p1 = {}, Proj2 p2 = {}) -> std::ranges::borrowed_subrange_t<Range1>
    {
	return find_end(std::begin(range1), std::end(range1),
		std::begin(range2), std::end(range2),
		std::move(f), std::move(p1), std::move(p2));
    }


    //******************* find_end_n *************************
    
    template<std::forward_iterator Iter1,
	std::sentinel_for<Iter1> Iter2,
	typename T,
	typename Pred = std::ranges::equal_to,
	typename Proj = std::identity>
    requires std::indirectly_comparable<Iter1, const T*, Pred, Proj>
    [[nodiscard]] constexpr auto find_end_n(Iter1 left, Iter2 right, std::iter_difference_t<Iter1> count,
	    const T& val, Pred f = {}, Proj p = {}) -> std::ranges::subrange<Iter1>
    {
	if constexpr(std::random_access_iterator<Iter1> && std::random_access_iterator<Iter2>) {
	    auto last = std::ranges::next(left, right);

	    if(count <= 0)
		return {last, last};

	    if(std::distance(left, right) == 0)
		return {left, left};

	    last = std::prev(last);

	    for(; last != left; --last) {
		if(std::invoke(f, std::invoke(p, *last), val)) {
		    auto end = last;
		    std::iter_difference_t<Iter1> n{1};
		    for(;;) {
			if(n++ == count)
			    return {last, std::next(end)};
			if(--last == left)
			    return {last, last};
			if(!std::invoke(f, std::invoke(p, *last), val))
			    break;
		    }
		}
	    }

	    return {left, left};
	} 

	if constexpr(std::bidirectional_iterator<Iter1> && std::bidirectional_iterator<Iter2>) {

	    auto reverse = alg::search_n(std::reverse_iterator(right), std::reverse_iterator(left),
		    std::move(count), val, std::move(f), std::move(p));
	    return {std::end(reverse).base(), std::begin(reverse).base()};

	}

	if(count <= 0) {
	    auto last = std::ranges::next(left, right);
	    return {last, last};
	}

	std::ranges::subrange<Iter1> result{}, new_result{left, left};

	do {
	    result = std::move(new_result);
	    new_result = search_n(std::end(result), right, count, val, f, p);
	} while(!new_result.empty());


	if(std::begin(result) == right)
	    return {left, left};
	return result;
    }

    template<std::ranges::forward_range Range,
	typename T,
	typename Pred = std::ranges::equal_to,
	typename Proj = std::identity>
    requires std::indirectly_comparable<std::ranges::iterator_t<Range>, const T*, Pred, Proj>
    [[nodiscard]] constexpr auto find_end_n(Range&& range, std::ranges::range_difference_t<Range> count,
	    const T& val, Pred f = {}, Proj p = {}) -> std::ranges::borrowed_subrange_t<Range>
    {
	return find_end_n(std::begin(range), std::end(range), std::move(count),
		val, std::move(f), std::move(p));
    }


}
