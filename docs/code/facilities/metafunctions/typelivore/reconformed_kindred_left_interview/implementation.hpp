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

/***********************/
/**** First Example ****/
/***********************/

/**** Vay ****/
template<auto Variable>
struct Vay
{ static constexpr auto value{Variable}; };

/**** Metafunction ****/
template<typename...Args>
using Metafunction = ReconformedKindredLeftInterview<Vay<0>, Vay<0>, Vay<1>, Vay<2>, Vay<2>>
::Mold<Args...>;

/*** Tests ****/
static_assert
(Metafunction<Vay<2>>::Road<std::is_same>::value == 3);
static_assert
(Metafunction<Vay<-1>>::Road<std::is_same>::value == -1);

/************************/
/**** Second Example ****/
/************************/

/**** Less ****/
template<typename I, typename J>
struct Less
{
    static constexpr bool value
    {I::value < J::value};
};

/**** Tests ****/
static_assert
(Metafunction<Vay<1>>::Road<Less>::value == 3);