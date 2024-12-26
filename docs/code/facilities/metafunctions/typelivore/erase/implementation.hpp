/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/**** Prefix ****/
template<typename, auto>
concept Prefix = true;

/************************/
/**** Implementation ****/
/************************/

/**** Ditch ****/
template<typename>
struct Ditch {};

template<size_t...I>
struct Ditch<std::index_sequence<I...>>
{
    template
    <
        template<typename...> class Operation,
        Prefix<I>...FrontTargets,
        typename,
        typename...BackTargets
    >
    static consteval auto idyl() -> Operation<FrontTargets..., BackTargets...>;
};

/**** Expunge ****/
template<typename, typename>
struct Expunge {};

template<size_t...I, size_t...J>
struct Expunge<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template
    <
        template<typename...> class Operation,
        // We use `Prefix<I>...` to reach the start of the unwanted elements.
        Prefix<I>...FrontTargets,
        // We use `Prefix<J>...` to enumerate the elements we want to erase.
        Prefix<J>...,
        typename...BackTargets
    >
    static consteval auto idyl() -> Operation<FrontTargets..., BackTargets...>;
};

/**** Erase ****/
template<typename...Elements>
struct Erase
{
    template<auto...>
    struct ProtoPage {};

    template<size_t Index>
    struct ProtoPage<Index>
    {
        template<template<typename...> class...Agreements>
        using Road = decltype
        (
            Ditch<std::make_index_sequence<Index>>
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
            Expunge
            <
                std::make_index_sequence<Start>,
                // `End-Start` is the number of elements we will erase.
                std::make_index_sequence<End-Start>
            >
            ::template idyl<Agreements..., Elements...>()
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
using SupposedResult = Operation<int, int**, int**>;

/**** Result ****/
using Result = Erase<int, int*, int**, int**>::Page<1>::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);

/************************/
/**** Second Example ****/
/************************/

/**** SupposedResult ****/
using SupposedResult_1 = Operation<int, int**>;

/**** Result ****/
using Result_1 = Erase<int, int*, int**, int**>::Page<1, 3>::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);