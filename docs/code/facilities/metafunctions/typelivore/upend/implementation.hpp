/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/**** Label ****/
template<typename Treasure, typename Key>
struct Label
{  static constexpr auto idyl(Key) -> Treasure; };

/************************/
/**** Implementation ****/
/************************/

template<typename...Elements>
struct Upend
{
    template<template<typename...> class, typename>
    struct Detail {};

    template<template<typename...> class Operation, size_t...I>
    struct Detail<Operation, std::index_sequence<I...>>
    // We create an overload set of `idyl` through inheritance.
    : public Label<Elements, std::integral_constant<size_t, I>>...
    {
        using Label<Elements, std::integral_constant<size_t, I>>::idyl...;
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
            )...
        >;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements..., std::make_index_sequence<sizeof...(Elements)>>::type;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int**, int**, int*, int>;

/**** Result ****/
using Result = Upend<int, int*, int**, int**>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);