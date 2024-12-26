/**********************/
/**** Dependencies ****/
/**********************/

#include <type_traits>
#include <cstddef>

/**** Varybivore::SensibleRightInterview ****/
namespace Varybivore {

template<auto...>
struct SensibleRightInterview
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...>
        struct ProtoPage
        { static constexpr auto value {-1}; };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<template<auto...> class...Predicates>
    using Rail = ProtoRail<Predicates...>;
};

template<auto First>
struct SensibleRightInterview<First>
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...RightSides>
        struct ProtoPage
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

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

template<auto First, auto Second, auto...Others>
struct SensibleRightInterview<First, Second, Others...>
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...RightSides>
        struct ProtoPage
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
                        ::template Rail<Predicates...>
                        ::template Page<RightSides...>
                        ::value != -1
                    )
                    { 
                        return 2 + SensibleRightInterview<Others...>
                        ::template Rail<Predicates...>
                        ::template Page<RightSides...>
                        ::value; 
                    }

                    else
                    { return -1; }
                }()
            };
        };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

}

/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class...Predicates>
struct RightInterview
{
    template<auto...Interviewers>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = Varybivore::SensibleRightInterview<Variables...>
        ::template ProtoRail<Predicates...>
        ::template ProtoPage<Interviewers...>;
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};

/*****************/
/**** Example ****/
/*****************/

/**** Equal ****/
template<auto I, auto J>
struct Equal
{
    static constexpr bool value
    {I == J};
};

/**** Metafunction ****/
template<auto...Args>
using Metafunction = RightInterview<Equal>
::Page<Args...>;

/**** Tests ****/
static_assert
(Metafunction<2>::Page<0, 1, 2, 2>::value == 2);
static_assert
(Metafunction<-1>::Page<0, 1, 2, 2>::value == -1);