/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class Operation>
struct Flip
{
    template<typename...Elements>
    struct ProtoMold 
    {
        template<typename...Agreements>
        using Mold = Operation<Agreements...>
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
template<typename...>
struct Operation
{
    template<typename...>
    struct ProtoMold {};

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};

/**** SupposedResult *****/
using SupposedResult = Operation<void>
::Mold<int, int*>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Flip<Operation>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<int, int*>::Mold<void>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);