#pragma once

#include <iterator>
#include <ranges>
#include <functional>
#include <algorithm>

namespace alg
{

    //**************** max_element ********************

    template<std::forward_iterator Iter, std::sentinel_for<Iter> Sent,
	typename Proj = std::identity,
	std::indirect_strict_weak_order<
	    std::projected<Iter, Proj>> Comp = std::ranges::less>
    [[nodiscard]] constexpr auto max_element(Iter left, Sent right, Comp f = {}, Proj p = {}) -> Iter
    {
	if(left == right)
	    return right;

	auto biggest = left++;
	for(; left != right; ++left)
	    if(std::invoke(f, std::invoke(p, *biggest), std::invoke(p, *left)))
		biggest = left;

	return biggest;
    }

    template<std::ranges::forward_range Range,
	typename Proj = std::identity,
	std::indirect_strict_weak_order<
	    std::projected<std::ranges::iterator_t<Range>, Proj>> Comp = std::ranges::less>
    [[nodiscard]] constexpr auto max_element(Range&& range, Comp f = {}, Proj p = {})
	-> std::ranges::borrowed_iterator_t<Range>
    {
	return max_element(std::begin(range), std::end(range), std::ref(f), std::ref(p));
    }


    //******************** max ************************

    template<typename T,
	typename Proj = std::identity,
	std::indirect_strict_weak_order<
	    std::projected<const T*, Proj>> Comp = std::ranges::less>
    [[nodiscard]] constexpr auto max(const T& a, const T& b, Comp f = {}, Proj p = {})
	-> const T&
    {
	return std::invoke(f, std::invoke(p, a), std::invoke(p, b)) ? b : a;
    }

    template<std::copyable T,
	typename Proj = std::identity,
	std::indirect_strict_weak_order<
	    std::projected<const T*, Proj>> Comp = std::ranges::less>
    [[nodiscard]] constexpr auto max(std::initializer_list<T> list, Comp f = {}, Proj p = {})
	-> T
    {
	return *max_element(list, std::ref(f), std::ref(p));
    }

    template<std::ranges::input_range Range,
	typename Proj = std::identity,
	std::indirect_strict_weak_order<
	    std::projected<std::ranges::iterator_t<Range>, Proj>> Comp = std::ranges::less>
    requires std::indirectly_copyable_storable<std::ranges::iterator_t<Range>,
	std::ranges::range_value_t<Range>*>
    [[nodiscard]] constexpr auto max(Range&& range, Comp f = {}, Proj p = {})
	-> std::ranges::range_value_t<Range>
    {
	using val_t = std::ranges::range_value_t<Range>;
	if constexpr(std::ranges::forward_range<Range>)
	    return static_cast<val_t>(*max_element(range, std::ref(f), std::ref(p)));

	auto l = std::begin(range);
	auto r = std::end(range);
	val_t v{*l};
	while(++l != r)
	    if(std::invoke(f, std::invoke(p, v), std::invoke(p, *l)))
		v = *l;

	return v;
    }


    //**************** min_element ********************

    template<std::forward_iterator Iter, std::sentinel_for<Iter> Sent,
	typename Proj = std::identity,
	std::indirect_strict_weak_order<
	    std::projected<Iter, Proj>> Comp = std::ranges::less>
    [[nodiscard]] constexpr auto min_element(Iter left, Sent right, Comp f = {}, Proj p = {})
	-> Iter
    {
	if(left == right)
	    return right;

	auto smallest = left++;
	for(; left != right; ++left)
	    if(!std::invoke(f, std::invoke(p, *smallest), std::invoke(p, *left)))
		smallest = left;

	return smallest;
    }

    template<std::ranges::forward_range Range,
	typename Proj = std::identity,
	std::indirect_strict_weak_order<
	    std::projected<std::ranges::iterator_t<Range>, Proj>> Comp = std::ranges::less>
    [[nodiscard]] constexpr auto min_element(Range&& range, Comp f = {}, Proj p = {})
	-> std::ranges::borrowed_iterator_t<Range>
    {
	return min_element(std::begin(range), std::end(range), std::ref(f), std::ref(p));
    }


    //******************** min ************************

    template<typename T,
	typename Proj = std::identity,
	std::indirect_strict_weak_order<
	    std::projected<const T*, Proj>> Comp = std::ranges::less>
    [[nodiscard]] constexpr auto min(const T& a, const T& b, Comp f = {}, Proj p = {})
	-> const T&
    {
	return std::invoke(f, std::invoke(p, a), std::invoke(p, b)) ? a : b;
    }

    template<std::copyable T,
	typename Proj = std::identity,
	std::indirect_strict_weak_order<
	    std::projected<const T*, Proj>> Comp = std::ranges::less>
    [[nodiscard]] constexpr auto min(std::initializer_list<T> list, Comp f = {}, Proj p = {})
	-> T
    {
	return *min_element(list, std::ref(f), std::ref(p));
    }

    template<std::ranges::input_range Range,
	typename Proj = std::identity,
	std::indirect_strict_weak_order<
	    std::projected<std::ranges::iterator_t<Range>, Proj>> Comp = std::ranges::less>
    requires std::indirectly_copyable_storable<std::ranges::iterator_t<Range>,
	std::ranges::range_value_t<Range>*>
    [[nodiscard]] constexpr auto min(Range&& range, Comp f = {}, Proj p = {})
	-> std::ranges::range_value_t<Range>
    {
	using val_t = std::ranges::range_value_t<Range>;
	if constexpr(std::ranges::forward_range<Range>)
	    return static_cast<val_t>(*min_element(range, std::ref(f), std::ref(p)));

	auto l = std::begin(range);
	auto r = std::end(range);
	val_t v{*l};
	while(++l != r)
	    if(!std::invoke(f, std::invoke(p, v), std::invoke(p, *l)))
		v = *l;

	return v;
    }


    //************** minmax_element *******************

    template<std::forward_iterator Iter, std::sentinel_for<Iter> Sent,
	typename Proj = std::identity,
	std::indirect_strict_weak_order<
	    std::projected<Iter, Proj>> Comp = std::ranges::less>
    [[nodiscard]] constexpr auto minmax_element(Iter left, Sent right, Comp f = {}, Proj p = {})
	-> std::ranges::minmax_result<Iter>
    {
	auto min = left, max = left;

	for(; left != right; ++left) {
	    if(std::invoke(f, std::invoke(p, *left), std::invoke(p, *min)))
		min = left;
	    else if(!std::invoke(f, std::invoke(p, *left), std::invoke(p, *max)))
		max = left;
	}

	return {min, max};
    }

    template<std::ranges::forward_range Range,
	typename Proj = std::identity,
	std::indirect_strict_weak_order<
	    std::projected<std::ranges::iterator_t<Range>, Proj>> Comp = std::ranges::less>
    [[nodiscard]] constexpr auto minmax_element(Range&& range, Comp f = {}, Proj p = {})
	-> std::ranges::minmax_result<std::ranges::borrowed_iterator_t<Range>>
    {
	return minmax_element(std::begin(range), std::end(range), std::ref(f), std::ref(p));
    }

    
    //******************* minmax **********************

    template<typename T,
	typename Proj = std::identity,
	std::indirect_strict_weak_order<
	    std::projected<const T*, Proj>> Comp = std::ranges::less>
    [[nodiscard]] constexpr auto minmax(const T& a, const T& b, Comp f = {}, Proj p = {})
	-> std::ranges::minmax_result<const T&>
    {
	if(std::invoke(f, std::invoke(p, a), std::invoke(p, b)))
	    return {a, b};
	return {b, a};
    }

    template<std::copyable T,
	typename Proj = std::identity,
	std::indirect_strict_weak_order<
	    std::projected<const T*, Proj>> Comp = std::ranges::less>
    [[nodiscard]] constexpr auto minmax(std::initializer_list<T> list, Comp f = {}, Proj p = {})
	-> std::ranges::minmax_result<T>
    {
	auto result = minmax_element(list, std::ref(f), std::ref(p));
	return {*result.min, *result.max};
    }

    template<std::ranges::input_range Range,
	typename Proj = std::identity,
	std::indirect_strict_weak_order<
	    std::projected<std::ranges::iterator_t<Range>, Proj>> Comp = std::ranges::less>
    requires std::indirectly_copyable_storable<std::ranges::iterator_t<Range>,
	std::ranges::range_value_t<Range>*>
    [[nodiscard]] constexpr auto minmax(Range&& range, Comp f = {}, Proj p = {})
	-> std::ranges::minmax_result<std::ranges::range_value_t<Range>>
    {
	auto result = minmax_element(range, std::ref(f), std::ref(p));
	return {std::move(*result.min), std::move(*result.max)};
    }


    //******************* clamp ***********************

    template<typename T, 
	typename Proj = std::identity,
	std::indirect_strict_weak_order<std::projected<const T*, Proj>> Comp = std::ranges::less>
    [[nodiscard]] constexpr auto clamp(const T& v, const T& l, const T& h, Comp f = {}, Proj p = {})
    {
	auto&& pv = std::invoke(p, v);

	return std::invoke(f, std::forward<decltype(pv)>(pv), std::invoke(p, l)) ? l
	     : std::invoke(f, std::invoke(p, h), std::forward<decltype(pv)>(pv)) ? h
	     : v;
    }


}
