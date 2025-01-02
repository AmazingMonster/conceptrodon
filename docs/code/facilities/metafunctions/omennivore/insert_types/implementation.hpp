/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>

/**** Prefix ****/
template<typename, auto>
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
        template<typename...BackArgs>
        static consteval auto idyl
        (
            // Expand `Prefix<I>` to reach the desired position.
            Prefix<I> auto...front_args,
            // Collect the rest arguments.
            BackArgs...
        )
        -> Capsule
        <
            typename decltype(front_args)::type...,
            NewElement,
            typename BackArgs::type...
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl(std::type_identity<Agreements>{}...));
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
        template<typename...BackArgs>
        static consteval auto idyl
        (
            // Expand `Prefix<I>` to reach the position for the first new element.
            Prefix<I> auto...front_args,
            // Expand `Prefix<J>` to reach the position for the second new element.
            Prefix<J> auto...middle_args,
            // Collect the rest arguments.
            BackArgs...
        )
        -> Capsule
        <
            typename decltype(front_args)::type...,
            FirstNewElement,
            typename decltype(middle_args)::type...,
            SecondNewElement,
            typename BackArgs::type...
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl(std::type_identity<Agreements>{}...));
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
        template<typename...BackArgs>
        static consteval auto idyl
        (
            // Expand `Prefix<I>` to reach the position for the first new element.
            Prefix<I> auto...front_args,
            // Expand `Prefix<J>` to reach the position for the second new element.
            Prefix<J> auto...middle_args,
            // Collect the rest arguments.
            BackArgs...
        )
        -> ExtendFront
        <
            decltype
            (
                InsertTypes<OtherSequences...>
                ::template Mold<OtherNewElements...>
                ::idyl(BackArgs{}...)
            )
        >
        ::template Mold
        <
            typename decltype(front_args)::type...,
            FirstNewElement,
            typename decltype(middle_args)::type...,
            SecondNewElement
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl(std::type_identity<Agreements>{}...));
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
static_assert(std::same_as<Result, SupposedResult>);
