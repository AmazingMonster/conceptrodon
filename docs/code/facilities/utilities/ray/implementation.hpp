/************************/
/**** Implementation ****/
/************************/

template<template<template<auto...> class...> class Stockroom>
struct Ray
{
    template<template<auto...> class...Sequences>
    using Rail = Stockroom<Sequences...>;
};

/***********************/
/**** First Example ****/
/***********************/

/**** Operations ****/
template<template<auto...> class...>
struct Stoc_0 {};

template<template<auto...> class...>
struct Stoc_1 {};

/**** fun ****/
constexpr bool fun(Ray<Stoc_0>) { return false; }

constexpr bool fun(Ray<Stoc_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Ray<Stoc_0>{}));
static_assert(fun(Ray<Stoc_1>{}));

/************************/
/**** Second Example ****/
/************************/

#include <type_traits>

/**** gun ****/
constexpr auto gun(Ray<Stoc_0>) -> std::false_type;

constexpr auto gun(Ray<Stoc_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Ray<Stoc_0>>()))::value);
static_assert(decltype(gun(std::declval<Ray<Stoc_1>>()))::value);