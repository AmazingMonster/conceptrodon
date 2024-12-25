/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/**** Prefix ****/
template<typename, size_t>
concept Prefix = true;

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Vay ****/
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };

/**** ExtendFront ****/
template<typename...>
struct ExtendFront {};

template<template<auto...> class Sequence, auto...Variables>
struct ExtendFront<Sequence<Variables...>>
{
    template<auto...NewVariables>
    using Page = Sequence<NewVariables..., Variables...>;
};

/************************/
/**** Implementation ****/
/************************/

template<typename...>
struct InsertValues {};

/**** Base Case ****/
template<auto...I>
struct InsertValues<std::index_sequence<I...>>
{
    template<auto NewVariable, auto...>
    struct ProtoPage
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            typename...BackTargets
        >
        static consteval auto idyl()
        // `NewVariable` is injected in the return type.
        // Note that `Shuttle` is instantiated by values
        // extracted from the template parameters.
        // This is because we will pack every variable
        // into `Vay`.
        -> Shuttle
        <
            FrontTargets::value...,
            NewVariable,
            BackTargets::value...
        >;

        template<auto...Agreements>
        using Page = decltype(idyl<Vay<Agreements>...>());
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template<auto...I, auto...J>
struct InsertValues<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<auto FirstNewVariable, auto SecondNewVariable, auto...>
    struct ProtoPage
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We use `Prefix<J>...` to go across the distance
            // between two targets.
            Prefix<J>...MiddleTargets,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> Shuttle
        <
            FrontTargets::value...,
            FirstNewVariable,
            MiddleTargets::value...,
            SecondNewVariable,
            BackTargets::value...
        >;

        template<auto...Agreements>
        using Page = decltype(idyl<Vay<Agreements>...>());
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/**** Recursive Case ****/
template<auto...I, auto...J, typename...OtherSequences>
struct InsertValues<std::index_sequence<I...>, std::index_sequence<J...>, OtherSequences...>
{
    template<auto FirstNewVariable, auto SecondNewVariable, auto...OtherNewVariables>
    struct ProtoPage
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We use `Prefix<J>...` to go across the distance
            // between two targets.
            Prefix<J>...MiddleTargets,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> ExtendFront
        <
            typename InsertValues<OtherSequences...>
            ::template Page<OtherNewVariables...>
            ::template Page<BackTargets::value...>
        >
        ::template Page
        <
            FrontTargets::value...,
            FirstNewVariable,
            MiddleTargets::value...,
            SecondNewVariable
        >;

        template<auto...Agreements>
        using Page = decltype(idyl<Vay<Agreements>...>());
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
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
using Metafunction = InsertValues
<
    std::make_index_sequence<1>,
    std::make_index_sequence<2-1>,
    std::make_index_sequence<3-2>
>
::Page<-1, -3, -5>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Shuttle<0, -1, 2, -3, 4, -5>;

/**** Result ****/
using Result = Metafunction<0, 2, 4>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
