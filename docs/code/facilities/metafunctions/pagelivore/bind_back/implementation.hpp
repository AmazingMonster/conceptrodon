/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class Operation>
struct BindBack
{
    template<auto...Endings>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = Operation<Variables..., Endings...>;
    };

    template<auto...Endings>
    using Page = ProtoPage<Endings...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 1, -1, -2>;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = BindBack<Operation>
::Page<-1, -2>
::Page<Args...>;

/**** Result ****/
using Result = Metafunction<0, 1>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
