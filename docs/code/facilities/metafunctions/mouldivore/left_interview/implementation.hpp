/**********************/
/**** Dependencies ****/
/**********************/

#include <type_traits>
#include <cstddef>

/**** Typelivore::SensibleLeftInterview ****/
namespace Typelivore {

template<typename...>
struct SensibleLeftInterview
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

}

/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class...Predicates>
struct LeftInterview
{
    template<typename...Interviewers>
    struct ProtoMold
    {
        template<typename...Elements>
        using Mold = Typelivore::SensibleLeftInterview<Elements...>
        ::template ProtoRoad<Predicates...>
        ::template ProtoMold<Interviewers...>;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <type_traits>

/****  Metafunction ****/
template<typename...Args>
using Metafunction = LeftInterview<std::is_same>
::Mold<Args...>;

/**** Tests ****/
static_assert
(Metafunction<int**>::Mold<int, int*, int**, int**>::value == 2);
static_assert
(Metafunction<void>::Mold<int, int*, int**, int**>::value == -1);