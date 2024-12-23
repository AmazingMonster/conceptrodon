/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class Operation>
struct BindBack
{
    template<typename...Endings>
    struct ProtoMold
    {
        template<typename...Elements>
        using Mold = Operation<Elements..., Endings...>;
    };

    template<typename...Endings>
    using Mold = ProtoMold<Endings...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Operation ****/
template<typename...>
struct Operation;

/**** Supposed Result ****/
using SupposedResult = Operation<int**, int***, int, int*>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = BindBack<Operation>
::Mold<int, int*>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<int**, int***>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);