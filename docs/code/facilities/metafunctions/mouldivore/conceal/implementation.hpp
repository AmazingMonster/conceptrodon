/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class Operation>
struct Conceal
{
    template<typename...Elements>
    struct ProtoMold
    { using type = Operation<Elements...>; };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int, int*, int**, int***>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Conceal<Operation>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<int, int*, int**, int***>
::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);