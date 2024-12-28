/************************/
/**** Implementation ****/
/************************/

template<template<template<template<auto...> class...> class...> class Operation>
struct Say
{
    template<template<template<auto...> class...> class...Args>
    using Sail = Operation<Args...>;
};

/***********************/
/**** First Example ****/
/***********************/

/**** Operations ****/
template<template<template<auto...> class...> class...>
struct Op_0 {};

template<template<template<auto...> class...> class...>
struct Op_1 {};

/**** fun ****/
constexpr bool fun(Say<Op_0>) { return false; }

constexpr bool fun(Say<Op_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Say<Op_0>{}));
static_assert(fun(Say<Op_1>{}));

/************************/
/**** Second Example ****/
/************************/

#include <type_traits>

/**** gun ****/
constexpr auto gun(Say<Op_0>) -> std::false_type;

constexpr auto gun(Say<Op_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Say<Op_0>>()))::value);
static_assert(decltype(gun(std::declval<Say<Op_1>>()))::value);