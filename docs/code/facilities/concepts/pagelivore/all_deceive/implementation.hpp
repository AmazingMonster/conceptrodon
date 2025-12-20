/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class Predicate, typename...Elements>
concept AllDeceive = (...&&(not Predicate<Elements::value>::value));

/***********************/
/**** First Example ****/
/***********************/

/**** Pred_0 ****/
template<auto...>
struct Pred_0
{
    static constexpr bool value {false};
};

/**** Pred_1 ****/
template<auto...>
struct Pred_1
{
    static constexpr bool value {false};
};

/**** Vay ****/
template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

/**** fun ****/
template<typename...Args>
requires (...&&(not Pred_0<Args::value>::value))
constexpr bool fun(){return false;}

template<typename...Args>
requires (...&&(not Pred_0<Args::value>::value)) && (...&&(not Pred_1<Args::value>::value))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<Vay<1>>());

/************************/
/**** Second Example ****/
/************************/

/**** pun ****/
template<typename...Args>
requires AllDeceive<Pred_0, Args...>
constexpr bool pun(){return false;}

template<typename...Args>
requires AllDeceive<Pred_0, Args...> && AllDeceive<Pred_1, Args...>
constexpr bool pun(){return true;}

/**** Test ****/
static_assert(pun<Vay<1>>());