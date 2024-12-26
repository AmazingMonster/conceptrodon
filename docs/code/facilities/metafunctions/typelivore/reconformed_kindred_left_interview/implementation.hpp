/**********************/
/**** Dependencies ****/
/**********************/

#include <type_traits>
#include <cstddef>

/************************/
/**** Implementation ****/
/************************/

template<
    template<typename...> class,
    typename,
    typename...
>
struct UnconformedLeftInterview
{ static constexpr std::make_signed_t<size_t> value {-1}; };

template<
    template<typename...> class Predicate,
    typename Interviewer,
    typename First
>
struct UnconformedLeftInterview<Predicate, Interviewer, First>
{
    static constexpr auto value 
    {
        []() -> std::make_signed_t<size_t>
        {
            if constexpr 
            (Predicate<Interviewer, First>::value)
            { return 0; }

            else
            { return -1; }
        }()
    };
};

template<
    template<typename...> class Predicate,
    typename Interviewer,
    typename First, typename Second, typename...Others
>
struct UnconformedLeftInterview<
    Predicate,
    Interviewer,
    First, Second, Others...
>
{
    static constexpr auto value 
    {
        []() -> std::make_signed_t<size_t>
        {
            if constexpr 
            (Predicate<Interviewer, First>::value)
            { return 0; }

            else if constexpr 
            (Predicate<Interviewer, Second>::value)
            { return 1; }

            else if constexpr
            (
                UnconformedLeftInterview<
                    Predicate, 
                    Interviewer, 
                    Others...
                >::value != -1
            )
            { 
                return 2 + UnconformedLeftInterview<
                    Predicate, 
                    Interviewer, 
                    Others...
                >::value; 
            }

            else
            { return -1; }
        }()
    };
};

template<typename...Elements>
struct ReconformedKindredLeftInterview
{
    template<typename Interviewer>
    struct ProtoMold 
    {
        template<template<typename...> class Operation>
        using Road = UnconformedLeftInterview
        <Operation, Interviewer, Elements...>;

        template<template<typename...> class Operation>
        static constexpr auto Road_v 
        {
            UnconformedLeftInterview
            <Operation, Interviewer, Elements...>::value
        };
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

/**** Metafuntion ****/
template<typename...Args>
using Metafunction = ReconformedKindredLeftInterview<int, int*, int**, int**>
::Mold<Args...>;

/**** Test ****/
static_assert
(Metafunction<int**>::Road<std::is_same>::value == 2);
static_assert
(Metafunction<void>::Road<std::is_same>::value == -1);