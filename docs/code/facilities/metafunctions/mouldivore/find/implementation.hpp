/**********************/
/**** Dependencies ****/
/**********************/

#include <type_traits>
#include <cstddef>

/**** Typelivore::KindredFind ****/
namespace Typelivore {

template<typename...>
struct KindredFind
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    { static constexpr auto value {-1}; };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template<typename First>
struct KindredFind<First>
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
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

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template<typename First, typename Second, typename...Others>
struct KindredFind<First, Second, Others...>
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
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
                    ::template ProtoRoad<Predicates...>
                    ::value != -1
                )
                { 
                    return 2 + KindredFind<Others...>
                    ::template ProtoRoad<Predicates...>
                    ::value; 
                }

                else
                { return -1; }
            }()
        };
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

}

/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class Predicate>
struct Find
{
    template<typename...Elements>
    using Mold = Typelivore::KindredFind<Elements...>
    ::template Road<Predicate>;
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
using Metafunction = Find<IsIntDoubleStar>
::Mold<Args...>;

/**** Tests ****/
static_assert(Metafunction<int, int*, int**, int***>::value == 2);
static_assert(Metafunction<int, int*, int***>::value == -1);