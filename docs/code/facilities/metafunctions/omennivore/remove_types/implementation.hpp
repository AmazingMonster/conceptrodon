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
struct RemoveTypes {};

/**** Base Case ****/
template<auto...I>
struct RemoveTypes<std::index_sequence<I...>>
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
    -> Capsule
    <
        typename decltype(front_args)::type...,
        typename BackArgs::type...
    >;

    template<typename...Agreements>
    using Mold = decltype(idyl(std::type_identity<Agreements>{}...));
};

template<auto...I, auto...J>
struct RemoveTypes<std::index_sequence<I...>, std::index_sequence<J...>>
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
    -> Capsule
    <
        typename decltype(front_args)::type...,
        typename decltype(middle_args)::type...,
        typename BackArgs::type...
    >;

    template<typename...Agreements>
    using Mold = decltype(idyl(std::type_identity<Agreements>{}...));
};

/**** Recursive Case ****/
template<auto...I, auto...J, typename...OtherSequences>
struct RemoveTypes<std::index_sequence<I...>, std::index_sequence<J...>, OtherSequences...>
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
            RemoveTypes<OtherSequences...>
            ::idyl(BackArgs{}...)
        )
    >
    ::template Mold
    <
        typename decltype(front_args)::type...,
        typename decltype(middle_args)::type...
    >;

    template<typename...Agreements>
    using Mold = decltype(idyl(std::type_identity<Agreements>{}...));
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