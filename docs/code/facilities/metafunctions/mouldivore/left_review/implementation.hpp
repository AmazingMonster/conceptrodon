/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/**** Prefix ****/
template<typename, auto>
concept Prefix = true;

/************************/
/**** Implementation ****/
/************************/

/**** LeftInspect ****/
template<typename>
struct LeftInspect {};

template<size_t...I>
struct LeftInspect<std::index_sequence<I...>> 
{
    template
    <
        template<typename...> class Predicate,
        typename Inspector,
        typename...RestElements
    >
    static consteval auto idyl
    (
        Prefix<I> auto...,
        Inspector,
        RestElements...
    )
    -> std::bool_constant
    <(...&&
        Predicate
        <
            typename Inspector::type,
            typename RestElements::type
        >
        ::value
    )>;
};

/**** LeftReview ****/
template<template<typename...> class Predicate>
struct LeftReview
{
    template<typename...Elements>
    struct ProtoMold
    {
        static constexpr bool value
        {
            // Immediately invoked lambda.
            []<size_t...I>(std::index_sequence<I...>)
            {
                return
                (...&&(
                    decltype
                    (
                        LeftInspect<std::make_index_sequence<I>>
                        ::template idyl<Predicate>(std::type_identity<Elements>{}...)
                    )::value
                ));
            }(std::make_index_sequence<sizeof...(Elements) - 1>{})
        }; 
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};

/***********************/
/**** First Example ****/
/***********************/

#include <type_traits>

/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** IsNoGreater ****/
template<typename L, typename R>
struct IsNoGreater
{
    static constexpr bool value
    { L::value <= R::value };

};

/**** Test ****/
static_assert
(
    LeftReview<IsNoGreater>
    ::Mold<Vay<0>, Vay<1>, Vay<2>, Vay<2>>
    ::value
);

/************************/
/**** Second Example ****/
/************************/

/**** Test ****/
// Reverse Vay<0> and Vay<1>
static_assert
(
    ! LeftReview<IsNoGreater>
    ::Mold<Vay<1>, Vay<0>, Vay<2>, Vay<2>>
    ::value
);