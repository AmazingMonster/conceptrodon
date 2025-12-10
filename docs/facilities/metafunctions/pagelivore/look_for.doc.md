<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::LookFor`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-look-for">To Index</a></p>

## Description

`Pagelivore::LookFor` accepts a predicate and returns a function.

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
 :: template<auto...> class...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class>
struct LookFor
{
    template<auto...>
    alias Page
    {
        static constexpr std::make_signed_t<size_t>
        value {RESULT};
    };

    template<template<auto...> class>
    static constexpr std::make_signed_t<size_t>
    Page_v {RESULT};
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
: public std::bool_constant<I == -1> {};

/**** Tests ****/
static_assert(LookFor<IsTwo>::Page<0, 1, 2, 2>::value == 2);
static_assert(LookFor<IsMinusOne>::Page<0, 1, 2, 2>::value == -1);
```

## Implementation

The central part of the implementation is this immediately invoked lambda expression:

```C++
[]() -> std::make_signed_t<size_t>
{
    std::make_signed_t<size_t> counter {-1};
    return
    (...||( (++counter, Predicate<Variables>::value) ? true : false)) ? 
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
template<template<auto...> class Predicate>
struct LookFor
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr auto value
        {
            []() -> std::make_signed_t<size_t>
            {
                std::make_signed_t<size_t> counter {-1};
                return
                (...||( (++counter, Predicate<Variables>::value) ? true : false)) ? 
                counter : -1;
            }()
        };
    };
        template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/look_for/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/look_for.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/look_for.test.hpp)
