/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class Predicate, typename...Elements>
concept AllConfess = (...&&Predicate<Elements::value>::value);

/***********************/
/**** First Example ****/
/***********************/

/**** Pred_0 ****/
template<auto...>
struct Pred_0
{
    static constexpr bool value {true};
};

/**** Pred_1 ****/
template<auto...>
struct Pred_1
{
    static constexpr bool value {true};
};

/**** Vay ****/
template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

/**** fun ****/
template<typename...Args>
requires (...&&Pred_0<Args::value>::value)
constexpr bool fun(){return false;}

template<typename...Args>
requires (...&&Pred_0<Args::value>::value) && (...&&Pred_1<Args::value>::value)
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<Vay<1>>());

/************************/
/**** Second Example ****/
/************************/

/**** pun ****/
template<typename...Args>
requires AllConfess<Pred_0, Args...>
constexpr bool pun(){return false;}

template<typename...Args>
requires AllConfess<Pred_0, Args...> && AllConfess<Pred_1, Args...>
constexpr bool pun(){return true;}

/**** Test ****/
static_assert(pun<Vay<1>>());