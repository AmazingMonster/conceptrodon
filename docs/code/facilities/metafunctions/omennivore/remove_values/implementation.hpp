/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>

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
template<typename, auto>
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
    template<typename...BackArgs>
    static consteval auto idyl
    (
        // Expand `Prefix<I>...` to reach the unwanted item.
        Prefix<I> auto...front_args,
        // Remove the next argument.
        auto,
        // Collect the rest arguments.
        BackArgs...
    )
    -> Shuttle
    <
        decltype(front_args)::value...,
        BackArgs::value...
    >;

    template<auto...Agreements>
    using Page = decltype(idyl(Vay<Agreements>{}...));
};

template<auto...I, auto...J>
struct RemoveValues<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<typename...BackArgs>
    static consteval auto idyl
    (
        // Expand `Prefix<I>...` to reach the first unwanted item.
        Prefix<I> auto...front_args,
        // Remove the next argument.
        auto,
        // Expand `Prefix<I>...` to reach the second unwanted item.
        Prefix<J> auto...middle_args,
        // Remove the next argument.
        auto,
        // Collect the rest arguments.
        BackArgs...
    )
    -> Shuttle
    <
        decltype(front_args)::value...,
        decltype(middle_args)::value...,
        BackArgs::value...
    >;

    template<auto...Agreements>
    using Page = decltype(idyl(Vay<Agreements>{}...));
};

/**** Recursive Case ****/
template<auto...I, auto...J, typename...OtherSequences>
struct RemoveValues<std::index_sequence<I...>, std::index_sequence<J...>, OtherSequences...>
{
    template<typename...BackArgs>
    static consteval auto idyl
    (
        // Expand `Prefix<I>...` to reach the first unwanted item.
        Prefix<I> auto...front_args,
        // Remove the next argument.
        auto,
        // Expand `Prefix<I>...` to reach the second unwanted item.
        Prefix<J> auto...middle_args,
        // Remove the next argument.
        auto,
        // Collect the rest arguments.
        BackArgs...
    )
    -> ExtendFront
    <
        decltype
        (
            RemoveValues<OtherSequences...>
            ::idyl(BackArgs{}...)
        )
    >
    ::template Page
    <
        decltype(front_args)::value...,
        decltype(middle_args)::value...
    >;

    template<auto...Agreements>
    using Page = decltype(idyl<>(Vay<Agreements>{}...));
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