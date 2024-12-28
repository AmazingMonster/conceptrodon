/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/**** Label ****/
template<typename Treasure, typename Key>
struct Label
{ 
    static constexpr auto idyl(Key) -> Treasure;
};

/**** Vay ****/
template<auto Variable>
struct Vay
{
    static constexpr auto value {Variable};
};

/************************/
/**** Implementation ****/
/************************/

template<auto...Variables>
struct Upend
{
    template<template<auto...> class, typename>
    struct Detail {};

    template<template<auto...> class Operation, size_t...I>
    struct Detail<Operation, std::index_sequence<I...>>
    // We create an overload set of `idyl` through inheritance.
    : public Label<Vay<Variables>, std::integral_constant<size_t, I>>...
    {
        using Label<Vay<Variables>, std::integral_constant<size_t, I>>::idyl...;
        using type = Operation<
            // Note that `sizeof...(I)` is the total number of I...,
            // which is a constant.
            // We are doing pack expansion over the second I.
            // The result is a list of form:
            // sizeof...(I) - 1, sizeof...(I) - 2, ..., 0. 
            decltype(
                idyl(
                    std::integral_constant
                    <size_t, sizeof...(I) - I - 1>{}
                )
            // We pull the value result out of `Vay`.
            )::value...
        >;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements..., std::make_index_sequence<sizeof...(Variables)>>::type;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Shuttle ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<2, 2, 1, 0>;

/**** Result ****/
using Result = Upend<0, 1, 2, 2>
::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);