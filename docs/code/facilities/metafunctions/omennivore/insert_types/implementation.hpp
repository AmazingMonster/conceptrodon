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
struct InsertTypes {};

/**** Base Case ****/
template<auto...I>
struct InsertTypes<std::index_sequence<I...>>
{
    template<typename NewElement, typename...>
    struct ProtoMold
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> Capsule
        <
            FrontTargets...,
            NewElement,
            BackTargets...
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl<Agreements...>());
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

template<auto...I, auto...J>
struct InsertTypes<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<typename FirstNewElement, typename SecondNewElement, typename...>
    struct ProtoMold
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
        -> Capsule
        <
            FrontTargets...,
            FirstNewElement,
            MiddleTargets...,
            SecondNewElement,
            BackTargets...
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl<Agreements...>());
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

/**** Recursive Case ****/
template<auto...I, auto...J, typename...OtherSequences>
struct InsertTypes<std::index_sequence<I...>, std::index_sequence<J...>, OtherSequences...>
{
    template<typename FirstNewElement, typename SecondNewElement, typename...OtherNewElements>
    struct ProtoMold
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
            typename InsertTypes<OtherSequences...>
            ::template Mold<OtherNewElements...>
            ::template Mold<BackTargets...>
        >
        ::template Mold
        <
            FrontTargets...,
            FirstNewElement,
            MiddleTargets...,
            SecondNewElement
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl<Agreements...>());
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
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
using Metafunction = InsertTypes
<
    std::make_index_sequence<1>,
    std::make_index_sequence<2-1>,
    std::make_index_sequence<3-2>
>
::Mold<Vay<-1>, Vay<-3>, Vay<-5>>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Capsule<Vay<0>, Vay<-1>, Vay<2>, Vay<-3>, Vay<4>, Vay<-5>>;

/**** Result ****/
using Result = Metafunction<Vay<0>, Vay<2>, Vay<4>>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
