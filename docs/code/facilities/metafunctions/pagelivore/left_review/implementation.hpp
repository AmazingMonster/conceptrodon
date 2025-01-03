/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/**** Prefix ****/
template<typename, auto>
concept Prefix = true;

/**** Vay ****/
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };

/************************/
/**** Implementation ****/
/************************/

template<typename>
struct LeftInspect {};

template<size_t...I>
struct LeftInspect<std::index_sequence<I...>> 
{
    template
    <
        template<auto...> class Predicate,
        typename Inspector,
        typename...RestArgs
    >
    static consteval auto idyl
    (
        Prefix<I> auto...,
        Inspector,
        RestArgs...
    )
    -> std::bool_constant
    <(...&&
        Predicate
        <
            Inspector::value,
            RestArgs::value
        >
        ::value
    )>;
};

template<template<auto...> class Predicate>
struct LeftReview
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        {
            []<size_t...I>(std::index_sequence<I...>)
            {
                return
                (...&&(
                    decltype
                    (
                        LeftInspect<std::make_index_sequence<I>>
                        ::template idyl<Predicate>(Vay<Variables>{}...)
                    )::value
                ));
            }(std::make_index_sequence<sizeof...(Variables) - 1>{})
        }; 
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};

/***********************/
/**** First Example ****/
/***********************/

/**** IsNoGreater ****/
template<auto L, auto R>
struct IsNoGreater
{
    static constexpr bool value
    { L<= R };
};

/**** Test ****/
static_assert(LeftReview<IsNoGreater>::Page<0, 1, 2, 2>::value);

/************************/
/**** Second Example ****/
/************************/

// Reverse 0 and 1
static_assert(! LeftReview<IsNoGreater>::Page<1, 0, 2, 2>::value);