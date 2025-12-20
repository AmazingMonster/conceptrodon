/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class Predicate, typename...Elements>
concept AnyConfess = (...||Predicate<Elements>::value);

/***********************/
/**** First Example ****/
/***********************/

/**** Pred_0 ****/
template<typename...>
struct Pred_0
{
    static constexpr bool value {true};
};

/**** Pred_1 ****/
template<typename...>
struct Pred_1
{
    static constexpr bool value {true};
};

/**** fun ****/
template<typename...Args>
requires (...||Pred_0<Args>::value)
constexpr bool fun(){return false;}

template<typename...Args>
requires (...||Pred_0<Args>::value) && (...||Pred_1<Args>::value)
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<int>());

/************************/
/**** Second Example ****/
/************************/

/**** pun ****/
template<typename...Args>
requires AnyConfess<Pred_0, Args...>
constexpr bool pun(){return false;}

template<typename...Args>
requires AnyConfess<Pred_0, Args...> && AnyConfess<Pred_1, Args...>
constexpr bool pun(){return true;}

/**** Test ****/
static_assert(pun<int>());