/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>

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
template<typename, auto>
concept Prefix = true;

/**** Capsule ****/
template<typename...>
struct Capsule;

/************************/
/**** Implementation ****/
/************************/

template<typename...>
struct ModifyTypes {};

/**** Base Case ****/
template<auto...I>
struct ModifyTypes<std::index_sequence<I...>>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        template
        <
            typename Target,
            typename...BackArgs
        >
        static consteval auto idyl
        (
            // Expand `Prefix<I>...` to count arguments before the target.
            Prefix<I> auto...front_args,
            // Transform the next argument.
            Target,
            // Collect the rest.
            BackArgs...
        )
        -> Capsule
        <
            typename decltype(front_args)::type...,
            Operation<typename Target::type>,
            typename BackArgs::type...
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl(std::type_identity<Agreements>{}...));
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template<auto...I, auto...J>
struct ModifyTypes<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        template
        <
            typename FirstTarget,
            typename SecondTarget,
            typename...BackArgs
        >
        static consteval auto idyl
        (
            // Expand `Prefix<I>...` to count arguments before the first target.
            Prefix<I> auto...front_args,
            // Transform the next argument.
            FirstTarget,
            // Expand `Prefix<J>...` to go across the distance between two targets.
            Prefix<J> auto...middle_args,
            // Transform the next argument.
            SecondTarget,
            // Collect the rest.
            BackArgs...
        )
        -> Capsule
        <
            typename decltype(front_args)::type...,
            Operation<typename FirstTarget::type>,
            typename decltype(middle_args)::type...,
            Operation<typename SecondTarget::type>,
            typename BackArgs::type...
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl(std::type_identity<Agreements>{}...));
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

/**** Recursive Case ****/
template<auto...I, auto...J, typename...OtherSequences>
struct ModifyTypes<std::index_sequence<I...>, std::index_sequence<J...>, OtherSequences...>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        template
        <
            typename FirstTarget,
            typename SecondTarget,
            typename...BackArgs
        >
        static consteval auto idyl
        (
            // Expand `Prefix<I>...` to count arguments before the first target.
            Prefix<I> auto...front_args,
            // Transform the next argument.
            FirstTarget,
            // Expand `Prefix<J>...` to go across the distance between two targets.
            Prefix<J> auto...middle_args,
            // Transform the next argument.
            SecondTarget,
            // Collect the rest.
            BackArgs...
        )
        -> ExtendFront
        <
            decltype
            (
                ModifyTypes<OtherSequences...>
                ::template Road<Operation>
                ::idyl(BackArgs{}...)
            )
        >
        ::template Mold
        <
            typename decltype(front_args)::type...,
            Operation<typename FirstTarget::type>,
            typename decltype(middle_args)::type...,
            Operation<typename SecondTarget::type>
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl(std::type_identity<Agreements>{}...));
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
struct UnaryMinusHelper
{
    using type = Vay<-Val::value>;
};

template<typename...Args>
using UnaryMinus = UnaryMinusHelper<Args...>::type;

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = ModifyTypes
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
