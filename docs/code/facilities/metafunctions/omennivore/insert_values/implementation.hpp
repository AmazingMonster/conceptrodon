/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>

/**** Prefix ****/
template<typename, auto>
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
        template<typename...BackArgs>
        static consteval auto idyl
        (
            // Expand `Prefix<I>` to reach the desired position.
            Prefix<I> auto...front_args,
            // Collect the rest arguments.
            BackArgs...
        )
        -> Shuttle
        <
            decltype(front_args)::value...,
            NewVariable,
            BackArgs::value...
        >;

        template<auto...Agreements>
        using Page = decltype(idyl(Vay<Agreements>{}...));
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
        template<typename...BackArgs>
        static consteval auto idyl
        (
            // Expand `Prefix<I>` to reach the position for the first new variable.
            Prefix<I> auto...front_args,
            // Expand `Prefix<J>` to reach the position for the second new variable.
            Prefix<J> auto...middle_args,
            // Collect the rest arguments.
            BackArgs...
        )
        -> Shuttle
        <
            decltype(front_args)::value...,
            FirstNewVariable,
            decltype(middle_args)::value...,
            SecondNewVariable,
            BackArgs::value...
        >;

        template<auto...Agreements>
        using Page = decltype(idyl(Vay<Agreements>{}...));
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
        template<typename...BackArgs>
        static consteval auto idyl
        (
            // Expand `Prefix<I>` to reach the position for the first new variable.
            Prefix<I> auto...front_args,
            // Expand `Prefix<J>` to reach the position for the second new variable.
            Prefix<J> auto...middle_args,
            // Collect the rest arguments.
            BackArgs...
        )
        -> ExtendFront
        <
            decltype
            (
                InsertValues<OtherSequences...>
                ::template Page<OtherNewVariables...>
                ::idyl(BackArgs{}...)
            )
        >
        ::template Page
        <
            decltype(front_args)::value...,
            FirstNewVariable,
            decltype(middle_args)::value...,
            SecondNewVariable
        >;

        template<auto...Agreements>
        using Page = decltype(idyl(Vay<Agreements>{}...));
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
