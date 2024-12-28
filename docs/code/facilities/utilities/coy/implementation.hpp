/************************/
/**** Implementation ****/
/************************/

template<template<template<template<template<template<typename...> class...> class...> class...> class...> class Operation>
struct Coy
{
    template<template<template<template<template<typename...> class...> class...> class...> class...Args>
    using Cool = Operation<Args...>;
};

/***********************/
/**** First Example ****/
/***********************/

/**** Operations ****/
template<template<template<template<template<typename...> class...> class...> class...> class...>
struct Op_0 {};

template<template<template<template<template<typename...> class...> class...> class...> class...>
struct Op_1 {};

/**** fun ****/
constexpr bool fun(Coy<Op_0>) { return false; }

constexpr bool fun(Coy<Op_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Coy<Op_0>{}));
static_assert(fun(Coy<Op_1>{}));

/************************/
/**** Second Example ****/
/************************/

#include <type_traits>

/**** gun ****/
constexpr auto gun(Coy<Op_0>) -> std::false_type;

constexpr auto gun(Coy<Op_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Coy<Op_0>>()))::value);
static_assert(decltype(gun(std::declval<Coy<Op_1>>()))::value);