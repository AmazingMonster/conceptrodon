/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/**** Prefix ****/
template<typename, size_t>
concept Prefix = true;

/**** Swivel ****/
template<typename>
struct Shear {};

template<size_t...I>
struct Shear<std::index_sequence<I...>>
{
    template
    <
        template<typename...> class Operation,
        // We use `Prefix<I>...` to enumerate the
        // unwanted arguments.
        Prefix<I>...Unwanted,
        typename...Targets
    >
    static consteval auto idyl()
    -> Operation<Targets...>;
};

/**** Incise ****/
template<typename, typename>
struct Incise {};

template<size_t...I, size_t...J>
struct Incise<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template
    <
        template<typename...> class Operation,
        // We use `Prefix<I>...` to reach the start of `Targets`.
        Prefix<I>...,
        // We use `Prefix<J>...` to enumerate the elements
        // we want to collect.
        Prefix<J>...Targets,
        typename...
    >
    static consteval auto idyl()
    -> Operation<Targets...>;
};

/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class Operation>
struct CognateSlice
{
    template<size_t...>
    struct ProtoPage {};

    template<size_t Amount>
    struct ProtoPage<Amount>
    {
        template<typename...Elements>
        using Mold = decltype
        (
            Shear<std::make_index_sequence<Amount>>
            ::template idyl<Operation, Elements...>()
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {
        template<typename...Elements>
        using Mold = decltype
        (
            Incise<std::make_index_sequence<Start>, std::make_index_sequence<End-Start>>
            ::template idyl<Operation, Elements...>()
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
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int**, int**>;

/**** Result ****/
using Result = CognateSlice<Operation>
::Page<2>
::Mold<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);

/************************/
/**** Second Example ****/
/************************/

/**** SupposedResult */
using SupposedResult_1 = Operation<int*, int**>;

/**** Result ****/
using Result_1 = CognateSlice<Operation>
::Page<1, 3>
::Mold<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);