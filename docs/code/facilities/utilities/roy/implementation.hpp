/************************/
/**** Implementation ****/
/************************/

template<template<template<typename...> class...> class Warehouse>
struct Roy
{
    template<template<typename...> class...Containers>
    using Road = Warehouse<Containers...>;
};

/***********************/
/**** First Example ****/
/***********************/

/**** Operations ****/
template<template<typename...> class...>
struct Ware_0 {};

template<template<typename...> class...>
struct Ware_1 {};

/**** fun ****/
constexpr bool fun(Roy<Ware_0>) { return false; }

constexpr bool fun(Roy<Ware_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Roy<Ware_0>{}));
static_assert(fun(Roy<Ware_1>{}));

/************************/
/**** Second Example ****/
/************************/

#include <type_traits>

/**** gun ****/
constexpr auto gun(Roy<Ware_0>) -> std::false_type;

constexpr auto gun(Roy<Ware_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Roy<Ware_0>>()))::value);
static_assert(decltype(gun(std::declval<Roy<Ware_1>>()))::value);