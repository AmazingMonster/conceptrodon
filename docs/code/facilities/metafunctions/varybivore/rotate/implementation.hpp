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

/**** Swivel ****/
template<typename>
struct Swivel {};

template<size_t...J>
struct Swivel<std::index_sequence<J...>>
{
    template<
        template<auto...> class Operation,
        Prefix<J>...FrontTargets,
        typename...BackTargets
    >
    static constexpr auto idyl()
    // Note the position change of `FrontTargets...` and `BackTargets.`
    // Note that `Operation` is invoked by values extracted from
    // the template parameters.
    // This is because we will pack every item
    // of `Variables...` into `Vay`.
    -> Operation<BackTargets::value..., FrontTargets::value...>;
};

/**** Rotate ****/
template<auto...Variables>
struct Rotate
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<template<auto...> class...Agreements>
        using Rail = decltype
        (
            Swivel<std::make_index_sequence<Amount>>
            ::template idyl<Agreements..., Vay<Variables>...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<2, 0, 1, 2>;

/**** Result ****/
using Result = Rotate<0, 1, 2, 2>
::Page<3>
::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);