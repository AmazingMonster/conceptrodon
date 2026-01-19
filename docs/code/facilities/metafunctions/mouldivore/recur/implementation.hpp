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
struct Recur
{
    template<template<typename...> class...LessonsLearned>
    struct ProtoRoad
    {
        template<typename...Sacrifices>
        static consteval auto idyl()
        {
            if constexpr 
            (
                // `LessonsLearned...` are the predicates.
                (...&&LessonsLearned<
                    // `History` is the operation that will recur.
                    History<
                        Sacrifices...
                    >
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
                    History<
                    History<
                        Sacrifices...
                    >
                    >
                >::value)
            )
            {
                return Tyy<History<
                    History<
                        Sacrifices...
                    >
                >>{};
            }

            else
            {
                return idyl<
                    History<
                    History<
                        Sacrifices...
                    >
                    >
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
struct AddOneHelper
{
    using type = Vay<Val::value + 1>;
};

template<typename...Args>
using AddOne  = AddOneHelper<Args...>::type;

/**** IsGreaterThanNine ****/
template<typename Val>
struct IsGreaterThanNine
{
    static constexpr auto value
    {Val::value > 9};
};

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Recur<AddOne>
::Road<IsGreaterThanNine>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Vay<10>;

/**** Result ****/
using Result_0 = Metafunction<Vay<0>>;
using Result_1 = Metafunction<Vay<-1>>;

/**** Tests ****/
static_assert(std::same_as<Result_0, SupposedResult>);
static_assert(std::same_as<Result_1, SupposedResult>);
