#pragma once

#include <concepts>
#include <compare>
#include <functional>


namespace concepts 
{

    template<typename T, typename... U>
    concept any_of = (std::same_as<T, U> || ...);

    template<typename T>
    concept three_way_comparison_result = any_of<T, std::strong_ordering, 
						       std::weak_ordering,
						       std::partial_ordering>;

    template<typename F, typename... Args>
    concept three_way_predicate = 
	std::regular_invocable<F, Args...> &&
	three_way_comparison_result<std::invoke_result_t<F, Args...>>;

    template<typename F, typename I1, typename I2>
    concept indirect_three_way_binary_predicate = 
	std::indirectly_readable<I1> &&
	std::indirectly_readable<I2> &&
	std::copy_constructible<F> &&
	three_way_predicate<F&, std::iter_value_t<I1>&, std::iter_value_t<I2>&> &&
	three_way_predicate<F&, std::iter_value_t<I1>&, std::iter_reference_t<I2>> &&
	three_way_predicate<F&, std::iter_reference_t<I1>, std::iter_value_t<I2>&> &&
	three_way_predicate<F&, std::iter_reference_t<I1>, std::iter_reference_t<I2>> &&
	three_way_predicate<F&, std::iter_common_reference_t<I1>, std::iter_common_reference_t<I2>>;
	

    template<typename Iter1, typename Iter2, typename Comp,
	typename Proj1 = std::identity, typename Proj2 = std::identity>
    concept indirectly_comparable_three_way = 
	indirect_three_way_binary_predicate<Comp,
	    std::projected<Iter1, Proj1>,
	    std::projected<Iter2, Proj2>>;

}
