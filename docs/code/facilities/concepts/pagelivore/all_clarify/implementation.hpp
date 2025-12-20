/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class Predicate, auto...Variables>
concept AllClarify = (...&&Predicate<Variables>::value);

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

/**** fun ****/
template<auto...Args>
requires (...&&Pred_0<Args>::value)
constexpr bool fun(){return false;}

template<auto...Args>
requires (...&&Pred_0<Args>::value) && (...&&Pred_1<Args>::value)
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());

/************************/
/**** Second Example ****/
/************************/

/**** pun ****/
template<auto...Args>
requires AllClarify<Pred_0, Args...>
constexpr bool pun(){return false;}

template<auto...Args>
requires AllClarify<Pred_0, Args...> && AllClarify<Pred_1, Args...>
constexpr bool pun(){return true;}

/**** Test ****/
static_assert(pun<1>());