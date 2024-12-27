/**********************/
/**** Dependencies ****/
/**********************/

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** ExtendFront ****/
// We will use this function to
// concatenate the preserved and recursed parts.
template<typename>
struct ExtendFront {};

template<template<auto...> class Sequence, auto...Variables>
struct ExtendFront<Sequence<Variables...>>
{
    template<auto...Beginnings>
    using Page = Sequence<Beginnings..., Variables...>;
};

/**** TypicalPop ****/
template<auto...>
struct TypicalPop {};

template<auto First>
struct TypicalPop<First>
{
    using type = Shuttle<>;
};

template<auto First, auto Second>
struct TypicalPop<First, Second>
{
    using type = Shuttle<First>;
};

template<auto First, auto Second, auto...Others>
struct TypicalPop<First, Second, Others...>
{
    using type
    = ExtendFront<typename TypicalPop<Others...>::type>
    ::template Page<First, Second>;
};

/************************/
/**** Implementation ****/
/************************/

template<auto...Variables>
using Pop = TypicalPop<Variables...>::type;

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** SupposedResult ****/
using SupposedResult = Shuttle<0, 1, 2>;

/**** Result ****/
using Result = TypicalPop<0, 1, 2, 2>::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);