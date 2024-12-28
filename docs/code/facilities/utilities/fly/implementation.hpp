/************************/
/**** Implementation ****/
/************************/

template<template<template<template<typename...> class...> class...> class Operation>
struct Fly
{
    template<template<template<typename...> class...> class...Args>
    using Flow = Operation<Args...>;
};

/***********************/
/**** First Example ****/
/***********************/

/**** Operations ****/
template<template<template<typename...> class...> class...>
struct Op_0 {};

template<template<template<typename...> class...> class...>
struct Op_1 {};

/**** fun ****/
constexpr bool fun(Fly<Op_0>) { return false; }

constexpr bool fun(Fly<Op_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Fly<Op_0>{}));
static_assert(fun(Fly<Op_1>{}));

/************************/
/**** Second Example ****/
/************************/

#include <type_traits>

/**** gun ****/
constexpr auto gun(Fly<Op_0>) -> std::false_type;

constexpr auto gun(Fly<Op_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Fly<Op_0>>()))::value);
static_assert(decltype(gun(std::declval<Fly<Op_1>>()))::value);