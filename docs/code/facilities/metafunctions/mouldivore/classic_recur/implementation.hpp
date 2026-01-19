/**********************/
/**** Dependencies ****/
/**********************/

/**** Tyy ****/
template<typename Element>
struct Tyy
{
    using type = Element;
};

/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class History>
struct ClassicRecur
{
    template<template<typename...> class...LessonsLearned>
    struct ProtoRoad
    {
        // `Sacrifices` are the arguments that will initiate `Operation`.
        template<typename...Sacrifices>
        static consteval auto idyl()
        {
            if constexpr 
            (
                // `LessonsLearned...` are the predicates.
                (...&&LessonsLearned<
                    // `History` is the operation that will recur.
                    typename History<
                        Sacrifices...
                    >::type
                >::value)
            )
            {
                return Tyy<History<
                        Sacrifices...
                >>{};
            }
            
            else if constexpr 
            (
                (...&&LessonsLearned<
                    typename History<
                    typename History<
                        Sacrifices...
                    >::type
                    >::type
                >::value)
            )
            {
                return Tyy<History<
                    typename History<
                        Sacrifices...
                    >::type
                >>{};
            }

            else
            {
                return idyl<
                    typename History<
                    typename History<
                        Sacrifices...
                    >::type
                    >::type
                >();
            }
        }

        template<typename...Sacrifices>
        using Mold = decltype(idyl<Sacrifices...>())::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** AddOne ****/
template<typename Val>
struct AddOne
{
    using type = Vay<Val::value + 1>;
};

/**** IsGreaterThanNine ****/
template<typename Val>
struct IsGreaterThanNine
{
    static constexpr auto value
    {Val::value > 9};
};

/**** Metafunction ****/
template<typename...Args>
using Metafunction = ClassicRecur<AddOne>
::Road<IsGreaterThanNine>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Vay<10>;

/**** Results ****/
using Result_0 = Metafunction<Vay<0>>::type;
using Result_1 = Metafunction<Vay<-1>>::type;

/**** Tests ****/
static_assert(std::same_as<Result_0, SupposedResult>);
static_assert(std::same_as<Result_1, SupposedResult>);