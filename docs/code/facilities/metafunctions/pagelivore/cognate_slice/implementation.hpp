/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/**** Prefix ****/
template<typename, auto>
concept Prefix = true;

/**** Vay ****/
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };

/************************/
/**** Implementation ****/
/************************/

/**** Shear ****/
template<typename>
struct Shear {};

template<size_t...I>
struct Shear<std::index_sequence<I...>>
{
    template
    <
        template<auto...> class Operation,
        // We use `Prefix<I>...` to enumerate the
        // unwanted arguments.
        Prefix<I>...Unwanted,
        typename...Targets
    >
    static consteval auto idyl()
    // Note that `Operation` is invoked by values
    // extracted from the template parameters.
    // This is because we will pack every item
    // of `Variables...` into `Vay`.
    -> Operation<Targets::value...>;
};

/**** Incise ****/
template<typename, typename>
struct Incise {};

template<size_t...I, size_t...J>
struct Incise<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template
    <
        template<auto...> class Operation,
        // We use `Prefix<I>...` to reach the start of `Targets`.
        Prefix<I>...,
        // We use `Prefix<J>...` to enumerate the variables
        // we want to collect.
        Prefix<J>...Targets,
        typename...
    >
    static consteval auto idyl()
    // Note that `Operation` is invoked by values
    // extracted from the template parameters.
    // This is because we will pack every item
    // of `Variables...` into `Vay`.
    -> Operation<Targets::value...>;
};

/**** CognateSlice ****/
template<template<auto...> class Operation>
struct CognateSlice
{
    template<size_t...>
    struct ProtoPage {};

    template<size_t Amount>
    struct ProtoPage<Amount>
    {
        template<auto...Variables>
        using Page = decltype
        (
            Shear<std::make_index_sequence<Amount>>
            ::template idyl<Operation, Vay<Variables>...>()
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {
        template<auto...Variables>
        using Page = decltype
        (
            Incise<std::make_index_sequence<Start>, std::make_index_sequence<End-Start>>
            ::template idyl<Operation, Vay<Variables>...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/***********************/
/**** First Example ****/
/***********************/

#include <concepts>

/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<2, 2>;

/**** Result ****/
using Result = CognateSlice<Operation>
::Page<2>
::Page<0, 1, 2, 2>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);

/************************/
/**** Second Example ****/
/************************/

/**** SupposedResult ****/
using SupposedResult_1 = Operation<1, 2>;

/**** Result ****/
using Result_1 = CognateSlice<Operation>
::Page<1, 3>
::Page<0, 1, 2, 2>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);