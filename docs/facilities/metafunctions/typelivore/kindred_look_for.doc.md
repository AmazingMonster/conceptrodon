<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::KindredLookFor`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-kindred-look-for">To Index</a></p>

## Description

`Typelivore::KindredLookFor` accepts a list of elements and returns a function.

When invoked by a predicate, the function returns the index of the first element that satisfies the predicate, or `-1` if it cannot find the element.
This function is created to exhibit the power of fold expression and to compare with `Typelivore::Find`.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Pred
-> Preds&lt;E<sub>0</sub>&gt;::value ? 0 : (
   Preds&lt;E<sub>1</sub>&gt;::value ? 1 : (
      &vellip;
   Preds&lt;E<sub>n</sub>&gt;::value ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
KindredLookFor
 :: typename...
 -> template<typename...> class...
 -> auto
```

## Structure

```C++
template<typename...>
struct KindredLookFor
{
    template<template<typename...> class...>
    alias Road
    {
        static constexpr std::make_signed_t<size_t>
        value {RESULT};
    };

    template<template<typename...> class...>
    static constexpr std::make_signed_t<size_t>
    Road_v {RESULT};
};
```

## Examples

We will look for the indices of `int**` and `void` in list `int, int*, int**, int***`.

```C++
/**** IsIntDoubleStar ****/
template<typename Element>
struct IsIntDoubleStar
: public std::is_same<Element, int**> {};

/**** IsVoid ****/
template<typename Element>
struct IsVoid
: public std::is_same<Element, void> {};

/**** Metafunction ****/
template<template<typename...> class...Args>
using Metafunction = KindredLookFor<int, int*, int**, int**>
::Road<Args...>;

/**** Tests ****/
static_assert(Metafunction<IsIntDoubleStar>::value == 2);
static_assert(Metafunction<IsVoid>::value == -1);
```

## Implementation

The central part of the implementation is this immediately invoked lambda expression:

```C++
[]() -> std::make_signed_t<size_t>
{
    std::make_signed_t<size_t> counter {-1};
    return
    (...||(++counter, Predicate<Elements>::value)) ? 
    counter : -1;
}()
```

The function contains two main components:

1. A fold expression over `||`;
2. A counter that produces side effects.

The comma operator discards the result of counter incrementation, leaving the predicate's result to the fold expression.
The fold expression will short-circuit as soon as `true` is obtained.
Hence, the counter will stop incrementing once the right element is found.

If no element satisfies all the predicates, then the fold expression is evaluated to `false`. In that case, `-1` is returned.

Here's the entire implementation:

```C++
template<typename...Elements>
struct KindredLookFor
{
    template<template<typename...> class Predicate>
    struct ProtoRoad
    {
        static constexpr auto value
        {
            []() -> std::make_signed_t<size_t>
            {
                std::make_signed_t<size_t> counter {-1};
                return
                (...||(++counter, Predicate<Elements>::value)) ? 
                counter : -1;
            }()
        };
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/kindred_look_for/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/kindred_look_for.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/kindred_look_for.test.hpp)
