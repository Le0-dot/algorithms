#pragma once

#include <functional>
#include <ranges>
#include <iterator>
#include <algorithm>

namespace alg
{

    //******************** copy ***********************

    template<std::input_iterator Iter, std::sentinel_for<Iter> Sent,
	std::weakly_incrementable Out>
    requires std::indirectly_copyable<Iter, Out>
    constexpr auto copy(Iter left, Sent right, Out out)
	-> std::ranges::in_out_result<Iter, Out>
    {
	for(; left != right; ++left, ++out) {
	    printf("%d", *left);
	    *out = *left;
	}

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
	for(std::iter_difference_t<Iter> i{}; i != n; ++left, ++out, ++i)
	    *out = *left;

	return {std::move(left), std::move(out)};
    }

    template<std::ranges::input_range Range,
	std::weakly_incrementable Out>
    requires std::indirectly_copyable<std::ranges::iterator_t<Range>, Out>
    constexpr auto copy_n(Range&& range, std::iter_difference_t<std::ranges::iterator_t<Range>> n, Out out)
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
		*out = *left;
		++out;
		++i;
	    }

	return {std::move(left), std::move(out)};
    }

    template<std::ranges::input_range Range,
	std::weakly_incrementable Out,
	typename Proj = std::identity,
	std::indirect_unary_predicate<std::projected<std::ranges::iterator_t<Range>, Proj>> Pred>
    requires std::indirectly_copyable<std::ranges::iterator_t<Range>, Out>
    constexpr auto copy_if_n(Range&& range, std::iter_difference_t<std::ranges::iterator_t<Range>> n,
	    Out out, Pred f, Proj p = {})
	-> std::ranges::in_out_result<std::ranges::borrowed_iterator_t<Range>, Out>
    {
	return copy_if_n(std::begin(range), std::move(n), std::move(out), std::ref(f), std::ref(p));
    }


}
