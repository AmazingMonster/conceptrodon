/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class Predicate, typename...Elements>
concept AnyDeceive = (...||(not Predicate<Elements>::value));

/***************/
/**** Tests ****/
/***************/

/**** Pred_0 ****/
template<typename...>
struct Pred_0
{
    static constexpr bool value {false};
};

/**** Pred_1 ****/
template<typename...>
struct Pred_1
{
    static constexpr bool value {false};
};

/**** fun ****/
template<typename...Args>
requires AnyDeceive<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AnyDeceive<Pred_0, Args...> && AnyDeceive<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<int>());