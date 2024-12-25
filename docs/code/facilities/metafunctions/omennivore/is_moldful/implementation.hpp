/************************/
/**** Implementation ****/
/************************/

template<typename>
struct IsMoldful
{ static constexpr bool value {false}; };

template<template<typename...> class Container, typename...Elements>
struct IsMoldful<Container<Elements...>>
{ static constexpr bool value {true}; };

/*****************/
/**** Example ****/
/*****************/

/**** Vessel ****/
template<typename...>
struct MoldLike;

/**** Tests ****/
static_assert(IsMoldful<MoldLike<int, int*>>::value);
static_assert(! IsMoldful<int>::value);