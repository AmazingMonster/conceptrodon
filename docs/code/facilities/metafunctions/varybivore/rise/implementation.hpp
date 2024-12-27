/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>
#include <algorithm>
#include <array>

/************************/
/**** Implementation ****/
/************************/

/**** arise ****/
template<template<auto...> class Operation, auto...Variables>
static consteval auto arise()
{    
    // `std::index_sequence<I...>` is created
    // for the length of `Variables...`.
    return []<size_t...I>(std::index_sequence<I...>)
    {
        constexpr auto sorted = []()
        {
            std::array original {Variables...};
            // `original` will be reused for the result.
            std::ranges::sort(original);
            return original;
        }();
        // We use `std::type_identity` to avoid construct
        // an object of type `Operation<*>`.
        return std::type_identity<Operation<sorted.at(I)...>> {};
    }(std::make_index_sequence<sizeof...(Variables)>{});
};

/**** Rise ****/
template<auto...Variables>
struct Rise
{
    template<template<auto...> class...Agreements>
    using Rail = decltype
    (arise<Agreements..., Variables...>())::type;
};

/*****************/
/**** Example ****/
/*****************/

/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 1, 2, 2>;

/**** Result ****/
using Result = Rise<0, 1, 2, 2>::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);