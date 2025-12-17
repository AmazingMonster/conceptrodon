/**********************/
/**** Dependencies ****/
/**********************/

#include <type_traits>
#include <cstddef>

/************************/
/**** Implementation ****/
/************************/

template<typename...>
struct KindredLeftInterview
{
    template<typename...>
    struct ProtoMold
    {
        template<template<typename...> class...Predicates>
        struct ProtoRoad
        { static constexpr std::make_signed_t<size_t> value {-1}; };

        template<template<typename...> class...Agreements>
        using Road = ProtoRoad<Agreements...>;
    };

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};

template<typename First>
struct KindredLeftInterview<First>
{
    template<typename...LeftSides>
    struct ProtoMold
    {
        template<template<typename...> class...Predicates>
        struct ProtoRoad
        {   
            static constexpr auto value 
            {
                []() -> std::make_signed_t<size_t>
                {
                    if constexpr 
                    ((...&&Predicates<LeftSides..., First>::value))
                    { return 0; }

                    else
                    { return -1; }
                }()
            };
        };

        template<template<typename...> class...Agreements>
        using Road = ProtoRoad<Agreements...>;
    };

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};

template<typename First, typename Second, typename...Others>
struct KindredLeftInterview<First, Second, Others...>
{
    template<typename...LeftSides>
    struct ProtoMold
    {
        template<template<typename...> class...Predicates>
        struct ProtoRoad
        {   
            static constexpr auto value 
            {
                []() -> std::make_signed_t<size_t>
                {
                    if constexpr 
                    ((...&&Predicates<LeftSides..., First>::value))
                    { return 0; }

                    else if constexpr 
                    ((...&&Predicates<LeftSides..., Second>::value))
                    { return 1; }

                    else if constexpr
                    (
                        KindredLeftInterview<Others...>
                        ::template Mold<LeftSides...>
                        ::template Road<Predicates...>
                        ::value != -1
                    )
                    { 
                        return 2 + KindredLeftInterview<Others...>
                        ::template Mold<LeftSides...>
                        ::template Road<Predicates...>
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

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
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
using Metafunction = KindredLeftInterview<Vay<0>, Vay<0>, Vay<1>, Vay<2>, Vay<2>>
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