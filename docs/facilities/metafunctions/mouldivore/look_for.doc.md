<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::LookFor`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-look-for">To Index</a></p>

## Description

`Mouldivore::LookFor` accepts a predicate and returns a function.

When invoked, the function returns the index of the first argument that satisfies the predicate, or `-1` if it cannot find the argument.

<pre><code>   Pred
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Pred&lt;Arg<sub>0</sub>&gt;::value ? 0 : (
   Pred&lt;Arg<sub>1</sub>&gt;::value ? 1 : (
            &vellip;
   Pred&lt;Arg<sub>n</sub>&gt;::value ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
LookFor
 :: template<typename...> class...
 -> typename...
 -> auto
```

## Structure

```C++
template<template<typename...> class>
struct LookFor
{
    template<typename...>
    alias Mold
    {
        static constexpr std::make_signed_t<size_t>
        value {RESULT};
    };

    template<template<typename...> class>
    static constexpr std::make_signed_t<size_t>
    Mold_v {RESULT};
};
```

## Examples

We will find the indices of `int**` in list `int, int*, int**, int***` and `int, int*, int***`.

```C++
/**** IsIntDoubleStar ****/
template<typename Element>
struct IsIntDoubleStar
: public std::is_same<Element, int**> {};

/**** Metafunction ****/
template<typename...Args>
using Metafunction = LookFor<IsIntDoubleStar>
::Mold<Args...>;

/**** Tests ****/
static_assert(Metafunction<int, int*, int**, int***>::value == 2);
static_assert(Metafunction<int, int*, int***>::value == -1);
```

## Implementation

The central part of the implementation is this immediately invoked lambda expression:

```C++
[]() -> std::make_signed_t<size_t>
{
    std::make_signed_t<size_t> counter {-1};
    return
    (...||(++counter, static_cast<bool>(Predicate<Elements>::value))) ? 
    counter : -1;
}()
```

The function contains two main components:

1. A fold expression over `||`;
2. A counter that produces side effects.

The comma operator discards the result of counter incrementation, leaving the predicate's result to the fold expression.
The fold expression will short-circuit as soon as `true` is obtained.
Hence, the counter will stop incrementing once the right element is found.

If no element satisfies the predicate, then the fold expression is evaluated to `false`. In that case, `-1` is returned.

Here's the entire implementation:

```C++
template<template<typename...> class Predicate>
struct LookFor
{
    template<typename...Elements>
    struct ProtoMold
    {
        static constexpr auto value
        {
            []() -> std::make_signed_t<size_t>
            {
                std::make_signed_t<size_t> counter {-1};
                return
                (...||(++counter, static_cast<bool>(Predicate<Elements>::value))) ? 
                counter : -1;
            }()
        };
    };
        template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/look_for/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/mouldivore/look_for.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/look_for.test.hpp)
