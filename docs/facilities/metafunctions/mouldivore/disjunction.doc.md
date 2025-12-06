<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Disjunction`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-disjuction">To Index</a></p>

## Description

`Mouldivore::Disjunction` accepts a list of predicates and returns a function.

When invoked, the function returns true if its argument list satisfies any of the predicates and returns false if otherwise.

<pre><code>   Preds...
-> Args...
-> ... || Preds&lt;Args...&gt;::value</code></pre>

## Type Signature

```Haskell
Disjunction
 :: template<typename...> class... 
 -> typename...
 -> auto
```

## Structure

```C++
template<template<typename...> class...>
struct Disjunction
{
    template<typename...>
    alias Mold
    {
        static constexpr bool value
        {RESULT};
    };
    
    template<auto...>
    static constexpr bool Mold_v
    {RESULT};
};
```

## Examples

We will combine `Pred_0`, `Pred_1`, and `Pred_2` into a new predicate using `Disjunction`.

```C++
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
```

## Implementation

We will implement `Disjunction` using a fold expression.

Note that we are not providing an initiator. The default initiator for `||` is `false`. We place `...` on the left side of the expression to do a left-fold.

<pre><code>   ... || Predicates&lt;Elements...&gt;::value
-> false || ... || Predicates&lt;Elements...&gt;::value
-> (...((
       false
    || Predicate<sub>0</sub>&lt;Elements...&gt;::value)
    || Predicate<sub>1</sub>&lt;Elements...&gt;::value)
    || ...
    || Predicate<sub>Last-1</sub>&lt;Elements...&gt;::value)
    || Predicate<sub>Last</sub>&lt;Elements...&gt;::value
</code></pre>

In our case, left-fold and right-fold produce the same result since `||` is commutative.

Here's the entire implementation:

```C++
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
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/disjunction/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/disjunction.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/disjunction.test.hpp)
