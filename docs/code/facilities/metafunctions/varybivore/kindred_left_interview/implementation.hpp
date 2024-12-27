/**********************/
/**** Dependencies ****/
/**********************/

#include <type_traits>
#include <cstddef>

/************************/
/**** Implementation ****/
/************************/

template<auto...>
struct KindredLeftInterview
{
    template<auto...>
    struct ProtoPage
    {
        template<template<auto...> class...Predicates>
        struct ProtoRail
        { static constexpr std::make_signed_t<size_t> value {-1}; };

        template<template<auto...> class...Agreements>
        using Rail = ProtoRail<Agreements...>;
    };

    template<auto...Args>
    using Page = ProtoPage<Args...>;
};

template<auto First>
struct KindredLeftInterview<First>
{
    template<auto...LeftSides>
    struct ProtoPage
    {
        template<template<auto...> class...Predicates>
        struct ProtoRail
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

        template<template<auto...> class...Agreements>
        using Rail = ProtoRail<Agreements...>;
    };

    template<auto...Args>
    using Page = ProtoPage<Args...>;
};

template<auto First, auto Second, auto...Others>
struct KindredLeftInterview<First, Second, Others...>
{
    template<auto...LeftSides>
    struct ProtoPage
    {
        template<template<auto...> class...Predicates>
        struct ProtoRail
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
                        ::template Page<LeftSides...>
                        ::template Rail<Predicates...>
                        ::value != -1
                    )
                    { 
                        return 2 + KindredLeftInterview<Others...>
                        ::template Page<LeftSides...>
                        ::template Rail<Predicates...>
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

    template<auto...Args>
    using Page = ProtoPage<Args...>;
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
using Metafunction = KindredLeftInterview<0, 1, 2, 2>
::Page<Args...>;

/**** Tests ****/
static_assert
(Metafunction<2>::Rail<Equal>::value == 2);
static_assert
(Metafunction<-1>::Rail<Equal>::value == -1);