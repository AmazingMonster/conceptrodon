/**********************/
/**** Dependencies ****/
/**********************/

#include <cstddef>
#include <type_traits>

/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class...Predicates>
struct IndependentFind
{
    template<typename...>
    struct ProtoMold
    { static constexpr std::make_signed_t<size_t> value {-1}; };

    template<typename First>
    struct ProtoMold<First>
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

    template<typename First, typename Second, typename...Others>
    struct ProtoMold<First, Second, Others...>
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
                    ProtoMold<Others...>
                    ::value != -1
                )
                { 
                    return 2 + ProtoMold<Others...>
                    ::value; 
                }

                else
                { return -1; }
            }()
        };
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

/**** IsIntDoubleStar ****/
template<typename Element>
struct IsIntDoubleStar
: public std::is_same<Element, int**> {};

/**** Metafunction ****/
template<typename...Args>
using Metafunction = IndependentFind<IsIntDoubleStar>
::Mold<Args...>;

/**** Tests ****/
static_assert(Metafunction<int, int*, int**, int***>::value == 2);
static_assert(Metafunction<int, int*, int***>::value == -1);