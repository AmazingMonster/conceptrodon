/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class Operation>
struct Conceal
{
    template<auto...Variables>
    struct ProtoPage
    { using type = Operation<Variables...>; };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 1, 2, 3>;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = Conceal<Operation>
::Page<Args...>;

/**** Result ****/
using Result = Metafunction<0, 1, 2, 3>::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);