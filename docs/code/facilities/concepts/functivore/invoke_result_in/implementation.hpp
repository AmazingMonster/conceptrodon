/**********************/
/**** Dependencies ****/
/**********************/

#include <type_traits>

template<template<typename...> class Predicate, typename...Elements>
concept Passed = Predicate<Elements...>::value;

/************************/
/**** Implementation ****/
/************************/

template<typename Fun, typename Result, typename...Args>
concept InvokeResultIn
= Passed<std::is_invocable_r, Result, Fun, Args...>;

/***************/
/**** Tests ****/
/***************/

struct FO;

// This will fail.
static_assert(std::is_invocable_r_v<void, void(FO::*) () volatile &, FO>);
// This will fail as well.
static_assert(InvokeResultIn<void(FO::*) () volatile &, void, FO>);