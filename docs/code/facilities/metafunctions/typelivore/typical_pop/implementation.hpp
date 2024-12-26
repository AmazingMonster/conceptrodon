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

/************************/
/**** Implementation ****/
/************************/

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
using Result = TypicalPop<int, int*, int**, int**>::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);