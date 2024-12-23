/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class Operation>
struct BindFront
{
    template<typename...Beginnings>
    struct ProtoMold
    {
        template<typename...Elements>
        using Mold = Operation<Beginnings..., Elements...>;
    };

    template<typename...Beginnings>
    using Mold = ProtoMold<Beginnings...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Operation ****/
template<typename...>
struct Operation;

/**** Supposed Result ****/
using SupposedResult = Operation<int, int*, int**, int***>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = BindFront<Operation>
::Mold<int, int*>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<int**, int***>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);