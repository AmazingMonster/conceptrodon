/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/************************/
/**** Implementation ****/
/************************/

/**** Bundle_v ****/
template<auto Variable, auto>
static constexpr auto Bundle_v
{Variable};

/**** Duplicate ****/
template<auto Variable>
struct Duplicate
{
    template<typename>
    struct ProtoMold {};

    template<size_t...I>
    struct ProtoMold<std::index_sequence<I...>>
    {
        template<template<auto...> class Operation>
        struct Detail
        {
            using type = Operation
            <Bundle_v<Variable, I>...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;
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

/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 0, 0, 0>;

/**** Result ****/
using Result = Duplicate<0>
::Page<4>
::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);