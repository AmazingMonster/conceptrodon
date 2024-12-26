/************************/
/**** Implementation ****/
/************************/

template<template<template<typename...> class...> class Operation>
struct Agent
{
    template<typename>
    struct Detail {};

    template<template<template<typename...> class...> class Warehouse, template<typename...> class...Containers>
    struct Detail<Warehouse<Containers...>>
    { using type = Operation<Containers...>; };
    
    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Vehicle ****/
template<template<typename...> class...>
struct Vehicle;

/**** Arguments ****/
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

/**** Operation ****/
template<template<typename...> class...>
struct Operation;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Agent<Operation>::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<Con_0, Con_1, Con_2>;

/**** Result ****/
using Result = Metafunction<Vehicle<Con_0, Con_1, Con_2>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

