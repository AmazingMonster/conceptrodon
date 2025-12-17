/**********************/
/**** Dependencies ****/
/**********************/

#include <type_traits>
#include <cstddef>

/************************/
/**** Implementation ****/
/************************/

template<typename...>
struct SensibleLeftInterview
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        template<typename...>
        struct ProtoMold
        { static constexpr std::make_signed_t<size_t> value {-1}; };

        template<typename...Agreements>
        using Mold = ProtoMold<Agreements...>;
    };

    template<template<typename...> class...Predicates>
    using Road = ProtoRoad<Predicates...>;
};

template<typename First>
struct SensibleLeftInterview<First>
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        template<typename...LeftSides>
        struct ProtoMold
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

        template<typename...Agreements>
        using Mold = ProtoMold<Agreements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template<typename First, typename Second, typename...Others>
struct SensibleLeftInterview<First, Second, Others...>
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        template<typename...LeftSides>
        struct ProtoMold
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
                        SensibleLeftInterview<Others...>
                        ::template Road<Predicates...>
                        ::template Mold<LeftSides...>
                        ::value != -1
                    )
                    { 
                        return 2 + SensibleLeftInterview<Others...>
                        ::template Road<Predicates...>
                        ::template Mold<LeftSides...>
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

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
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
using Metafunction = SensibleLeftInterview<Vay<0>, Vay<0>, Vay<1>, Vay<2>, Vay<2>>
::Road<std::is_same>::Mold<Args...>;

/*** Tests ****/
static_assert
(Metafunction<Vay<2>>::value == 3);
static_assert
(Metafunction<Vay<-1>>::value == -1);

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

/**** Metafunction_1 ****/
template<typename...Args>
using Metafunction_1 = SensibleLeftInterview<Vay<0>, Vay<0>, Vay<1>, Vay<2>, Vay<2>>
::Road<Less>::Mold<Args...>;

/**** Tests ****/
static_assert
(Metafunction_1<Vay<1>>::value == 3);