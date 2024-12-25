/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/**** ExtendFront ****/
template<typename...>
struct ExtendFront {};

template<template<typename...> class Container, typename...Elements>
struct ExtendFront<Container<Elements...>>
{
    template<typename...NewElements>
    using Mold = Container<NewElements..., Elements...>;
};

/**** Prefix ****/
template<typename, size_t>
concept Prefix = true;

/**** Capsule ****/
template<typename...>
struct Capsule;

/************************/
/**** Implementation ****/
/************************/

template<typename...>
struct ClassicModifyTypes {};

/**** Base Case ****/
template<auto...I>
struct ClassicModifyTypes<std::index_sequence<I...>>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We will transform the next argument.
            typename Target,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> Capsule
        <
            FrontTargets...,
            typename Operation<Target>::type,
            BackTargets...
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl<Agreements...>());
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template<auto...I, auto...J>
struct ClassicModifyTypes<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We will transform the next argument.
            typename FirstTarget,
            // We use `Prefix<J>...` to go across the distance
            // between two targets.
            Prefix<J>...MiddleTargets,
            // We will transform the next argument.
            typename SecondTarget,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> Capsule
        <
            FrontTargets...,
            typename Operation<FirstTarget>::type,
            MiddleTargets...,
            typename Operation<SecondTarget>::type,
            BackTargets...
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl<Agreements...>());
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

/**** Recursive Case ****/
template<auto...I, auto...J, typename...OtherSequences>
struct ClassicModifyTypes<std::index_sequence<I...>, std::index_sequence<J...>, OtherSequences...>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We will transform the next argument.
            typename FirstTarget,
            // We use `Prefix<J>...` to go across the distance
            // between two targets.
            Prefix<J>...MiddleTargets,
            // We will transform the next argument.
            typename SecondTarget,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> ExtendFront
        <
            typename ClassicModifyTypes<OtherSequences...>
            ::template Road<Operation>
            ::template Mold<BackTargets...>
        >
        ::template Mold
        <
            FrontTargets...,
            typename Operation<FirstTarget>::type,
            MiddleTargets...,
            typename Operation<SecondTarget>::type
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl<Agreements...>());
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** UnaryMinus ****/
template<typename Val>
struct UnaryMinus
{
    using type = Vay<-Val::value>;
};

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = ClassicModifyTypes
<
    std::make_index_sequence<1>,
    std::make_index_sequence<3-1-1>,
    std::make_index_sequence<5-3-1>
>
::Road<UnaryMinus>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Capsule<Vay<0>, Vay<-1>, Vay<2>, Vay<-3>, Vay<4>, Vay<-5>>;

/**** Result ****/
using Result = Metafunction<Vay<0>, Vay<1>, Vay<2>, Vay<3>, Vay<4>, Vay<5>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
