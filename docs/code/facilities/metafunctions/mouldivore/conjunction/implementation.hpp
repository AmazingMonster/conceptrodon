/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class...Predicates>
struct Conjunction
{
    template<typename...Elements>
    struct ProtoMold
    {
        static constexpr bool value
        {(...&&Predicates<Elements...>::value)};
    };
    
    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <type_traits>

/**** Pred_0 ****/
// Returns true if the argument is less than 10.
template<typename...>
struct Pred_0
{ static constexpr bool value {false}; };

template<typename I>
requires (I::value < 10)
struct Pred_0<I>
{ static constexpr bool value {true}; };

/**** Pred_1 ****/
// Returns true if the argument is greater than 0.
template<typename...>
struct Pred_1
{ static constexpr bool value {false}; };

template<typename I>
requires (0 < I::value)
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

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Conjunction<Pred_0, Pred_1, Pred_2>
::Mold<Args...>;

/**** Tests ****/
static_assert(Metafunction<std::integral_constant<int, 2>>::value);
static_assert(Metafunction<std::integral_constant<int, 4>>::value);
static_assert(! Metafunction<std::integral_constant<int, 5>>::value);
static_assert(! Metafunction<std::integral_constant<int, -2>>::value);

// If no predicate is provided,
// the value is always `true`.
static_assert
(
    Conjunction<>
    ::Mold
    <
        std::integral_constant<int, 1>,
        std::integral_constant<int, 2>,
        std::integral_constant<int, 3>
    >::value
);