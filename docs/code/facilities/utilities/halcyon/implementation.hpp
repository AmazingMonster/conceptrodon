/**********************/
/**** Dependencies ****/
/**********************/

#include <cstddef>

/************************/
/**** Implementation ****/
/************************/

template<template<template<template<template<auto...> class...> class...> class...> class...Items>
struct Halcyon
{
    static constexpr size_t size()
    { return sizeof...(Items); }

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class Tranquil>
    struct Detail { using type = Tranquil<Items...>; };

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Tranquil>
    using Will = Detail<Tranquil...>::type;
};

/***********************/
/**** First Example ****/
/***********************/

#include <concepts>

/**** Items ****/
template<template<template<template<auto...> class...> class...> class...>
struct Item_0;

template<template<template<template<auto...> class...> class...> class...>
struct Item_1;

template<template<template<template<auto...> class...> class...> class...>
struct Item_2;

template<template<template<template<auto...> class...> class...> class...>
struct Item_3;

/**** Operation ****/
template<template<template<template<template<auto...> class...> class...> class...> class...>
struct Operation;

/**** Packed Vessel ****/
using PackedHalcyon = Halcyon
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

/**** SuppsedResult ****/
using SupposedResult = Operation
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

/**** Result ****/
using Result = PackedHalcyon::Will<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

/************************/
/**** Second Example ****/
/************************/

static_assert(PackedHalcyon::size() == 4);