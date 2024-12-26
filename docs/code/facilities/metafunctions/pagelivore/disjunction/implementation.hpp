/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class...Predicates>
struct Disjunction
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        {(...||Predicates<Variables...>::value)};
    };
    
    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};

/*****************/
/**** Example ****/
/*****************/

/**** Pred_0 ****/
// Returns true if the argument is greater than 10.
template<auto...>
struct Pred_0
{ static constexpr bool value {false}; };

template<auto I>
requires (10 < I)
struct Pred_0<I>
{ static constexpr bool value {true}; };

/**** Pred_1 ****/
// Returns true if the argument is less than 0.
template<auto...>
struct Pred_1
{ static constexpr bool value {false}; };

template<auto I>
requires (I < 0)
struct Pred_1<I>
{ static constexpr bool value {true}; };

/**** Pred_2 ****/
// Returns true if the argument is even.
template<auto...>
struct Pred_2
{ static constexpr bool value {false}; };

template<auto I>
requires (I % 2 == 0)
struct Pred_2<I>
{ static constexpr bool value {true}; };

/**** Metafunction ****/
template<auto...Args>
using Metafunction = Disjunction<Pred_0, Pred_1, Pred_2>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction<-1>::value);
static_assert(Metafunction<2>::value);
static_assert(! Metafunction<5>::value);
static_assert(Metafunction<-2>::value);

// If no predicate is provided,
// the value is always `false`.
static_assert(! Disjunction<>::Page<1, 2, 3>::value);