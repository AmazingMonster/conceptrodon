/**********************/
/**** Dependencies ****/
/**********************/

#include <cstddef>
#include <type_traits>

/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class...Predicates>
struct IndependentLeftInterview
{
    template<typename...LeftSides>
    struct ProtoMold
    {
        struct Slash
        {
            template<typename...>
            struct ProtoMold
            { static constexpr auto value {-1}; };

            template<typename First>
            struct ProtoMold<First>
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

            template<typename First, typename Second, typename...Others>
            struct ProtoMold<First, Second, Others...>
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
        };
        
        template<typename...Agreements>
        using Mold = Slash::template ProtoMold<Agreements...>;
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
using Metafunction = IndependentLeftInterview<std::is_same>
::Mold<Args...>;

/*** Tests ****/
static_assert
(Metafunction<Vay<2>>::Mold<Vay<0>, Vay<0>, Vay<1>, Vay<2>, Vay<2>>::value == 3);
static_assert
(Metafunction<Vay<-1>>::Mold<Vay<0>, Vay<0>, Vay<1>, Vay<2>, Vay<2>>::value == -1);

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

/**** Metafunction ****/
template<typename...Args>
using Metafunction_1 = IndependentLeftInterview<Less>
::Mold<Args...>;

/**** Tests ****/
static_assert
(Metafunction_1<Vay<1>>::Mold<Vay<0>, Vay<0>, Vay<1>, Vay<2>, Vay<2>>::value == 3);