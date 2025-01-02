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
struct ModifyValues {};

/**** Base Case ****/
template<auto...I>
struct ModifyValues<std::index_sequence<I...>>
{
    template<template<auto...> class Operation>
    struct ProtoRail
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
        -> Shuttle
        <
            decltype(front_args)::value...,
            Operation<Target::value>::value,
            BackArgs::value...
        >;

        template<auto...Agreements>
        using Page = decltype(idyl(Vay<Agreements>{}...));
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

template<auto...I, auto...J>
struct ModifyValues<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<template<auto...> class Operation>
    struct ProtoRail
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
        -> Shuttle
        <
            decltype(front_args)::value...,
            Operation<FirstTarget::value>::value,
            decltype(middle_args)::value...,
            Operation<SecondTarget::value>::value,
            BackArgs::value...
        >;

        template<auto...Agreements>
        using Page = decltype(idyl(Vay<Agreements>{}...));
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

/**** Recursive Case ****/
template<auto...I, auto...J, typename...OtherSequences>
struct ModifyValues<std::index_sequence<I...>, std::index_sequence<J...>, OtherSequences...>
{
    template<template<auto...> class Operation>
    struct ProtoRail
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
                ModifyValues<OtherSequences...>
                ::template Rail<Operation>
                ::idyl(BackArgs{}...)
            )
        >
        ::template Page
        <
            decltype(front_args)::value...,
            Operation<FirstTarget::value>::value,
            decltype(middle_args)::value...,
            Operation<SecondTarget::value>::value
        >;

        template<auto...Agreements>
        using Page = decltype(idyl(Vay<Agreements>{}...));
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** UnaryMinus ****/
template<auto I>
struct UnaryMinus
{
    static constexpr auto value
    {-I};
};

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = ModifyValues
<
    std::make_index_sequence<1>,
    std::make_index_sequence<3-1-1>,
    std::make_index_sequence<5-3-1>
>
::Rail<UnaryMinus>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Shuttle<0, -1, 2, -3, 4, -5>;

/**** Result ****/
using Result = Metafunction<0, 1, 2, 3, 4, 5>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);