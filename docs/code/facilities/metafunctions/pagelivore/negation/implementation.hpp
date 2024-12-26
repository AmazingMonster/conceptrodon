/************************/
/**** Implementation ****/
/************************/

template<template<auto...>  class Predicate>
struct Negation
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value 
        {not Predicate<Variables...>::value};
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};

/*****************/
/**** Example ****/
/*****************/

/**** IsLess ****/
template<auto First, auto Second>
struct IsLess
{
    static constexpr bool value
    {First < Second};
};

/**** IsNoLess ****/
template<auto...Args>
using IsNoLess = Negation<IsLess>::Page<Args...>;

/**** Tests ****/
static_assert(IsNoLess<1, 1>::value);
static_assert(IsNoLess<1, 0>::value);
static_assert(! IsNoLess<1, 2>::value);