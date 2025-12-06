/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class Operation>
struct Reveal
{
    template<typename...Elements>
    using Mold = Operation<Elements...>::type;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Operation ****/
template<typename...Args>
struct Operation
{ using type = Capsule<Args...>; };

/**** SupposedResult ****/
using SupposedResult = Capsule<int, int*, int**, int**>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Reveal<Operation>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);