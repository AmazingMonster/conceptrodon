/**********************/
/**** Dependencies ****/
/**********************/

/**** ExtendFront ****/
// We will use this function to
// concatenate the preserved and recursed parts.
template<typename>
struct ExtendFront {};

template<template<typename...> class Container, typename...Elements>
struct ExtendFront<Container<Elements...>>
{
    template<typename...Beginnings>
    using Mold = Container<Beginnings..., Elements...>;
};

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** TypicalPop ****/
template<typename...>
struct TypicalPop {};

template<typename First>
struct TypicalPop<First>
{
    using type = Capsule<>;
};

template<typename First, typename Second>
struct TypicalPop<First, Second>
{
    using type = Capsule<First>;
};

template<typename First, typename Second, typename...Others>
struct TypicalPop<First, Second, Others...>
{
    using type
    = ExtendFront<typename TypicalPop<Others...>::type>
    ::template Mold<First, Second>;
};

/************************/
/**** Implementation ****/
/************************/

template<typename...Elements>
using Pop = TypicalPop<Elements...>::type;

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** SupposedResult ****/
using SupposedResult = Capsule<int, int*, int**>;

/**** Result ****/
using Result = Pop<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);