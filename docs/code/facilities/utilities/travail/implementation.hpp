/**********************/
/**** Dependencies ****/
/**********************/

#include <cstddef>

/************************/
/**** Implementation ****/
/************************/

template<template<template<template<auto...> class...> class...> class...Items>
struct Travail
{
    static constexpr size_t size()
    { return sizeof...(Items); }

    template<template<template<template<template<auto...> class...> class...> class...> class Tranquil>
    struct Detail { using type = Tranquil<Items...>; };

    template<template<template<template<template<auto...> class...> class...> class...> class...Tranquil>
    using Calm = Detail<Tranquil...>::type;
};

/***********************/
/**** First Example ****/
/***********************/

#include <concepts>

/**** Items ****/
template<template<template<auto...> class...> class...>
struct Item_0;

template<template<template<auto...> class...> class...>
struct Item_1;

template<template<template<auto...> class...> class...>
struct Item_2;

template<template<template<auto...> class...> class...>
struct Item_3;

/**** Operation ****/
template<template<template<template<auto...> class...> class...> class...>
struct Operation;

/**** Packed Vessel ****/
using PackedTravail = Travail
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
using Result = PackedTravail::Calm<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

/************************/
/**** Second Example ****/
/************************/

static_assert(PackedTravail::size() == 4);