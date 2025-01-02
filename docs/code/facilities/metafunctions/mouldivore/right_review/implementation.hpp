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

/**** RightInspect ****/
template<typename>
struct RightInspect {};

template<size_t...I>
struct RightInspect<std::index_sequence<I...>> 
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
            typename RestElements::type,
            typename Inspector::type
        >
        ::value
    )>;
};

/**** RightReview ****/
template<template<typename...> class Predicate>
struct RightReview
{
    template<typename...Elements>
    struct ProtoMold
    {
        static constexpr bool value
        {
            []<size_t...I>(std::index_sequence<I...>)
            {
                return
                (...&&(
                    decltype
                    (
                        RightInspect<std::make_index_sequence<I>>
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

/**** IsNoeLess ****/
template<typename L, typename R>
struct IsNoLess
{
    static constexpr bool value
    { L::value >= R::value };

};

/**** Test ****/
static_assert
(
    RightReview<IsNoLess>
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
    ! RightReview<IsNoLess>
    ::Mold<Vay<1>, Vay<0>, Vay<2>, Vay<2>>
    ::value
);