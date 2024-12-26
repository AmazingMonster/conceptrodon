/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class Operation>
struct CognateHarvest
{ 
    template<typename...Crops>
    using Mold = Operation<Crops::value...>; 
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Operation ****/
template<auto...>
struct Operation;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = CognateHarvest<Operation>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 1, 2, 2>;

/**** Result ****/
using Result = Metafunction<
    std::integral_constant<int, 0>, std::integral_constant<int, 1>, std::integral_constant<int, 2>, std::integral_constant<int, 2>
>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);