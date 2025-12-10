<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Conjunction`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-conjunction">To Index</a></p>

## Description

`Pagelivore::Conjunction` accepts a list of predicates and returns a function.

When invoked, the function returns true if its argument list satisfies all of the predicates and returns false if otherwise.

<pre><code>   Preds...
-> Args...
-> ... && Preds&lt;Args...&gt;::value</code></pre>

## Type Signature

```Haskell
Conjunction
 :: template<auto...> class... 
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct Conjunction
{
    template<auto...>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };
    
    template<auto...>
    static constexpr bool Page_v
    {RESULT};
};
```

## Examples

We will combine `Pred_0`, `Pred_1`, and `Pred_2` into a new predicate using `Conjunction`.

```C++
/**** Pred_0 ****/
// Returns true if the argument is less than 10.
template<auto...>
struct Pred_0
{ static constexpr bool value {false}; };

template<auto I>
requires (I < 10)
struct Pred_0<I>
{ static constexpr bool value {true}; };

/**** Pred_1 ****/
// Returns true if the argument is greater than 0.
template<auto...>
struct Pred_1
{ static constexpr bool value {false}; };

template<auto I>
requires (0 < I)
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
using Metafunction = Conjunction<Pred_0, Pred_1, Pred_2>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction<2>::value);
static_assert(Metafunction<4>::value);
static_assert(! Metafunction<5>::value);
static_assert(! Metafunction<-2>::value);

// If no predicate is provided,
// the value is always `true`.
static_assert(Conjunction<>::Page<1, 2, 3>::value);
```

## Implementation

We will implement `Conjunction` using a fold expression.

Note that we are not providing an initiator. The default initiator for `&&` is `true`. We place `...` on the left side of the expression to do a left-fold.

<pre><code>   ... && Predicates&lt;Variables...&gt;::value
-> true && ... && Predicates&lt;Variables...&gt;::value
-> (...((
       true
    && Predicate<sub>0</sub>&lt;Variables...&gt;::value)
    && Predicate<sub>1</sub>&lt;Variables...&gt;::value)
    && ...
    && Predicate<sub>Last-1</sub>&lt;Variables...&gt;::value)
    && Predicate<sub>Last</sub>&lt;Variables...&gt;::value
</code></pre>

In our case, left-fold and right-fold produce the same result since `&&` is commutative.

Here's the entire implementation:

```C++
template<template<auto...> class...Predicates>
struct Conjunction
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        {(...&&Predicates<Variables...>::value)};
    };
    
    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/conjunction/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/conjunction.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/conjunction.test.hpp)
