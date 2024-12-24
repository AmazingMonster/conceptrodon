/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/**** Prefix ****/
template<typename, size_t>
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
    template<template<typename...> class Predicate, Prefix<I>..., typename OnDuty, typename...RestElements>
    static consteval auto idyl()
    // We combine the results using a fold expression over `&&`.
    // The pack we are folding is `RestElements...`.
    -> std::bool_constant<(...&&Predicate<RestElements, OnDuty>::value)>;
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
                        ::template idyl<Predicate, Elements...>()
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