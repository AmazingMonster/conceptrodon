/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/************************/
/**** Implementation ****/
/************************/

/**** Bundle_t ****/
template<typename Element, auto>
using Bundle_t = Element;

/**** Duplicate ****/
template<typename Element>
struct Duplicate
{
    template<typename>
    struct ProtoMold {};

    template<size_t...I>
    struct ProtoMold<std::index_sequence<I...>>
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation
            <Bundle_t<Element, I>...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<size_t I>
    struct ProtoPage
    : public ProtoMold<std::make_index_sequence<I>>
    {};

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
using SupposedResult = Operation<int, int, int, int>;

/**** Result ****/
using Result = Duplicate<int>
::Page<4>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);