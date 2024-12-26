/**********************/
/**** Dependencies ****/
/**********************/

template<typename...>
struct TypicalPaste {};

// Base Case:

template<typename PackedWarehouse>
struct TypicalPaste<PackedWarehouse>
{
    using type = PackedWarehouse;
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
struct TypicalPaste<WarehouseA<ContainerAs...>, WarehouseB<ContainerBs...>, Others...>
{
    using type = typename TypicalPaste
    <
        WarehouseA<ContainerAs..., ContainerBs...>,
        Others...
    >::type;
};

/************************/
/**** Implementation ****/
/************************/

template<typename...Args>
using Paste = TypicalPaste<Args...>::type;

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

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
using SupposedResult = Warehouse_0<Con_0, Con_1, Con_2, Con_3>;

/**** Result ****/
using Result = Paste
<
    Warehouse_0<Con_0>, 
    Warehouse_1<Con_1, Con_2>,
    Warehouse_2<Con_3>
>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
