/**********************/
/**** Dependencies ****/
/**********************/

#include <cstddef>

/************************/
/**** Implementation ****/
/************************/

template<template<template<template<typename...> class...> class...> class...Items>
struct Forlorn
{
    static constexpr size_t size()
    { return sizeof...(Items); }

    template<template<template<template<template<typename...> class...> class...> class...> class Silence>
    struct Detail { using type = Silence<Items...>; };

    template<template<template<template<template<typename...> class...> class...> class...> class...Silence>
    using Cool = Detail<Silence...>::type;
};

/***********************/
/**** First Example ****/
/***********************/

#include <concepts>

/**** Items ****/
template<template<template<typename...> class...> class...>
struct Item_0;

template<template<template<typename...> class...> class...>
struct Item_1;

template<template<template<typename...> class...> class...>
struct Item_2;

template<template<template<typename...> class...> class...>
struct Item_3;

/**** Operation ****/
template<template<template<template<typename...> class...> class...> class...>
struct Operation;

/**** Packed Vessel ****/
using PackedForlorn = Forlorn
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
using Result = PackedForlorn::Cool<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

/************************/
/**** Second Example ****/
/************************/

static_assert(PackedForlorn::size() == 4);