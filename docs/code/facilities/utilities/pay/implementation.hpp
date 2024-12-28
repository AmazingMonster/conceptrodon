/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class Sequence>
struct Pay
{
    template<auto...Variables>
    using Page = Sequence<Variables...>;
};

/***********************/
/**** First Example ****/
/***********************/

/**** Operations ****/
template<auto...>
struct Seq_0 {};

template<auto...>
struct Seq_1 {};

/**** fun ****/
constexpr bool fun(Pay<Seq_0>) { return false; }

constexpr bool fun(Pay<Seq_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Pay<Seq_0>{}));
static_assert(fun(Pay<Seq_1>{}));

/************************/
/**** Second Example ****/
/************************/

#include <type_traits>

/**** gun ****/
constexpr auto gun(Pay<Seq_0>) -> std::false_type;

constexpr auto gun(Pay<Seq_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Pay<Seq_0>>()))::value);
static_assert(decltype(gun(std::declval<Pay<Seq_1>>()))::value);