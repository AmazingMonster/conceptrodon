/************************/
/**** Implementation ****/
/************************/

template<template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class Operation>
struct Gly
{
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Args>
    using Glow = Operation<Args...>;
};

/***********************/
/**** First Example ****/
/***********************/

/**** Operations ****/
template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct Op_0 {};

template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct Op_1 {};

/**** fun ****/
constexpr bool fun(Gly<Op_0>) { return false; }

constexpr bool fun(Gly<Op_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Gly<Op_0>{}));
static_assert(fun(Gly<Op_1>{}));

/************************/
/**** Second Example ****/
/************************/

#include <type_traits>

/**** gun ****/
constexpr auto gun(Gly<Op_0>) -> std::false_type;

constexpr auto gun(Gly<Op_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Gly<Op_0>>()))::value);
static_assert(decltype(gun(std::declval<Gly<Op_1>>()))::value);