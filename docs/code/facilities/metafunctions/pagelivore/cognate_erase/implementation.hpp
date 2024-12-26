/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/**** Vay ****/
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };

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
        template<auto...> class Operation,
        Prefix<I>...FrontTargets,
        typename,
        typename...BackTargets
    >
    static consteval auto idyl() -> 
    // Note that `Operation` is invoked by values
    // extracted from the template parameters.
    // This is because we will pack every item
    // of `Variables...` into `Vay`.
    Operation<FrontTargets::value..., BackTargets::value...>;
};

/**** Expunge ****/
template<typename, typename>
struct Expunge {};

template<size_t...I, size_t...J>
struct Expunge<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template
    <
        template<auto...> class Operation,
        // We use `Prefix<I>...` to reach the start of the unwanted variables.
        Prefix<I>...FrontTargets,
        // We use `Prefix<J>...` to enumerate the variables we want to erase.
        Prefix<J>...,
        typename...BackTargets
    >
    static consteval auto idyl() ->
    // Note that `Operation` is invoked by values
    // extracted from the template parameters.
    // This is because we will pack every item
    // of `Variables...` into `Vay`.
    Operation<FrontTargets::value..., BackTargets::value...>;
};

/**** CognateErase ****/
template<template<auto...> class Operation>
struct CognateErase
{
    template<size_t...>
    struct ProtoPage {};

    template<size_t Index>
    struct ProtoPage<Index>
    {
        template<auto...Variables>
        using Page = decltype
        (
            Ditch<std::make_index_sequence<Index>>
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
            Expunge<std::make_index_sequence<Start>, std::make_index_sequence<End-Start>>
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
using SupposedResult = Operation<0, 2, 2>;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = CognateErase<Operation>::Page<1>::Page<Args...>;

/**** Result ****/
using Result = Metafunction<0, 1, 2, 2>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);

/************************/
/**** Second Example ****/
/************************/

/**** SupposedResult ****/
using SupposedResult_1 = Operation<0, 2>;

/**** Metafunction ****/
template<auto...Args>
using Metafunction_1 = CognateErase<Operation>::Page<1, 3>::Page<Args...>;

/**** Result ****/
using Result_1 = Metafunction_1<0, 1, 2, 2>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);