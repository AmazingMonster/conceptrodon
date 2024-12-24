/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class...Predicates>
struct Disjunction
{
    template<typename...Elements>
    struct ProtoMold
    {
        static constexpr bool value
        {(...||Predicates<Elements...>::value)};
    };
    
    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <type_traits>

/**** Pred_0 ****/
// Returns true if the argument is greater than 10.
template<typename...>
struct Pred_0
{ static constexpr bool value {false}; };

template<typename I>
requires (10 < I::value)
struct Pred_0<I>
{ static constexpr bool value {true}; };

/**** Pred_1 ****/
// Returns true if the argument is less than 0.
template<typename...>
struct Pred_1
{ static constexpr bool value {false}; };

template<typename I>
requires (I::value < 0)
struct Pred_1<I>
{ static constexpr bool value {true}; };

/**** Pred_2 ****/
// Returns true if the argument is even.
template<typename...>
struct Pred_2
{ static constexpr bool value {false}; };

template<typename I>
requires (I::value % 2 == 0)
struct Pred_2<I>
{ static constexpr bool value {true}; };

/**** Metafuntion ****/
template<typename...Args>
using Metafunction = Disjunction<Pred_0, Pred_1, Pred_2>
::Mold<Args...>;

/**** Tests ****/
static_assert(Metafunction<std::integral_constant<int, -1>>::value);
static_assert(Metafunction<std::integral_constant<int, 2>>::value);
static_assert(! Metafunction<std::integral_constant<int, 5>>::value);
static_assert(Metafunction<std::integral_constant<int, -2>>::value);

// If no predicate is provided,
// the value is always `false`.
static_assert
(
    ! Disjunction<>
    ::Mold
    <
        std::integral_constant<int, 1>,
        std::integral_constant<int, 2>,
        std::integral_constant<int, 3>
    >::value
);