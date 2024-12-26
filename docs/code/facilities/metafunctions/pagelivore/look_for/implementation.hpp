/**********************/
/**** Dependencies ****/
/**********************/

#include <type_traits>
#include <cstddef>

/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class Predicate>
struct LookFor
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr auto value
        {
            []() -> std::make_signed_t<size_t>
            {
                std::make_signed_t<size_t> counter {-1};
                return
                (...||( (++counter, Predicate<Variables>::value) ? true : false)) ? 
                counter : -1;
            }()
        };
    };
        template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};

/*****************/
/**** Example ****/
/*****************/

/**** IsTwo ****/
template<auto I>
struct IsTwo
: public std::bool_constant<I == 2> {};

/**** IsMinusOne ****/
template<auto I>
struct IsMinusOne
: public std::bool_constant<I == -1> {};

/**** Tests ****/
static_assert(LookFor<IsTwo>::Page<0, 1, 2, 2>::value == 2);
static_assert(LookFor<IsMinusOne>::Page<0, 1, 2, 2>::value == -1);