/**********************/
/**** Dependencies ****/
/**********************/

#include <type_traits>
#include <cstddef>

/**** Varybivore::KindredFind ****/
namespace Varybivore {

template<auto...>
struct KindredFind
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    { static constexpr auto value {-1}; };

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

}

/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class...Predicates>
struct Find
{
    template<auto...Variables>
    using Page = Varybivore::KindredFind<Variables...>
    ::template ProtoRail<Predicates...>;
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
using Metafunction = Find<IsTwo>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction<0, 1, 2, 3>::value == 2);
static_assert(Metafunction<0, 1, 3>::value == -1);