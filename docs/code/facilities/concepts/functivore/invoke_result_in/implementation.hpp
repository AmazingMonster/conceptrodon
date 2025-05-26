/**********************/
/**** Dependencies ****/
/**********************/

#include <type_traits>

template<template<typename...> class Predicate, typename...Elements>
concept Confess = Predicate<Elements...>::value;

/************************/
/**** Implementation ****/
/************************/

template<typename Fun, typename Result, typename...Args>
concept InvokeResultIn
= Confess<std::is_invocable_r, Result, Fun, Args...>;

/***************/
/**** Tests ****/
/***************/

struct FO;

// This will fail.
static_assert(std::is_invocable_r_v<void, void(FO::*) () volatile &, FO>);