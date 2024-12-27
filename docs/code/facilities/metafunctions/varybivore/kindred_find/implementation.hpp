/**********************/
/**** Dependencies ****/
/**********************/

#include <type_traits>
#include <cstddef>

/************************/
/**** Implementation ****/
/************************/

template<auto...>
struct KindredFind
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    { static constexpr std::make_signed_t<size_t> value {-1}; };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

template<auto First>
struct KindredFind<First>
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {   
        static constexpr auto value 
        {
            []() -> std::make_signed_t<size_t>
            {
                if constexpr ((...&&Predicates<First>::value))
                { return 0; }

                else
                { return -1; }
            }()
        };
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

template<auto First, auto Second, auto...Others>
struct KindredFind<First, Second, Others...>
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {   
        static constexpr auto value 
        {
            []() -> std::make_signed_t<size_t>
            {
                if constexpr
                ((...&&Predicates<First>::value))
                { return 0; }

                else if constexpr
                ((...&&Predicates<Second>::value))
                { return 1; }

                else if constexpr
                (
                    KindredFind<Others...>
                    ::template ProtoRail<Predicates...>
                    ::value != -1
                )
                { 
                    return 2 + KindredFind<Others...>
                    ::template ProtoRail<Predicates...>
                    ::value; 
                }

                else
                { return -1; }
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
using Metafunction = KindredFind<0, 1, 2, 3>
::Rail<Args...>;

/**** Tests ****/
static_assert(Metafunction<IsTwo>::value == 2);
static_assert(Metafunction<IsMinusOne>::value == -1);