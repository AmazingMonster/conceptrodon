/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <array>
#include <algorithm>

/**** Tyy ****/
template<typename Element>
struct Tyy
{
    using type = Element;
};

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
        // We use `Tyy` to avoid construct
        // an object of type `Operation<*>`.
        return Tyy<Operation<sorted.at(I)...>> {};
    }(std::make_index_sequence<sizeof...(Variables)>{});
};

/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class Operation>
struct CognateRise
{
    template<auto...Variables>
    using Page = decltype(arise<Operation, Variables...>())
    ::type;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 1, 2, 2>;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = CognateRise<Operation>
::Page<Args...>;

/**** Result ****/
using Result = Metafunction<0, 1, 2, 2>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);