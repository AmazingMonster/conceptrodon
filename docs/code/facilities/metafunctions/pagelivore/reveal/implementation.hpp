/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class Operation>
struct Reveal
{
    template<auto...Variables>
    using Page = Operation<Variables...>::type;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Operation ****/
template<auto...Args>
struct Operation
{ using type = Shuttle<Args...>; };

/**** SupposedResult ****/
using SupposedResult = Shuttle<0, 1, 2, 2>;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = Reveal<Operation>
::Page<Args...>;

/**** Result ****/
using Result = Metafunction<0, 1, 2, 2>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);