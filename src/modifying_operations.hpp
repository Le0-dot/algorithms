#pragma once

#include <functional>
#include <ranges>
#include <iterator>
#include <algorithm>

#include "non_modifying_operations.hpp"
#include "minmax_operations.hpp"

namespace alg
{

    //********************** iter_swap ****************************
    
    template<std::input_iterator Iter1, std::input_iterator Iter2>
    constexpr auto iter_swap(Iter1 it1, Iter2 it2)
    {
	std::swap(*it1, *it2);
    }


    //******************** copy ***********************

    template<std::input_iterator Iter, std::sentinel_for<Iter> Sent,
	std::weakly_incrementable Out>
    requires std::indirectly_copyable<Iter, Out>
    constexpr auto copy(Iter left, Sent right, Out out)
	-> std::ranges::in_out_result<Iter, Out>
    {
	for(; left != right; *out++ = *left++);

	return {std::move(left), std::move(out)};
    }

    template<std::ranges::input_range Range,
	std::weakly_incrementable Out>
    requires std::indirectly_copyable<std::ranges::iterator_t<Range>, Out>
    constexpr auto copy(Range&& range, Out out)
	-> std::ranges::in_out_result<std::ranges::borrowed_iterator_t<Range>, Out>
    {
	return ::alg::copy(std::begin(range), std::end(range), std::move(out));
    }


    //******************* copy_n **********************

    template<std::input_iterator Iter,
	std::weakly_incrementable Out>
    requires std::indirectly_copyable<Iter, Out>
    constexpr auto copy_n(Iter left, std::iter_difference_t<Iter> n, Out out)
	-> std::ranges::in_out_result<Iter, Out>
    {
	for(std::iter_difference_t<Iter> i{}; i != n; *out++ = *left++, ++i);

	return {std::move(left), std::move(out)};
    }

    template<std::ranges::input_range Range,
	std::weakly_incrementable Out>
    requires std::indirectly_copyable<std::ranges::iterator_t<Range>, Out>
    constexpr auto copy_n(Range&& range, std::ranges::range_difference_t<Range> n, Out out)
	-> std::ranges::in_out_result<std::ranges::borrowed_iterator_t<Range>, Out>
    {
	return ::alg::copy_n(std::begin(range), std::move(n), std::move(out));
    }


    //******************* copy_if *********************

    template<std::input_iterator Iter, std::sentinel_for<Iter> Sent,
	std::weakly_incrementable Out, 
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<Iter, Proj>> Pred>
    requires std::indirectly_copyable<Iter, Out>
    constexpr auto copy_if(Iter left, Sent right, Out out, Pred f, Proj p = {})
	-> std::ranges::in_out_result<Iter, Out>
    {
	for(; left != right; ++left)
	    if(std::invoke(f, std::invoke(p, *left)))
		*out++ = *left;

	return {std::move(left), std::move(out)};
    }

    template<std::ranges::input_range Range,
	std::weakly_incrementable Out,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<std::ranges::iterator_t<Range>, Proj>> Pred>
    requires std::indirectly_copyable<std::ranges::iterator_t<Range>, Out>
    constexpr auto copy_if(Range&& range, Out out, Pred f, Proj p = {})
	-> std::ranges::in_out_result<std::ranges::borrowed_iterator_t<Range>, Out>
    {
	return ::alg::copy_if(std::begin(range), std::end(range), std::move(out), std::ref(f), std::ref(p));
    }


    //****************** copy_if_n ********************

    template<std::input_iterator Iter,
	std::weakly_incrementable Out, 
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<Iter, Proj>> Pred>
    requires std::indirectly_copyable<Iter, Out>
    constexpr auto copy_if_n(Iter left, std::iter_difference_t<Iter> n, Out out, Pred f, Proj p = {})
	-> std::ranges::in_out_result<Iter, Out>
    {
	for(std::iter_difference_t<Iter> i{}; i != n; ++left)
	    if(std::invoke(f, std::invoke(p, *left))) {
		*out++ = *left;
		++i;
	    }

	return {std::move(left), std::move(out)};
    }

    template<std::ranges::input_range Range,
	std::weakly_incrementable Out,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<std::ranges::iterator_t<Range>, Proj>> Pred>
    requires std::indirectly_copyable<std::ranges::iterator_t<Range>, Out>
    constexpr auto copy_if_n(Range&& range, std::ranges::range_difference_t<Range> n,
	    Out out, Pred f, Proj p = {})
	-> std::ranges::in_out_result<std::ranges::borrowed_iterator_t<Range>, Out>
    {
	return copy_if_n(std::begin(range), std::move(n), std::move(out), std::ref(f), std::ref(p));
    }


    //**************** copy_backwards *****************
    
    template<std::bidirectional_iterator Iter, std::sentinel_for<Iter> Sent,
	std::bidirectional_iterator Out>
    requires std::indirectly_copyable<Iter, Out>
    constexpr auto copy_backwards(Iter left, Sent right, Out out)
	-> std::ranges::in_out_result<Iter, Out>
    {
	Iter iter{std::ranges::next(left, std::move(right))};
	for(Iter i{iter}; i != left; *--out = *--i);

	return {std::move(iter), std::move(out)};
    }

    template<std::ranges::bidirectional_range Range,
	std::bidirectional_iterator Out>
    requires std::indirectly_copyable<std::ranges::iterator_t<Range>, Out>
    constexpr auto copy_backwards(Range&& range, Out out)
	-> std::ranges::in_out_result<std::ranges::borrowed_iterator_t<Range>, Out>
    {
	return ::alg::copy_backwards(std::begin(range), std::end(range), std::move(out));
    }


    //*************** copy_backwards_n ****************
    
    template<std::bidirectional_iterator Iter,
	std::bidirectional_iterator Out>
    requires std::indirectly_copyable<Iter, Out>
    constexpr auto copy_backwards_n(Iter left, std::iter_difference_t<Iter> n, Out out)
	-> std::ranges::in_out_result<Iter, Out>
    {
	Iter iter{std::ranges::next(left, n)};
	for(Iter i{iter}; i != left; *--out = *--i);

	return {std::move(iter), std::move(out)};
    }

    template<std::ranges::bidirectional_range Range,
	std::bidirectional_iterator Out>
    requires std::indirectly_copyable<std::ranges::iterator_t<Range>, Out>
    constexpr auto copy_backwards_n(Range&& range, std::ranges::range_difference_t<Range> n, Out out)
	-> std::ranges::in_out_result<std::ranges::borrowed_iterator_t<Range>, Out>
    {
	return ::alg::copy_backwards_n(std::begin(range), std::move(n), std::move(out));
    }

    
    //******************** move ***********************

    template<std::input_iterator Iter, std::sentinel_for<Iter> Sent,
	std::weakly_incrementable Out>
    requires std::indirectly_movable<Iter, Out>
    constexpr auto move(Iter left, Sent right, Out out)
	-> std::ranges::in_out_result<Iter, Out>
    {
	for(; left != right; ++left, ++out)
	    *out = std::ranges::iter_move(left);

	return {std::move(left), std::move(out)};
    }

    template<std::ranges::input_range Range,
	std::weakly_incrementable Out>
    requires std::indirectly_movable<std::ranges::iterator_t<Range>, Out>
    constexpr auto move(Range&& range, Out out)
	-> std::ranges::in_out_result<std::ranges::borrowed_iterator_t<Range>, Out>
    {
	return ::alg::move(std::begin(range), std::end(range), std::move(out));
    }


    //******************* move_n **********************

    template<std::input_iterator Iter,
	std::weakly_incrementable Out>
    requires std::indirectly_movable<Iter, Out>
    constexpr auto move_n(Iter left, std::iter_difference_t<Iter> n, Out out)
	-> std::ranges::in_out_result<Iter, Out>
    {
	for(std::iter_difference_t<Iter> i{}; i != n; ++left, ++out, ++i)
	    *out = std::ranges::iter_move(left);

	return {std::move(left), std::move(out)};
    }

    template<std::ranges::input_range Range,
	std::weakly_incrementable Out>
    requires std::indirectly_movable<std::ranges::iterator_t<Range>, Out>
    constexpr auto move_n(Range&& range, std::ranges::range_difference_t<Range> n, Out out)
	-> std::ranges::in_out_result<std::ranges::borrowed_iterator_t<Range>, Out>
    {
	return ::alg::move_n(std::begin(range), std::move(n), std::move(out));
    }


    //**************** move_backwards *****************
    
    template<std::bidirectional_iterator Iter, std::sentinel_for<Iter> Sent,
	std::bidirectional_iterator Out>
    requires std::indirectly_movable<Iter, Out>
    constexpr auto move_backwards(Iter left, Sent right, Out out)
	-> std::ranges::in_out_result<Iter, Out>
    {
	Iter iter{std::ranges::next(left, std::move(right))};
	for(Iter i{iter}; i != left; *--out = std::ranges::iter_move(--i));

	return {std::move(iter), std::move(out)};
    }

    template<std::ranges::bidirectional_range Range,
	std::bidirectional_iterator Out>
    requires std::indirectly_movable<std::ranges::iterator_t<Range>, Out>
    constexpr auto move_backwards(Range&& range, Out out)
	-> std::ranges::in_out_result<std::ranges::borrowed_iterator_t<Range>, Out>
    {
	return ::alg::move_backwards(std::begin(range), std::end(range), std::move(out));
    }


    //*************** move_backwards_n ****************
    
    template<std::bidirectional_iterator Iter,
	std::bidirectional_iterator Out>
    requires std::indirectly_movable<Iter, Out>
    constexpr auto move_backwards_n(Iter left, std::iter_difference_t<Iter> n, Out out)
	-> std::ranges::in_out_result<Iter, Out>
    {
	Iter iter{std::ranges::next(left, n)};
	for(Iter i{iter}; i != left; *--out = std::ranges::iter_move(--i));

	return {std::move(iter), std::move(out)};
    }

    template<std::ranges::bidirectional_range Range,
	std::bidirectional_iterator Out>
    requires std::indirectly_movable<std::ranges::iterator_t<Range>, Out>
    constexpr auto move_backwards_n(Range&& range, std::ranges::range_difference_t<Range> n, Out out)
	-> std::ranges::in_out_result<std::ranges::borrowed_iterator_t<Range>, Out>
    {
	return ::alg::move_backwards_n(std::begin(range), std::move(n), std::move(out));
    }


    //******************** fill ***********************

    template<typename T,
	std::output_iterator<const T&> Iter,
	std::sentinel_for<Iter> Sent>
    constexpr auto fill(Iter left, Sent right, const T& val)
    {
	while(left != right)
	    *left++ = val;

	return left;
    }

    template<typename T,
	std::ranges::output_range<const T&> Range>
    constexpr auto fill(Range&& range, const T& val)
    {
	return ::alg::fill(std::begin(range), std::end(range), val);
    }


    //******************* fill_n **********************

    template<typename T,
	std::output_iterator<const T&> Iter>
    constexpr auto fill_n(Iter left, std::iter_difference_t<Iter> n, const T& val)
    {
	for(std::iter_difference_t<Iter> i{}; i != n; ++left, ++i)
	    *left = val;

	return left;
    }

    template<typename T,
	std::ranges::output_range<const T&> Range>
    constexpr auto fill_n(Range&& range, std::ranges::range_difference_t<Range> n, const T& val)
    {
	return ::alg::fill_n(std::begin(range), std::move(n), val);
    }


    //***************** transform *********************

    template<std::input_iterator Iter, std::sentinel_for<Iter> Sent,
	std::weakly_incrementable Out, std::copy_constructible Op, 
	typename Proj = std::identity>
    requires std::indirectly_writable<Out, std::indirect_result_t<Op&, std::projected<Iter, Proj>>>
    constexpr auto transform(Iter left, Sent right, Out out, Op f, Proj p = {})
	-> std::ranges::in_out_result<Iter, Out>
    {
	for(; left != right; ++left, ++out)
	    *out = std::invoke(f, std::invoke(p, *left));

	return {left, out};
    }

    template<std::ranges::input_range Range,
	std::weakly_incrementable Out, std::copy_constructible Op, 
	typename Proj = std::identity>
    requires std::indirectly_writable<Out, 
	std::indirect_result_t<Op&, std::projected<std::ranges::iterator_t<Range>, Proj>>>
    constexpr auto transform(Range&& range, Out out, Op f, Proj p = {})
	-> std::ranges::in_out_result<std::ranges::borrowed_iterator_t<Range>, Out>
    {
	return ::alg::transform(std::begin(range), std::end(range), out, std::ref(f), std::ref(p));
    }
	
    template<std::input_iterator Iter1, std::sentinel_for<Iter1> Sent1,
	std::input_iterator Iter2, std::sentinel_for<Iter2> Sent2,
	std::weakly_incrementable Out, std::copy_constructible Op,
	typename Proj1 = std::identity, typename Proj2 = std::identity>
    requires std::indirectly_writable<Out, std::indirect_result_t<Op&,
	std::projected<Iter1, Proj1>,
	std::projected<Iter2, Proj2>>>
    constexpr auto transform(Iter1 left1, Sent1 right1, Iter2 left2, Sent2 right2,
	Out out, Op f, Proj1 p1 = {}, Proj2 p2 = {})
	-> std::ranges::in_in_out_result<Iter1, Iter2, Out>
    {
	for(; left1 != right1 && left2 != right2; ++left1, ++left2, ++out)
	    *out = std::invoke(f, std::invoke(p1, *left1), std::invoke(p2, *left2));

	return {left1, left2, out};
    }

    template<std::ranges::input_range Range1,
	std::ranges::input_range Range2,
	std::weakly_incrementable Out, std::copy_constructible Op,
	typename Proj1 = std::identity, typename Proj2 = std::identity>
    requires std::indirectly_writable<Out, std::indirect_result_t<Op,
	std::projected<std::ranges::iterator_t<Range1>, Proj1>,
	std::projected<std::ranges::iterator_t<Range2>, Proj2>>>
    constexpr auto transform(Range1&& range1, Range2&& range2,
	Out out, Op f, Proj1 p1 = {}, Proj2 p2 = {})
	-> std::ranges::in_in_out_result<
	    std::ranges::borrowed_iterator_t<Range1>,
	    std::ranges::borrowed_iterator_t<Range2>,
	    Out>
    {
	return ::alg::transform(std::begin(range1), std::end(range1), std::begin(range2), std::end(range2),
		out, std::ref(f), std::ref(p1), std::ref(p2));
    }


    //**************** transform_n ********************

    template<std::input_iterator Iter,
	std::weakly_incrementable Out, std::copy_constructible Op, 
	typename Proj = std::identity>
    requires std::indirectly_writable<Out, std::indirect_result_t<Op&, std::projected<Iter, Proj>>>
    constexpr auto transform_n(Iter left, std::iter_difference_t<Iter> n, Out out, Op f, Proj p = {})
	-> std::ranges::in_out_result<Iter, Out>
    {
	for(std::iter_difference_t<Iter> i{}; i < n; ++i, ++left, ++out)
	    *out = std::invoke(f, std::invoke(p, *left));

	return {left, out};
    }

    template<std::ranges::input_range Range,
	std::weakly_incrementable Out, std::copy_constructible Op, 
	typename Proj = std::identity>
    requires std::indirectly_writable<Out, 
	std::indirect_result_t<Op&, std::projected<std::ranges::iterator_t<Range>, Proj>>>
    constexpr auto transform_n(Range&& range, std::ranges::range_difference_t<Range> n, Out out, Op f, Proj p = {})
	-> std::ranges::in_out_result<std::ranges::borrowed_iterator_t<Range>, Out>
    {
	return ::alg::transform_n(std::begin(range), std::move(n), out, std::ref(f), std::ref(p));
    }
	
    template<std::input_iterator Iter1,
	std::input_iterator Iter2,
	std::weakly_incrementable Out, std::copy_constructible Op,
	typename Proj1 = std::identity, typename Proj2 = std::identity>
    requires std::indirectly_writable<Out, std::indirect_result_t<Op&,
	std::projected<Iter1, Proj1>,
	std::projected<Iter2, Proj2>>>
    constexpr auto transform_n(Iter1 left1, Iter2 left2,
	std::common_type_t<std::iter_difference_t<Iter1>, std::iter_difference_t<Iter2>> n,
	Out out, Op f, Proj1 p1 = {}, Proj2 p2 = {})
	-> std::ranges::in_in_out_result<Iter1, Iter2, Out>
    {
	using diff_t = std::common_type_t<std::iter_difference_t<Iter1>, std::iter_difference_t<Iter2>>;
	for(diff_t i{}; i < n; ++i, ++left1, ++left2, ++out)
	    *out = std::invoke(f, std::invoke(p1, *left1), std::invoke(p2, *left2));

	return {left1, left2, out};
    }

    template<std::ranges::input_range Range1,
	std::ranges::input_range Range2,
	std::weakly_incrementable Out, std::copy_constructible Op,
	typename Proj1 = std::identity, typename Proj2 = std::identity>
    requires std::indirectly_writable<Out, std::indirect_result_t<Op,
	std::projected<std::ranges::iterator_t<Range1>, Proj1>,
	std::projected<std::ranges::iterator_t<Range2>, Proj2>>>
    constexpr auto transform_n(Range1&& range1, Range2&& range2,
	std::common_type_t<std::ranges::range_difference_t<Range1>, std::ranges::range_difference_t<Range2>> n,
	Out out, Op f, Proj1 p1 = {}, Proj2 p2 = {})
	-> std::ranges::in_in_out_result<
	    std::ranges::borrowed_iterator_t<Range1>,
	    std::ranges::borrowed_iterator_t<Range2>,
	    Out>
    {
	return ::alg::transform_n(std::begin(range1), std::begin(range2), std::move(n),
		out, std::ref(f), std::ref(p1), std::ref(p2));
    }


    //***************** generate **********************

    template<std::input_or_output_iterator Iter, std::sentinel_for<Iter> Sent,
	std::copy_constructible F>
    requires std::invocable<F&> && std::indirectly_writable<Iter, std::invoke_result_t<F&>>
    constexpr auto generate(Iter left, Sent right, F gen)
    {
	for(; left != right; *left++ = std::invoke(gen));
	return left;
    }

    template<std::copy_constructible F,
	std::ranges::output_range<std::invoke_result_t<F&>> Range>
    requires std::invocable<F&>
    constexpr auto generate(Range&& range, F gen) -> std::ranges::borrowed_iterator_t<Range>
    {
	return ::alg::generate(std::begin(range), std::end(range), std::move(gen));
    }


    //**************** generate_n *********************

    template<std::input_or_output_iterator Iter,
	std::copy_constructible F>
    requires std::invocable<F&> && std::indirectly_writable<Iter, std::invoke_result_t<F&>>
    constexpr auto generate_n(Iter left, std::iter_difference_t<Iter> n, F gen)
    {
	for(std::iter_difference_t<Iter> i{}; i < n; ++i, *left++ = std::invoke(gen));
	return left;
    }

    template<std::copy_constructible F,
	std::ranges::output_range<std::invoke_result_t<F&>> Range>
    requires std::invocable<F&>
    constexpr auto generate_n(Range&& range, std::ranges::range_difference_t<Range> n, F gen) -> std::ranges::borrowed_iterator_t<Range>
    {
	return ::alg::generate_n(std::begin(range), std::move(n), std::move(gen));
    }


    //****************** remove ***********************

    template<std::permutable Iter, std::sentinel_for<Iter> Sent,
	typename T, typename Proj = std::identity>
    requires std::indirect_binary_predicate<std::ranges::equal_to,
	std::projected<Iter, Proj>,
	const T*>
    constexpr auto remove(Iter left, Sent right, const T& val, Proj p = {})
	-> std::ranges::subrange<Iter>
    {
	left = find(std::move(left), right, val, p);

	if(left != right)
	    for(auto i{std::ranges::next(left)}; i != right; ++i)
		if(val != std::invoke(p, *i))
		    *left++ = std::ranges::iter_move(i);

	return {left, right};
    }

    template<std::ranges::forward_range Range,
	typename T, typename Proj = std::identity>
    requires std::permutable<std::ranges::iterator_t<Range>> && 
	std::indirect_binary_predicate<std::ranges::equal_to,
	    std::projected<std::ranges::iterator_t<Range>, Proj>,
	    const T*>
    constexpr auto remove(Range&& range, const T& val, Proj p = {})
	-> std::ranges::borrowed_subrange_t<Range>
    {
	return remove(std::begin(range), std::end(range), val, std::move(p));
    }


    //****************** remove_n ***********************

    template<std::permutable Iter,
	typename T, typename Proj = std::identity>
    requires std::indirect_binary_predicate<std::ranges::equal_to,
	std::projected<Iter, Proj>,
	const T*>
    constexpr auto remove_n(Iter left, std::iter_difference_t<Iter> n, const T& val, Proj p = {})
	-> std::ranges::subrange<Iter>
    {
	auto right = std::ranges::next(left, n);
	left = find(std::move(left), right, val, p);

	if(left != right)
	    for(auto i{std::ranges::next(left)}; i != right; ++i)
		if(val != std::invoke(p, *i))
		    *left++ = std::ranges::iter_move(i);

	return {left, right};
 
    }

    template<std::ranges::forward_range Range,
	typename T, typename Proj = std::identity>
    requires std::permutable<std::ranges::iterator_t<Range>> && 
	std::indirect_binary_predicate<std::ranges::equal_to,
	    std::projected<std::ranges::iterator_t<Range>, Proj>,
	    const T*>
    constexpr auto remove_n(Range&& range, std::ranges::range_difference_t<Range> n, const T& val, Proj p = {})
	-> std::ranges::borrowed_subrange_t<Range>
    {
	return remove_n(std::begin(range), n, val, std::move(p));
    }

    
    //***************** remove_if *********************

    template<std::permutable Iter, std::sentinel_for<Iter> Sent,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<Iter, Proj>> Pred>
    constexpr auto remove_if(Iter left, Sent right, Pred f, Proj p = {})
	-> std::ranges::subrange<Iter>
    {
	left = find_if(std::move(left), right, f, p);

	if(left != right)
	    for(auto i{std::ranges::next(left)}; i != right; ++i)
		if(!std::invoke(f, std::invoke(p, *i)))
		    *left++ = std::ranges::iter_move(i);

	return {left, right};
    }

    template<std::ranges::forward_range Range,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<std::ranges::iterator_t<Range>, Proj>> Pred>
    constexpr auto remove_if(Range&& range, Pred f, Proj p = {})
	-> std::ranges::borrowed_subrange_t<Range>
    {
	return ::alg::remove_if(std::begin(range), std::end(range), f, std::move(p));
    }


    //**************** remove_if_n **********************

    template<std::permutable Iter,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<Iter, Proj>> Pred>
    constexpr auto remove_if_n(Iter left, std::iter_difference_t<Iter> n, Pred f, Proj p = {})
	-> std::ranges::subrange<Iter>
    {
	auto right = std::ranges::next(left, n);
	left = find_if_n(std::move(left), n, f, p);

	if(left != right)
	    for(auto i{std::ranges::next(left)}; i != right; ++i)
		if(!std::invoke(f, std::invoke(p, *i)))
		    *left++ = std::ranges::iter_move(i);

	return {left, right};
 
    }

    template<std::ranges::forward_range Range,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<std::ranges::iterator_t<Range>, Proj>> Pred>
    constexpr auto remove_if_n(Range&& range, std::ranges::range_difference_t<Range> n, Pred f, Proj p = {})
	-> std::ranges::borrowed_subrange_t<Range>
    {
	return remove_if_n(std::begin(range), n, f, std::move(p));
    }


    //****************** remove_copy ***********************

    template<std::input_iterator Iter, std::sentinel_for<Iter> Sent,
	std::weakly_incrementable Out,
	typename T, typename Proj = std::identity>
    requires std::indirectly_copyable<Iter, Out> &&
	std::indirect_binary_predicate<std::ranges::equal_to,
	std::projected<Iter, Proj>,
	const T*>
    constexpr auto remove_copy(Iter left, Sent right, Out out, const T& val, Proj p = {})
	-> std::ranges::in_out_result<Iter, Out>
    {
	for(; left != right; ++left)
	    if(val != std::invoke(p, *left))
		*out++ = *left;

	return {std::move(left), std::move(out)};
    }

    template<std::ranges::input_range Range,
	std::weakly_incrementable Out,
	typename T, typename Proj = std::identity>
    requires std::indirectly_copyable<std::ranges::iterator_t<Range>, Out> &&
	std::indirect_binary_predicate<std::ranges::equal_to,
	    std::projected<std::ranges::iterator_t<Range>, Proj>,
	    const T*>
    constexpr auto remove_copy(Range&& range, Out out, const T& val, Proj p = {})
	-> std::ranges::in_out_result<std::ranges::iterator_t<Range>, Out>
    {
	return ::alg::remove_copy(std::begin(range), std::end(range), std::move(out), val, std::move(p));
    }


    //****************** remove_copy_n ***********************

    template<std::input_iterator Iter,
	std::weakly_incrementable Out,
	typename T, typename Proj = std::identity>
    requires std::indirectly_copyable<Iter, Out> &&
	std::indirect_binary_predicate<std::ranges::equal_to,
	std::projected<Iter, Proj>,
	const T*>
    constexpr auto remove_copy_n(Iter left, std::iter_difference_t<Iter> n, Out out, const T& val, Proj p = {})
	-> std::ranges::in_out_result<Iter, Out>
    {
	for(std::iter_difference_t<Iter> i{}; i != n; ++i, ++left)
	    if(val != std::invoke(p, *left))
		*out++ = *left;

	return {std::move(left), std::move(out)};
 
    }

    template<std::ranges::input_range Range,
	std::weakly_incrementable Out,
	typename T, typename Proj = std::identity>
    requires std::indirectly_copyable<std::ranges::iterator_t<Range>, Out> &&
	std::indirect_binary_predicate<std::ranges::equal_to,
	    std::projected<std::ranges::iterator_t<Range>, Proj>,
	    const T*>
    constexpr auto remove_copy_n(Range&& range, std::ranges::range_difference_t<Range> n, Out out, const T& val, Proj p = {})
	-> std::ranges::in_out_result<std::ranges::iterator_t<Range>, Out>
    {
	return remove_copy_n(std::begin(range), n, std::move(out), val, std::move(p));
    }

    
    //***************** remove_copy_if *********************

    template<std::input_iterator Iter, std::sentinel_for<Iter> Sent,
	std::weakly_incrementable Out,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<Iter, Proj>> Pred>
    requires std::indirectly_copyable<Iter, Out>
    constexpr auto remove_copy_if(Iter left, Sent right, Out out, Pred f, Proj p = {})
	-> std::ranges::in_out_result<Iter, Out>
    {
	for(; left != right; ++left)
	    if(!std::invoke(f, std::invoke(p, *left)))
		*out++ = *left;

	return {std::move(left), std::move(out)};
    }

    template<std::ranges::input_range Range,
	std::weakly_incrementable Out,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<std::ranges::iterator_t<Range>, Proj>> Pred>
    requires std::indirectly_copyable<std::ranges::iterator_t<Range>, Out>
    constexpr auto remove_copy_if(Range&& range, Out out, Pred f, Proj p = {})
	-> std::ranges::in_out_result<std::ranges::iterator_t<Range>, Out>
    {
	return ::alg::remove_copy_if(std::begin(range), std::end(range), std::move(out), f, std::move(p));
    }


    //**************** remove_copy_if_n **********************

    template<std::input_iterator Iter,
	std::weakly_incrementable Out,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<Iter, Proj>> Pred>
    requires std::indirectly_copyable<Iter, Out>
    constexpr auto remove_copy_if_n(Iter left, std::iter_difference_t<Iter> n,
	Out out, Pred f, Proj p = {})
	-> std::ranges::in_out_result<Iter, Out>
    {
	for(std::iter_difference_t<Iter> i{}; i != n; ++i, ++left)
	    if(!std::invoke(f, std::invoke(p, *left)))
		*out++ = *left;

	return {std::move(left), std::move(out)};
 
    }

    template<std::ranges::input_range Range,
	std::weakly_incrementable Out,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<std::ranges::iterator_t<Range>, Proj>> Pred>
    requires std::indirectly_copyable<std::ranges::iterator_t<Range>, Out>
    constexpr auto remove_copy_if_n(Range&& range, std::ranges::range_difference_t<Range> n,
	Out out, Pred f, Proj p = {})
	-> std::ranges::in_out_result<std::ranges::iterator_t<Range>, Out>
    {
	return remove_copy_if_n(std::begin(range), n, std::move(out), f, std::move(p));
    }


    //********************* replace **************************

    template<std::input_iterator Iter, std::sentinel_for<Iter> Sent,
	typename Old, typename New,
	typename Proj = std::identity>
    requires std::indirectly_writable<Iter, const New&> &&
	std::indirect_binary_predicate<std::ranges::equal_to,
	    std::projected<Iter, Proj>,
	    const Old*>
    constexpr auto replace(Iter left, Sent right, const Old& old, const New& val, Proj p = {})
    {
	for(; left != right; ++left)
	    if(old == std::invoke(p, *left))
		*left = val;

	return left;
    }

    template<std::ranges::input_range Range,
	typename Old, typename New,
	typename Proj = std::identity>
    requires std::indirectly_writable<std::ranges::iterator_t<Range>, const New&> &&
	std::indirect_binary_predicate<std::ranges::equal_to,
	    std::projected<std::ranges::iterator_t<Range>, Proj>,
	    const Old*>
    constexpr auto replace(Range&& range, const Old& old, const New& val, Proj p = {})
    {
	return ::alg::replace(std::begin(range), std::end(range), old, val, std::move(p));
    }


    //******************** replace_n *************************

    template<std::input_iterator Iter,
	typename Old, typename New,
	typename Proj = std::identity>
    requires std::indirectly_writable<Iter, const New&> &&
	std::indirect_binary_predicate<std::ranges::equal_to,
	    std::projected<Iter, Proj>,
	    const Old*>
    constexpr auto replace_n(Iter left, std::iter_difference_t<Iter> n, const Old& old, const New& val, Proj p = {})
    {
	for(std::iter_difference_t<Iter> i{}; i != n; ++i, ++left)
	    if(old == std::invoke(p, *left))
		*left = val;

	return left;
    }

    template<std::ranges::input_range Range,
	typename Old, typename New,
	typename Proj = std::identity>
    requires std::indirectly_writable<std::ranges::iterator_t<Range>, const New&> &&
	std::indirect_binary_predicate<std::ranges::equal_to,
	    std::projected<std::ranges::iterator_t<Range>, Proj>,
	    const Old*>
    constexpr auto replace_n(Range&& range, std::ranges::range_difference_t<Range> n, const Old& old, const New& val, Proj p = {})
    {
	return ::alg::replace_n(std::begin(range), std::move(n), old, val, std::move(p));
    }


    //******************* replace_if *************************

    template<std::input_iterator Iter, std::sentinel_for<Iter> Sent,
	typename New,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<Iter, Proj>> Pred>
    requires std::indirectly_writable<Iter, const New&>
    constexpr auto replace_if(Iter left, Sent right, Pred f, const New& val, Proj p = {})
    {
	for(; left != right; ++left)
	    if(std::invoke(f, std::invoke(p, *left)))
		*left = val;

	return left;
    }

    template<std::ranges::input_range Range,
	typename New,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<std::ranges::iterator_t<Range>, Proj>> Pred>
    requires std::indirectly_writable<std::ranges::iterator_t<Range>, const New&>
    constexpr auto replace_if(Range&& range, Pred f, const New& val, Proj p = {})
    {
	return ::alg::replace_if(std::begin(range), std::end(range), std::move(f), val, std::move(p));
    }


    //****************** replace_if_n ************************

    template<std::input_iterator Iter,
	typename New,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<Iter, Proj>> Pred>
    requires std::indirectly_writable<Iter, const New&>
    constexpr auto replace_if_n(Iter left, std::iter_difference_t<Iter> n, Pred f, const New& val, Proj p = {})
    {
	for(std::iter_difference_t<Iter> i{}; i != n; ++i, ++left)
	    if(std::invoke(f, std::invoke(p, *left)))
		*left = val;

	return left;
    }

    template<std::ranges::input_range Range,
	typename New,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<std::ranges::iterator_t<Range>, Proj>> Pred>
    requires std::indirectly_writable<std::ranges::iterator_t<Range>, const New&>
    constexpr auto replace_if_n(Range&& range, std::ranges::range_difference_t<Range> n, Pred f, const New& val, Proj p = {})
    {
	return ::alg::replace_if_n(std::begin(range), std::move(n), std::move(f), val, std::move(p));
    }


    //********************* replace_copy **************************

    template<std::input_iterator Iter, std::sentinel_for<Iter> Sent,
	typename Old, typename New,
	std::output_iterator<const New&> Out,
	typename Proj = std::identity>
    requires std::indirectly_copyable<Iter, Out> &&
	std::indirect_binary_predicate<std::ranges::equal_to,
	    std::projected<Iter, Proj>,
	    const Old*>
    constexpr auto replace_copy(Iter left, Sent right, Out out, const Old& old, const New& val, Proj p = {})
	-> std::ranges::in_out_result<Iter, Out>
    {
	for(; left != right; ++left, ++out)
	    *out = (old == std::invoke(p, *left)) ? val : *left;

	return {std::move(left), std::move(out)};
    }

    template<std::ranges::input_range Range,
	typename Old, typename New,
	std::output_iterator<const New&> Out,
	typename Proj = std::identity>
    requires std::indirectly_copyable<std::ranges::iterator_t<Range>, Out> &&
	std::indirect_binary_predicate<std::ranges::equal_to,
	    std::projected<std::ranges::iterator_t<Range>, Proj>,
	    const Old*>
    constexpr auto replace_copy(Range&& range, Out out, const Old& old, const New& val, Proj p = {})
	-> std::ranges::in_out_result<std::ranges::borrowed_iterator_t<Range>, Out>
    {
	return ::alg::replace_copy(std::begin(range), std::end(range), std::move(out), old, val, std::move(p));
    }


    //******************** replace_copy_n *************************

    template<std::input_iterator Iter,
	typename Old, typename New,
	std::output_iterator<const New&> Out,
	typename Proj = std::identity>
    requires std::indirectly_copyable<Iter, Out> &&
	std::indirect_binary_predicate<std::ranges::equal_to,
	    std::projected<Iter, Proj>,
	    const Old*>
    constexpr auto replace_copy_n(Iter left, std::iter_difference_t<Iter> n,
	    Out out, const Old& old, const New& val, Proj p = {})
	-> std::ranges::in_out_result<Iter, Out>
    {
	for(std::iter_difference_t<Iter> i{}; i != n; ++i, ++left, ++out)
	    *out = (old == std::invoke(p, *left)) ? val : *left;

	return {std::move(left), std::move(out)};
    }

    template<std::ranges::input_range Range,
	typename Old, typename New,
	std::output_iterator<const New&> Out,
	typename Proj = std::identity>
    requires std::indirectly_copyable<std::ranges::iterator_t<Range>, Out> &&
	std::indirect_binary_predicate<std::ranges::equal_to,
	    std::projected<std::ranges::iterator_t<Range>, Proj>,
	    const Old*>
    constexpr auto replace_copy_n(Range&& range, std::ranges::range_difference_t<Range> n,
	    Out out, const Old& old, const New& val, Proj p = {})
	-> std::ranges::in_out_result<std::ranges::borrowed_iterator_t<Range>, Out>
    {
	return ::alg::replace_copy_n(std::begin(range), std::move(n), std::move(out), old, val, std::move(p));
    }


    //******************* replace_copy_if *************************

    template<std::input_iterator Iter, std::sentinel_for<Iter> Sent,
	typename New,
	std::output_iterator<const New&> Out,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<Iter, Proj>> Pred>
    requires std::indirectly_copyable<Iter, Out>
    constexpr auto replace_copy_if(Iter left, Sent right, Out out, Pred f, const New& val, Proj p = {})
	-> std::ranges::in_out_result<Iter, Out>
    {
	for(; left != right; ++left, ++out)
	    *out = std::invoke(f, std::invoke(p, *left)) ? val : *left;

	return {std::move(left), std::move(out)};
    }

    template<std::ranges::input_range Range,
	typename New,
	std::output_iterator<const New&> Out,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<std::ranges::iterator_t<Range>, Proj>> Pred>
    requires std::indirectly_copyable<std::ranges::iterator_t<Range>, Out>
    constexpr auto replace_copy_if(Range&& range, Out out, Pred f, const New& val, Proj p = {})
	-> std::ranges::in_out_result<std::ranges::borrowed_iterator_t<Range>, Out>
    {
	return ::alg::replace_copy_if(std::begin(range), std::end(range), std::move(out), std::move(f), val, std::move(p));
    }


    //****************** replace_copy_if_n ************************

    template<std::input_iterator Iter,
	typename New,
	std::output_iterator<const New&> Out,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<Iter, Proj>> Pred>
    requires std::indirectly_copyable<Iter, Out>
    constexpr auto replace_copy_if_n(Iter left, std::iter_difference_t<Iter> n,
	    Out out, Pred f, const New& val, Proj p = {})
	-> std::ranges::in_out_result<Iter, Out>
    {
	for(std::iter_difference_t<Iter> i{}; i != n; ++i, ++left, ++out)
	    *out = std::invoke(f, std::invoke(p, *left)) ? val : *left;

	return {std::move(left), std::move(out)};
    }

    template<std::ranges::input_range Range,
	typename New,
	std::output_iterator<const New&> Out,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<std::ranges::iterator_t<Range>, Proj>> Pred>
    requires std::indirectly_copyable<std::ranges::iterator_t<Range>, Out>
    constexpr auto replace_copy_if_n(Range&& range, std::ranges::range_difference_t<Range> n,
	    Out out, Pred f, const New& val, Proj p = {})
	-> std::ranges::in_out_result<std::ranges::borrowed_iterator_t<Range>, Out>
    {
	return ::alg::replace_copy_if_n(std::begin(range), std::move(n), std::move(out), std::move(f), val, std::move(p));
    }

    
    //********************* swap_ranges ***************************

    template<std::input_iterator Iter1, std::sentinel_for<Iter1> Sent1,
	std::input_iterator Iter2, std::sentinel_for<Iter2> Sent2>
    requires std::indirectly_swappable<Iter1, Iter2>
    constexpr auto swap_ranges(Iter1 left1, Sent1 right1, Iter2 left2, Sent2 right2)
	-> std::ranges::in_in_result<Iter1, Iter2>
    {
	for(; left1 != right1 && left2 != right2; ++left1, ++left2)
	    ::alg::iter_swap(left1, left2);

	return {std::move(left1), std::move(left2)};
    }

    template<std::ranges::input_range Range1, std::ranges::input_range Range2>
    requires std::indirectly_swappable<
	std::ranges::iterator_t<Range1>,
	std::ranges::iterator_t<Range2>>
    constexpr auto swap_ranges(Range1&& range1, Range2&& range2)
	-> std::ranges::in_in_result<
	    std::ranges::borrowed_iterator_t<Range1>,
	    std::ranges::borrowed_iterator_t<Range2>>
    {
	return swap_ranges(std::begin(range1), std::end(range1), std::begin(range2), std::end(range2));
    }
    

    //*********************** reverse *****************************

    template<std::bidirectional_iterator Iter, std::sentinel_for<Iter> Sent>
    requires std::permutable<Iter>
    constexpr auto reverse(Iter left, Sent right) -> Iter
    {
	auto last{std::ranges::next(left, right)};

	for(auto tail{last}; left != tail && left != --tail; ++left)
	    ::alg::iter_swap(left, tail);

	return last;
    }

    template<std::ranges::bidirectional_range Range>
    requires std::permutable<std::ranges::iterator_t<Range>>
    constexpr auto reverse(Range&& range) -> std::ranges::borrowed_iterator_t<Range>
    {
	return ::alg::reverse(std::begin(range), std::end(range));
    }


    //*********************** reverse_n *****************************

    template<std::bidirectional_iterator Iter>
    requires std::permutable<Iter>
    constexpr auto reverse_n(Iter left, std::iter_difference_t<Iter> n) -> Iter
    {
	auto last{std::ranges::next(left, n)};

	for(auto tail{last}; left != tail && left != --tail; ++left)
	    ::alg::iter_swap(left, tail);

	return last;
    }

    template<std::ranges::bidirectional_range Range>
    requires std::permutable<std::ranges::iterator_t<Range>>
    constexpr auto reverse_n(Range&& range, std::ranges::range_difference_t<Range> n) -> std::ranges::borrowed_iterator_t<Range>
    {
	return ::alg::reverse_n(std::begin(range), std::move(n));
    }


    //********************* reverse_copy **************************

    template<std::bidirectional_iterator Iter, std::sentinel_for<Iter> Sent,
	std::weakly_incrementable Out>
    requires std::indirectly_copyable<Iter, Out>
    constexpr auto reverse_copy(Iter left, Sent right, Out out) -> std::ranges::in_out_result<Iter, Out>
    {
	auto last{std::ranges::next(left, right)};

	for(; right != left; *out++ = *--right);

	return {std::move(last), std::move(out)};
    }


    template<std::ranges::bidirectional_range Range,
	std::weakly_incrementable Out>
    requires std::indirectly_copyable<std::ranges::iterator_t<Range>, Out>
    constexpr auto reverse_copy(Range&& range, Out out) 
	-> std::ranges::in_out_result<std::ranges::iterator_t<Range>, Out>
    {
	return ::alg::reverse_copy(std::begin(range), std::end(range), std::move(out));
    }

    
    //******************** reverse_copy_n *************************

    template<std::bidirectional_iterator Iter,
	std::weakly_incrementable Out>
    requires std::indirectly_copyable<Iter, Out>
    constexpr auto reverse_copy_n(Iter left, std::iter_difference_t<Iter> n, Out out)
	-> std::ranges::in_out_result<Iter, Out>
    {
	auto last{std::ranges::next(left, n)};

	for(auto right{last}; right != left; *out++ = *--right);

	return {std::move(last), std::move(out)};
    }


    template<std::ranges::bidirectional_range Range,
	std::weakly_incrementable Out>
    requires std::indirectly_copyable<std::ranges::iterator_t<Range>, Out>
    constexpr auto reverse_copy_n(Range&& range, std::ranges::range_difference_t<Range> n, Out out) 
	-> std::ranges::in_out_result<std::ranges::iterator_t<Range>, Out>
    {
	return ::alg::reverse_copy_n(std::begin(range), std::move(n), std::move(out));
    }


    //************************ shuffle *****************************

    template<std::random_access_iterator Iter, std::sentinel_for<Iter> Sent,
	typename Gen>
    requires std::permutable<Iter> && 
	std::uniform_random_bit_generator<std::remove_reference_t<Gen>>
    constexpr auto shuffle(Iter left, Sent right, Gen&& gen) -> Iter
    {
	using diff_t = std::iter_difference_t<Iter>;
	using distr_t = std::uniform_int_distribution<diff_t>;
	using param_t = typename distr_t::param_type;

	distr_t distr;
	const auto n{std::distance(left, right)};
	for(diff_t i{1}; i < n; ++i)
	    ::alg::iter_swap(left + i, left + distr(gen, param_t{0, i}));

	return std::ranges::next(left, right);
    }

    template<std::ranges::random_access_range Range,
	typename Gen>
    requires std::permutable<std::ranges::iterator_t<Range>> && 
	std::uniform_random_bit_generator<std::remove_reference_t<Gen>>
    constexpr auto shuffle(Range&& range, Gen&& gen) -> std::ranges::borrowed_iterator_t<Range>
    {
	return ::alg::shuffle(std::begin(range), std::end(range), std::forward<Gen>(gen));
    }


    //************************* sample *****************************

    template<std::input_iterator Iter, std::sentinel_for<Iter> Sent,
	std::weakly_incrementable Out, typename Gen>
    requires (std::forward_iterator<Iter> ||
	    std::random_access_iterator<Out>) &&
	std::indirectly_copyable<Iter, Out> &&
	std::uniform_random_bit_generator<std::remove_reference_t<Gen>>
    constexpr auto sample(Iter left, Sent right, Out out, std::iter_difference_t<Iter> n, Gen&& gen) -> Out
    {
	using diff_t = std::iter_difference_t<Iter>;
	using distr_t = std::uniform_int_distribution<diff_t>;
	using param_t = typename distr_t::param_type;

	distr_t distr;

	if constexpr(std::forward_iterator<Iter>) {

	    auto rest{std::distance(left, right)};    
	    for(n = min(n, rest); n != 0; ++left)
		if(distr(gen, param_t{0, --rest}) < n) {
		    *out++ = *left;
		    --n;
		}

	    return out;

	} else {

	    diff_t sample_s{};

	    for(; left != right && sample_s != n; ++left)
		out[sample_s++] = *left;

	    for(auto pop_s{sample_s}; left != right; ++left, ++pop_s)
		if(const auto i{distr(gen, param_t{0, pop_s})}; i < n)
		    out[i] = *left;

	    return out + sample_s;

	}
    }

    template<std::ranges::input_range Range,
	std::weakly_incrementable Out, typename Gen>
    requires (std::forward_iterator<std::ranges::iterator_t<Range>> ||
	    std::random_access_iterator<Out>) &&
	std::indirectly_copyable<std::ranges::iterator_t<Range>, Out> &&
	std::uniform_random_bit_generator<std::remove_reference_t<Gen>>
    constexpr auto sample(Range&& range, Out out, std::ranges::range_difference_t<Range> n, Gen&& gen) -> Out
    {
	return ::alg::sample(std::begin(range), std::end(range), std::move(out), n, std::forward<Gen>(gen));
    }


    //************************* unique *****************************

    template<std::permutable Iter, std::sentinel_for<Iter> Sent,
	typename Proj = std::identity,
	std::indirect_equivalence_relation<std::projected<Iter, Proj>> Comp = std::ranges::equal_to>
    constexpr auto unique(Iter left, Sent right, Comp f = {}, Proj p = {}) -> std::ranges::subrange<Iter>
    {
	left = adjacent_find(left, right, f, p);
	if(left == right)
	    return {left, left};

	auto i{left++};
	while(++left != right)
	    if(!std::invoke(f, std::invoke(p, *i), std::invoke(p, *left)))
		*++i = std::ranges::iter_move(left);

	return {++i, left};
    }

    template<std::ranges::forward_range Range,
	typename Proj = std::identity,
	std::indirect_equivalence_relation<
	    std::projected<std::ranges::iterator_t<Range>, Proj>
	    > Comp = std::ranges::equal_to>
    constexpr auto unique(Range&& range, Comp f = {}, Proj p = {}) -> std::ranges::borrowed_subrange_t<Range>
    {
	return ::alg::unique(std::begin(range), std::end(range), std::move(f), std::move(p));
    }


    //********************** unique_copy ***************************

    template<std::input_iterator Iter, std::sentinel_for<Iter> Sent,
	std::weakly_incrementable Out, typename Proj = std::identity,
	std::indirect_equivalence_relation<std::projected<Iter, Proj>> Comp = std::ranges::equal_to>
    requires std::indirectly_copyable<Iter, Out> && (std::forward_iterator<Iter> ||
	    (std::input_iterator<Out> && std::same_as<std::iter_value_t<Iter>, std::iter_value_t<Out>>) ||
	    std::indirectly_copyable_storable<Iter, Out>)
    constexpr auto unique_copy(Iter left, Sent right, Out out, Comp f = {}, Proj p = {}) -> std::ranges::in_out_result<Iter, Out>
    {
	if(left != right) {
	    auto val = *left;
	    *out++ = val;

	    while(++left != right) {
		auto&& next_val = *left;
		if(!std::invoke(f, std::invoke(p, next_val), std::invoke(p, val))) {
		    val = std::forward<decltype(next_val)>(next_val);
		    *out++ = val;
		}
	    }
	}
	return {std::move(left), std::move(out)};
    }

    template<std::ranges::input_range Range,
	std::weakly_incrementable Out, typename Proj = std::identity,
	std::indirect_equivalence_relation<
	    std::projected<std::ranges::iterator_t<Range>, Proj>
	    > Comp = std::ranges::equal_to>
    requires std::indirectly_copyable<std::ranges::iterator_t<Range>, Out> && 
	    (std::forward_iterator<std::ranges::iterator_t<Range>> ||
	    (std::input_iterator<Out> && std::same_as<std::iter_value_t<std::ranges::iterator_t<Range>>, std::iter_value_t<Out>>) ||
	    std::indirectly_copyable_storable<std::ranges::iterator_t<Range>, Out>)
    constexpr auto unique_copy(Range&& range, Out out, Comp f = {}, Proj p = {}) 
	-> std::ranges::in_out_result<std::ranges::borrowed_iterator_t<Range>, Out>
    {
	return ::alg::unique_copy(std::begin(range), std::end(range), std::move(out), std::move(f), std::move(p));
    }


    //************************ rotate ******************************

    template<std::permutable Iter, std::sentinel_for<Iter> Sent>
    constexpr auto rotate(Iter left, Iter middle, Sent right) -> std::ranges::subrange<Iter>
    {
	if(left == middle) {
	    auto last{std::ranges::next(left, right)};
	    return {last, last};
	}

	if(middle == right)
	    return {std::move(left), std::move(middle)};

	if constexpr(std::bidirectional_iterator<Iter>) {
	    ::alg::reverse(left, middle);
	    auto last{std::ranges::next(left, right)};
	    ::alg::reverse(middle, last);

	    if constexpr(std::random_access_iterator<Iter>) {
		::alg::reverse(left, last);
		return {left + (last - middle), std::move(last)};
	    } else { // !random_access_iterator<Iter>
		auto mid_last{last};
		do {
		    ::alg::iter_swap(left, --mid_last);
		    ++left;
		} while(left != middle && mid_last != middle);
		::alg::reverse(left, mid_last);

		if(left == middle)
		    return {std::move(mid_last), std::move(last)};
		else
		    return {std::move(left), std::move(last)};
	    }
	} else { // forward_iterator<Iter>
	    auto next{middle};
	    do {
		::alg::iter_swap(left, next);
		++left, ++next;
		if(left == middle)
		    middle = next;
	    } while(next != right);

	    auto new_left{left};
	    while(middle != right) {
		next = middle;
		do {
		    ::alg::iter_swap(left, next);
		    ++left, ++next;
		    if(left == middle)
			middle = next;
		} while(next != right);
	    }
	    return {std::move(new_left), std::move(middle)};
	}
    }

    template<std::ranges::forward_range Range>
    requires std::permutable<std::ranges::iterator_t<Range>>
    constexpr auto rotate(Range&& range, std::ranges::iterator_t<Range> middle) -> std::ranges::borrowed_subrange_t<Range>
    {
	return ::alg::rotate(std::begin(range), std::move(middle), std::end(range));
    }


    //********************** rotate_copy ***************************

    template<std::forward_iterator Iter, std::sentinel_for<Iter> Sent,
	std::weakly_incrementable Out>
    requires std::indirectly_copyable<Iter, Out>
    constexpr auto rotate_copy(Iter left, Iter middle, Sent right, Out out) -> std::ranges::in_out_result<Iter, Out>
    {
	auto copy1{::alg::copy(middle, std::move(right), std::move(out))};
	auto copy2{::alg::copy(std::move(left), std::move(middle), std::move(copy1.out))};
	return {std::move(copy1.in), std::move(copy2.out)};
    }

    template<std::ranges::forward_range Range, std::weakly_incrementable Out>
    requires std::indirectly_copyable<std::ranges::iterator_t<Range>, Out>
    constexpr auto rotate_copy(Range&& range, std::ranges::iterator_t<Range> middle, Out out)
	-> std::ranges::in_out_result<std::ranges::iterator_t<Range>, Out>
    {
	return ::alg::rotate_copy(std::begin(range), std::move(middle), std::end(range), std::move(out));
    }


    //********************** shift_left ***************************

    template<std::permutable Iter, std::sentinel_for<Iter> Sent>
    constexpr auto shift_left(Iter left, Sent right, std::iter_difference_t<Iter> n)
	-> std::ranges::subrange<Iter> 
    {
	if(n >= std::distance(left, right) || !n)
	    return {left, left};

	auto beginning{std::ranges::next(left, n)};

	auto ret = ::alg::move(beginning, std::move(right), left);

	return {std::move(left), std::move(ret.out)};
    }

    template<std::ranges::forward_range Range>
    requires std::permutable<std::ranges::iterator_t<Range>>
    constexpr auto shift_left(Range&& range, std::ranges::range_difference_t<Range> n)
	-> std::ranges::borrowed_subrange_t<Range>
    {
	return ::alg::shift_left(std::begin(range), std::end(range), std::move(n));
    }


    //********************** shift_right ***************************

    template<std::forward_iterator Iter, std::sentinel_for<Iter> Sent>
    requires std::permutable<Iter>
    constexpr auto shift_right(Iter left, Sent right, std::iter_difference_t<Iter> n)
	-> std::ranges::subrange<Iter>
    {
	if(!n)
	    return {left, right};

	if constexpr(std::bidirectional_iterator<Iter>) {
	    auto len{std::distance(left, right)};

	    if(n >= len)
	        return {right, right};

	    auto ending{std::ranges::next(left, len - n)};
	    auto beginning = std::ranges::next(left, right);
	    auto ret = ::alg::move_backwards(std::move(left), std::move(ending), beginning);
	    return {std::move(ret.out), std::move(right)};
	} else { // forward_iterator<Iter>
	    Iter middle{left};
	    for(std::iter_difference_t<Iter> i{}; i != n && middle != right; ++i, ++middle);

	    if(middle == right || ++middle == right)
		return {std::move(left), std::move(middle)};

	    return ::alg::rotate(std::move(left), std::move(middle), std::move(right)); 
	}
    }

    template<std::ranges::forward_range Range>
    requires std::permutable<std::ranges::iterator_t<Range>>
    constexpr auto shift_right(Range&& range, std::ranges::range_difference_t<Range> n)
	-> std::ranges::borrowed_subrange_t<Range>
    {
	return ::alg::shift_right(std::begin(range), std::end(range), std::move(n));
    }


}
