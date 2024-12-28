/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class Container>
struct Moy
{
    template<typename...Elements>
    using Mold = Container<Elements...>;
};

/***********************/
/**** First Example ****/
/***********************/

/**** Operations ****/
template<typename...>
struct Con_0 {};

template<typename...>
struct Con_1 {};

/**** fun ****/
constexpr bool fun(Moy<Con_0>) { return false; }

constexpr bool fun(Moy<Con_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Moy<Con_0>{}));
static_assert(fun(Moy<Con_1>{}));

/************************/
/**** Second Example ****/
/************************/

#include <type_traits>

/**** gun ****/
constexpr auto gun(Moy<Con_0>) -> std::false_type;

constexpr auto gun(Moy<Con_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Moy<Con_0>>()))::value);
static_assert(decltype(gun(std::declval<Moy<Con_1>>()))::value);