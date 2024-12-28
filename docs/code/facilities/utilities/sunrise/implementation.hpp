/**********************/
/**** Dependencies ****/
/**********************/

#include <cstddef>

/************************/
/**** Implementation ****/
/************************/

template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Items>
struct Sunrise
{
    static constexpr size_t size()
    { return sizeof...(Items); }
};

/*****************/
/**** Example ****/
/*****************/

/**** Items ****/
template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct Item_0;

template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct Item_1;

template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct Item_2;

template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct Item_3;

/**** Packed Vessel ****/
using PackedSunrise = Sunrise
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

/**** Test ****/
static_assert(PackedSunrise::size() == 4);