/**********************/
/**** Dependencies ****/
/**********************/

#include <type_traits>
#include <cstddef>

/************************/
/**** Implementation ****/
/************************/

template<auto...Variables>
struct KindredLookFor
{
    template<template<auto...> class Predicate>
    struct ProtoRail
    {
        static constexpr auto value
        {
            []() -> std::make_signed_t<size_t>
            {
                std::make_signed_t<size_t> counter {-1};
                return
                (...||(++counter, Predicate<Variables>::value)) ? 
                counter : -1;
            }()
        };
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
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
: public std::bool_constant<I==-1> {};

/**** Metafunction ****/
template<template<auto...> class...Args>
using Metafunction = KindredLookFor<0, 1, 2, 3>
::Rail<Args...>;

/**** Tests ****/
static_assert(Metafunction<IsTwo>::value == 2);
static_assert(Metafunction<IsMinusOne>::value == -1);