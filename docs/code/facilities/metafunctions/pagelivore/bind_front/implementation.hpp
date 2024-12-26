/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class Operation>
struct BindFront
{
    template<auto...Beginnings>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = Operation<Beginnings..., Variables...>;
    };

    template<auto...Beginnings>
    using Page = ProtoPage<Beginnings...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult */
using SupposedResult = Operation<-1, -2, 0, 1>;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = BindFront<Operation>
::Page<-1, -2>
::Page<Args...>;

/**** Result ****/
using Result = Metafunction<0, 1>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
