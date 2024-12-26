/**********************/
/**** Dependencies ****/
/**********************/

/**** Vehicle ****/
template<template<typename...> class...>
struct Vehicle;

/************************/
/**** Implementation ****/
/************************/

template<typename...>
struct KindredRepack {};

// Base Case:

template<template<template<typename...> class...> class Warehouse, template<typename...> class...Containers>
struct KindredRepack<Warehouse<Containers...>>
{
    template<template<template<typename...> class...> class Operation>
    struct Detail
    {
        using type = Operation<Containers...>;
    };

    template<template<template<typename...> class...> class...Agreements>
    using Flow = Detail<Agreements...>::type;
};

// Recursive Case:

template
<
    template<template<typename...> class...> class WarehouseA,
    template<template<typename...> class...> class WarehouseB,
    template<typename...> class...ContainerAs, 
    template<typename...> class...ContainerBs,
    typename...Others
>
struct KindredRepack<WarehouseA<ContainerAs...>, WarehouseB<ContainerBs...>, Others...>
{
    template<template<template<typename...> class...> class Operation>
    struct Detail
    {
        using type = KindredRepack
        <
            Vehicle<ContainerAs..., ContainerBs...>,
            Others...
        >::template Flow<Operation>;
    };

    template<template<template<typename...> class...> class...Agreements>
    using Flow = Detail<Agreements...>::type;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** New Vessel ****/
template<template<typename...> class...>
struct Warehouse;

/**** Vessels ****/
template<template<typename...> class...>
struct Warehouse_0;

template<template<typename...> class...>
struct Warehouse_1;

template<template<typename...> class...>
struct Warehouse_2;

/**** Items ****/
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

/**** SupposedResult ****/
using SupposedResult = Warehouse<Con_0, Con_1, Con_2, Con_3>;

/**** Result ****/
using Result = KindredRepack
<
    Warehouse_0<Con_0>, 
    Warehouse_1<Con_1, Con_2>,
    Warehouse_2<Con_3>
>::Flow<Warehouse>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

