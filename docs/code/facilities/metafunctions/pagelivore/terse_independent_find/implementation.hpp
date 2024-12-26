/**********************/
/**** Dependencies ****/
/**********************/

#include <type_traits>
#include <cstddef>

/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class...Predicates>
struct TerseIndependentFind
{
    template<auto...>
    struct ProtoPage
    { static constexpr std::make_signed_t<size_t> value {-1}; };

    template<auto First>
    struct ProtoPage<First>
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

    template<auto First, auto Second, auto...Others>
    struct ProtoPage<First, Second, Others...>
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
                    ProtoPage<Others...>
                    ::value != -1
                )
                { 
                    return 2 + ProtoPage<Others...>
                    ::value; 
                }

                else
                { return -1; }
            }()
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

/**** IsTwo ****/
template<auto I>
struct IsTwo
: public std::bool_constant<I == 2> {};

/**** Metafunction ****/
template<auto...Args>
using Metafunction = TerseIndependentFind<IsTwo>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction<0, 1, 2, 3>::value == 2);
static_assert(Metafunction<0, 1, 3>::value == -1);