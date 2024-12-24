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
struct Swivel {};

template<size_t...J>
struct Swivel<std::index_sequence<J...>>
{
    template
    <
        template<typename...> class Operation,
        Prefix<J>...FrontTargets,
        typename...BackTargets
    >
    static constexpr auto idyl()
    // Note the position change of `FrontTargets...` and `BackTargets.`.
    -> Operation<BackTargets..., FrontTargets...>;
};

/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class Operation>
struct CognateRotate
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<typename...Elements>
        using Mold = decltype
        (
            Swivel<std::make_index_sequence<Amount>>
            ::template idyl<Operation, Elements...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int**, int, int*, int**>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = CognateRotate<Operation>
::Page<3>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);