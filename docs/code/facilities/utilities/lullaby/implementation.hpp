/**********************/
/**** Dependencies ****/
/**********************/

#include <cstddef>

/************************/
/**** Implementation ****/
/************************/

template<template<template<template<template<typename...> class...> class...> class...> class...Items>
struct Lullaby
{
    static constexpr size_t size()
    { return sizeof...(Items); }

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class Tranquil>
    struct Detail { using type = Tranquil<Items...>; };

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Tranquil>
    using Grit = Detail<Tranquil...>::type;
};

/***********************/
/**** First Example ****/
/***********************/

#include <concepts>

/**** Items ****/
template<template<template<template<typename...> class...> class...> class...>
struct Item_0;

template<template<template<template<typename...> class...> class...> class...>
struct Item_1;

template<template<template<template<typename...> class...> class...> class...>
struct Item_2;

template<template<template<template<typename...> class...> class...> class...>
struct Item_3;

/**** Operation ****/
template<template<template<template<template<typename...> class...> class...> class...> class...>
struct Operation;

/**** Packed Vessel ****/
using PackedLullaby = Lullaby
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
using Result = PackedLullaby::Grit<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

/************************/
/**** Second Example ****/
/************************/

static_assert(PackedLullaby::size() == 4);