/************************/
/**** Implementation ****/
/************************/

template<template<template<typename...> class...> class Operation>
struct Reveal
{
    template<template<typename...> class...Containers>
    using Road = Operation<Containers...>::type;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Dummy Arguments ****/
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

/**** Vehicle ****/
template<template<typename...> class...>
struct Vehicle;

/**** Operation ****/
template<template<typename...> class...Args>
struct Operation
{ using type = Vehicle<Args...>; };

/**** SupposedResult ****/
using SupposedResult = Vehicle<Con_2, Con_3, Con_0, Con_1>;

/**** Metafunction ****/
template<template<typename...> class...Args>
using Metafunction = Reveal<Operation>
::Road<Args...>;

/**** Result ****/
using Result = Metafunction<Con_2, Con_3, Con_0, Con_1>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

