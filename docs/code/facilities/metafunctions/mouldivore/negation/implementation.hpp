/************************/
/**** Implementation ****/
/************************/

template<template<typename...>  class Predicate>
struct Negation
{
    template<typename...Elements>
    struct ProtoMold
    {
        static constexpr bool value 
        {not Predicate<Elements...>::value};
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <type_traits>

/**** IsLess ****/
template<typename First, typename Second>
struct IsLess
{
    static constexpr bool value
    {First::value < Second::value};
};

/**** IsNoLess ****/
template<typename...Args>
using IsNoLess = Negation<IsLess>::Mold<Args...>;

/**** Tests ****/
static_assert(IsNoLess<std::integral_constant<int, 1>, std::integral_constant<int, 1>>::value);
static_assert(IsNoLess<std::integral_constant<int, 1>, std::integral_constant<int, 0>>::value);
static_assert(! IsNoLess<std::integral_constant<int, 1>, std::integral_constant<int, 2>>::value);
