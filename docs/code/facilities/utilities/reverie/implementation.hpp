/**********************/
/**** Dependencies ****/
/**********************/

#include <cstddef>

/************************/
/**** Implementation ****/
/************************/

template<template<template<typename...> class...> class...Warehouses>
struct Reverie
{
    static constexpr size_t size()
    { return sizeof...(Warehouses); }

    template<template<template<template<typename...> class...> class...> class Sorrow>
    struct Detail { using type = Sorrow<Warehouses...>; };

    template<template<template<template<typename...> class...> class...> class...Sorrow>
    using Snow = Detail<Sorrow...>::type;
};

/***********************/
/**** First Example ****/
/***********************/

#include <concepts>

/**** Items ****/
template<template<typename...> class...>
struct Warehouse_0;

template<template<typename...> class...>
struct Warehouse_1;

template<template<typename...> class...>
struct Warehouse_2;

template<template<typename...> class...>
struct Warehouse_3;

/**** Operation ****/
template<template<template<typename...> class...> class...>
struct Operation;

/**** Packed Vessel ****/
using PackedReverie = Reverie
<
    Warehouse_0, 
    Warehouse_1, 
    Warehouse_2, 
    Warehouse_3
>;

/**** SupposedResult ****/
using SupposedResult = Operation
<
    Warehouse_0, 
    Warehouse_1, 
    Warehouse_2, 
    Warehouse_3
>;

/**** Result ****/
using Result = PackedReverie::Snow<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

/************************/
/**** Second Example ****/
/************************/

static_assert(PackedReverie::size() == 4);