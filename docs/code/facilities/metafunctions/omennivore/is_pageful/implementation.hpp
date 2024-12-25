/************************/
/**** Implementation ****/
/************************/

template<typename>
struct IsPageful
{ static constexpr bool value {false}; };

template<template<auto...> class Sequence, auto...Variables>
struct IsPageful<Sequence<Variables...>>
{ static constexpr bool value {true}; };

/*****************/
/**** Example ****/
/*****************/

/**** Vessel ****/
template<auto...>
struct PageLike;

/**** Tests ****/
static_assert(IsPageful<PageLike<0, 1>>::value);
static_assert(! IsPageful<int>::value);