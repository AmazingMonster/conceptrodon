/**********************/
/**** Dependencies ****/
/**********************/

#include <type_traits>
#include <cstddef>

/**** Typelivore::SensibleRightInterview ****/
namespace Typelivore {

template<typename...>
struct SensibleRightInterview
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        template<typename...>
        struct ProtoMold
        { static constexpr auto value {-1}; };

        template<typename...Agreements>
        using Mold = ProtoMold<Agreements...>;
    };

    template<template<typename...> class...Predicates>
    using Road = ProtoRoad<Predicates...>;
};

template<typename First>
struct SensibleRightInterview<First>
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        template<typename...RightSides>
        struct ProtoMold
        {   
            static constexpr auto value 
            {
                []() -> std::make_signed_t<size_t>
                {
                    if constexpr 
                    ((...&&Predicates<First, RightSides...>::value))
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
struct SensibleRightInterview<First, Second, Others...>
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        template<typename...RightSides>
        struct ProtoMold
        {   
            static constexpr auto value 
            {
                []() -> std::make_signed_t<size_t>
                {
                    if constexpr 
                    ((...&&Predicates<First, RightSides...>::value))
                    { return 0; }

                    else if constexpr 
                    ((...&&Predicates<Second, RightSides...>::value))
                    { return 1; }

                    else if constexpr
                    (
                        SensibleRightInterview<Others...>
                        ::template Road<Predicates...>
                        ::template Mold<RightSides...>
                        ::value != -1
                    )
                    { 
                        return 2 + SensibleRightInterview<Others...>
                        ::template Road<Predicates...>
                        ::template Mold<RightSides...>
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

}

/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class...Predicates>
struct RightInterview
{
    template<typename...Interviewers>
    struct ProtoMold
    {
        template<typename...Elements>
        using Mold = Typelivore::SensibleRightInterview<Elements...>
        ::template ProtoRoad<Predicates...>
        ::template Mold<Interviewers...>;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
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
using Metafunction = RightInterview<std::is_same>
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
using Metafunction_2 = RightInterview<Less>
::Mold<Args...>;

/**** Tests ****/
static_assert
(Metafunction_2<Vay<1>>::Mold<Vay<0>, Vay<0>, Vay<1>, Vay<2>, Vay<2>>::value == 0);