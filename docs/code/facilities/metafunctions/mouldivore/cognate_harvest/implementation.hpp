/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class Operation>
struct CognateHarvest
{ 
    template<typename...Crops>
    using Mold = Operation<typename Crops::type...>; 
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** AddOne ****/
template<auto I>
struct AddOne
{
    using type = std::integral_constant<int, I + 1>;
};

/**** Operation ****/
template<typename...>
struct Operation;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = CognateHarvest<Operation>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation
<
    std::integral_constant<int, 0 + 1>,
    std::integral_constant<int, 1 + 1>, 
    std::integral_constant<int, 2 + 1>, 
    std::integral_constant<int, 2 + 1>
>;

/**** Result ****/
using Result = Metafunction<
    AddOne<0>, AddOne<1>, AddOne<2>, AddOne<2>
>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);