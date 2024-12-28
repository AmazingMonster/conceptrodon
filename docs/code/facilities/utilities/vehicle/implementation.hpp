/**********************/
/**** Dependencies ****/
/**********************/

#include <cstddef>

/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class...Containers>
struct Vehicle
{
    static constexpr size_t size()
    { return sizeof...(Containers); }

    template<template<template<typename...> class...> class Warehouse>
    struct Detail { using type = Warehouse<Containers...>; };

    template<template<template<typename...> class...> class...Warehouses>
    using Flow = Detail<Warehouses...>::type;
};

/***********************/
/**** First Example ****/
/***********************/

#include <concepts>

/**** Items ****/
template<typename...>
struct Container_0;

template<typename...>
struct Container_1;

template<typename...>
struct Container_2;

template<typename...>
struct Container_3;

/**** Operation ****/
template<template<typename...> class...>
struct Operation;

/**** Packed Vessel ****/
using PackedVehicle = Vehicle
<
    Container_0, 
    Container_1, 
    Container_2, 
    Container_3
>;

/**** SuppsedResult ****/
using SupposedResult = Operation
<
    Container_0, 
    Container_1, 
    Container_2, 
    Container_3
>;

/**** Result ****/
using Result = PackedVehicle::Flow<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

/************************/
/**** Second Example ****/
/************************/

static_assert(PackedVehicle::size() == 4);