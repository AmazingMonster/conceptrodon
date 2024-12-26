/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/************************/
/**** Implementation ****/
/************************/

template<typename, auto>
concept Prefix = true;

/**** Shear ****/
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
    static consteval auto idyl() -> Operation<Targets...>;
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
    static consteval auto idyl() -> Operation<Targets...>;
};

/**** Slice ****/
template<typename...Elements>
struct Slice
{
    template<auto...>
    struct ProtoPage {};

    template<size_t Amount>
    struct ProtoPage<Amount>
    {
        template<template<typename...> class...Agreements>
        using Road = decltype
        (
            Shear<std::make_index_sequence<Amount>>
            ::template idyl<Agreements..., Elements...>()
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {   
        template<template<typename...> class...Agreements>
        using Road = decltype
        (
            Incise<std::make_index_sequence<Start>, std::make_index_sequence<End-Start>>
            ::template idyl<Agreements..., Elements...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/***********************/
/**** First Example ****/
/***********************/

/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int**, int**>;

/**** Result ****/
using Result = Slice<int, int*, int**, int**>
::Page<2>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);

/************************/
/**** Second Example ****/
/************************/

/**** SupposedResult ****/
using SupposedResult_1 = Operation<int*, int**>;

/**** Result ****/
using Result_1 = Slice<int, int*, int**, int**>
::Page<1, 3>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);