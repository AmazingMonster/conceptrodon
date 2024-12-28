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

/**** Erase ****/
template<auto...Variables>
struct Erase
{
    template<auto...>
    struct ProtoPage {};

    template<size_t Index>
    struct ProtoPage<Index>
    {
        template<template<auto...> class...Agreements>
        using Rail = decltype
        (
            Ditch<std::make_index_sequence<Index>>
            ::template idyl<Agreements..., Vay<Variables>...>()
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {
        template<template<auto...> class...Agreements>
        using Rail = decltype
        (
            Expunge<std::make_index_sequence<Start>, std::make_index_sequence<End-Start>>
            ::template idyl<Agreements..., Vay<Variables>...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/***********************/
/**** First Example ****/
/***********************/

/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 2, 2>;

/**** Result ****/
using Result = Erase<0, 1, 2, 2>::Page<1>::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);

/************************/
/**** Second Example ****/
/************************/

/**** SupposedResult ****/
using SupposedResult_1 = Operation<0, 2>;

/**** Result ****/
using Result_1 = Erase<0, 1, 2, 2>::Page<1, 3>::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);