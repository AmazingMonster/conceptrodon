/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/**** ExtendFront ****/
template<typename...>
struct ExtendFront {};

template<template<auto...> class Sequence, auto...Variables>
struct ExtendFront<Sequence<Variables...>>
{
    template<auto...NewVariables>
    using Page = Sequence<NewVariables..., Variables...>;
};

/**** Vay ****/
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };

/**** Prefix ****/
template<typename, size_t>
concept Prefix = true;

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/************************/
/**** Implementation ****/
/************************/

template<typename...>
struct RemoveValues {};

/**** Base Case ****/
template<auto...I>
struct RemoveValues<std::index_sequence<I...>>
{
    template
    <
        // We use `Prefix<I>...` to enumerate `FrontTargets`.
        Prefix<I>...FrontTargets,
        // We drop the next argument.
        typename,
        typename...BackTargets
    >
    static consteval auto idyl()
    // Note that `Shuttle` is instantiated by values
    // extracted from the template parameters.
    // This is because we will pack every variable
    // into `Vay`.
    -> Shuttle
    <
        FrontTargets::value...,
        BackTargets::value...
    >;

    template<auto...Agreements>
    using Page = decltype(idyl<Vay<Agreements>...>());
};

template<auto...I, auto...J>
struct RemoveValues<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template
    <
        // We use `Prefix<I>...` to enumerate `FrontTargets`.
        Prefix<I>...FrontTargets,
        // We drop the next argument.
        typename,
        // We use `Prefix<J>...` to go across the distance
        // between two targets.
        Prefix<J>...MiddleTargets,
        // We drop the next argument.
        typename,
        typename...BackTargets
    >
    static consteval auto idyl()
    -> Shuttle
    <
        FrontTargets::value...,
        MiddleTargets::value...,
        BackTargets::value...
    >;

    template<auto...Agreements>
    using Page = decltype(idyl<Vay<Agreements>...>());
};

/**** Recursive Case ****/
template<auto...I, auto...J, typename...OtherSequences>
struct RemoveValues<std::index_sequence<I...>, std::index_sequence<J...>, OtherSequences...>
{
    template
    <
        // We use `Prefix<I>...` to enumerate `FrontTargets`.
        Prefix<I>...FrontTargets,
        // We drop the next argument.
        typename,
        // We use `Prefix<J>...` to go across the distance
        // between two targets.
        Prefix<J>...MiddleTargets,
        // We drop the next argument.
        typename,
        typename...BackTargets
    >
    static consteval auto idyl()
    -> ExtendFront
    <
        typename RemoveValues<OtherSequences...>
        ::template Page<BackTargets::value...>
    >
    ::template Page
    <
        FrontTargets::value...,
        MiddleTargets::value...
    >;

    template<auto...Agreements>
    using Page = decltype(idyl<Vay<Agreements>...>());
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = RemoveValues
<
    std::make_index_sequence<1>,
    std::make_index_sequence<3-1-1>,
    std::make_index_sequence<5-3-1>
>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Shuttle<0, 2, 4>;

/**** Result ****/
using Result = Metafunction<0, -1, 2, -3, 4, -5>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);