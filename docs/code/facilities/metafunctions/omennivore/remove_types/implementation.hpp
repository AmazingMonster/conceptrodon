/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/**** Prefix ****/
template<typename, size_t>
concept Prefix = true;

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** ExtendFront ****/
template<typename...>
struct ExtendFront {};

template<template<typename...> class Container, typename...Elements>
struct ExtendFront<Container<Elements...>>
{
    template<typename...NewElements>
    using Mold = Container<NewElements..., Elements...>;
};

/************************/
/**** Implementation ****/
/************************/

template<typename...>
struct RemoveTypes {};

/**** Base Case ****/
template<auto...I>
struct RemoveTypes<std::index_sequence<I...>>
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
    -> Capsule
    <
        FrontTargets...,
        BackTargets...
    >;

    template<typename...Agreements>
    using Mold = decltype(idyl<Agreements...>());
};

template<auto...I, auto...J>
struct RemoveTypes<std::index_sequence<I...>, std::index_sequence<J...>>
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
    -> Capsule
    <
        FrontTargets...,
        MiddleTargets...,
        BackTargets...
    >;

    template<typename...Agreements>
    using Mold = decltype(idyl<Agreements...>());
};

/**** Recursive Case ****/
template<auto...I, auto...J, typename...OtherSequences>
struct RemoveTypes<std::index_sequence<I...>, std::index_sequence<J...>, OtherSequences...>
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
        typename RemoveTypes<OtherSequences...>
        ::template Mold<BackTargets...>
    >
    ::template Mold
    <
        FrontTargets...,
        MiddleTargets...
    >;

    template<typename...Agreements>
    using Mold = decltype(idyl<Agreements...>());
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = RemoveTypes
<
    std::make_index_sequence<1>,
    std::make_index_sequence<3-1-1>,
    std::make_index_sequence<5-3-1>
>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Capsule<Vay<0>, Vay<2>, Vay<4>>;

/**** Result ****/
using Result = Metafunction<Vay<0>, Vay<-1>, Vay<2>, Vay<-3>, Vay<4>, Vay<-5>>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);