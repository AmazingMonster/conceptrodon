/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class Operation>
struct Flip
{
    template<typename...Elements>
    struct ProtoMold 
    {
        template<auto...Agreements>
        using Page = Operation<Agreements...>
        ::template Mold<Elements...>;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Operation ****/
template<auto...>
struct Operation
{
    template<typename...>
    struct ProtoMold {};

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};

/**** SupposedResult ****/
using SupposedResult = Operation<0>
::Mold<int, int*>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Flip<Operation>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<int, int*>::Page<0>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);