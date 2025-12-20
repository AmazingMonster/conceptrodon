<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::KindredLookFor`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-kindred-look-for">To Index</a></p>

## Description

`Varybivore::KindredLookFor` accepts a list of variables and returns a function.

When invoked by a predicate, the function returns the index of the first variable that satisfies the predicate, or `-1` if it cannot find the variable.
This function is created to exhibit the power of fold expression and to compare with `Varybivore::Find`.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Pred
-> Preds&lt;V<sub>0</sub>&gt;::value ? 0 : (
   Preds&lt;V<sub>1</sub>&gt;::value ? 1 : (
      &vellip;
   Preds&lt;V<sub>n</sub>&gt;::value ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
KindredLookFor
 :: auto...
 -> template<auto...> class...
 -> auto
```

## Structure

```C++
template<auto...>
struct KindredLookFor
{
    template<template<auto...> class>
    alias Rail
    {
        static constexpr std::make_signed_t<size_t>
        value {RESULT};
    };

    template<template<auto...> class>
    static constexpr std::make_signed_t<size_t>
    Rail_v {RESULT};
};
```

## Examples

We will look for the indices of `2` and `-1` in list `0, 1, 2, 2`.

```C++
/**** IsTwo ****/
template<auto I>
struct IsTwo
: public std::bool_constant<I == 2> {};

/**** IsMinusOne ****/
template<auto I>
struct IsMinusOne
: public std::bool_constant<I==-1> {};

/**** Metafunction ****/
template<template<auto...> class...Args>
using Metafunction = KindredLookFor<0, 1, 2, 3>
::Rail<Args...>;

/**** Tests ****/
static_assert(Metafunction<IsTwo>::value == 2);
static_assert(Metafunction<IsMinusOne>::value == -1);
```

## Implementation

The central part of the implementation is this immediately invoked lambda expression:

```C++
[]() -> std::make_signed_t<size_t>
{
    std::make_signed_t<size_t> counter {-1};
    return
    (...||(++counter, Predicate<Variables>::value)) ? 
    counter : -1;
}()
```

The function contains two main components:

1. A fold expression over `||`;
2. A counter that produces side effects.

The comma operator discards the result of counter incrementation, leaving the predicate's result to the fold expression.
The fold expression will short-circuit as soon as `true` is obtained.
Hence, the counter will stop incrementing once the right variable is found.

If no variable satisfies the predicate, then the fold expression is evaluated to `false`. In that case, `-1` is returned.

Here's the entire implementation:

```C++
template<auto...Variables>
struct KindredLookFor
{
    template<template<auto...> class Predicate>
    struct ProtoRail
    {
        static constexpr auto value
        {
            []() -> std::make_signed_t<size_t>
            {
                std::make_signed_t<size_t> counter {-1};
                return
                (...||(++counter, Predicate<Variables>::value)) ? 
                counter : -1;
            }()
        };
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/kindred_look_for/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/kindred_look_for.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/kindred_look_for.test.hpp)
