<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Find`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-find">To Index</a></p>

## Description

`Pagelivore::Find` accepts a list of predicates and returns a function.

When invoked, the function returns the index of the first argument that satisfies all predicates, or `-1` if it cannot find the argument.

<pre><code>   Preds...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> (...&&Preds&lt;Arg<sub>0</sub>&gt;::value) ? 0 : (
   (...&&Preds&lt;Arg<sub>1</sub>&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Arg<sub>n</sub>&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
Find
 :: template<auto...> class...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct Find
{
    template<auto...>
    alias Page
    {
        static constexpr std::make_signed_t<size_t> value
        {RESULT};
    };

    template<auto...>
    static constexpr std::make_signed_t<size_t> Page_v
    {RESULT};
};
```

## Examples

We will find the indices of `2` in list `0, 1, 2, 3` and `0, 1, 3`.

```C++
/**** IsTwo ****/
template<auto I>
struct IsTwo
: public std::bool_constant<I == 2> {};

/**** Metafunction ****/
template<auto...Args>
using Metafunction = Find<IsTwo>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction<0, 1, 2, 3>::value == 2);
static_assert(Metafunction<0, 1, 3>::value == -1);
```

## Implementation

`Pagelivore::Find` is implemented based on `Varybivore::KindredFind`. It changes the invocation order of the latter.

```C++
template<template<auto...> class...Predicates>
struct Find
{
    template<auto...Variables>
    using Page = Varybivore::KindredFind<Variables...>
    ::template ProtoRail<Predicates...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/find/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/find.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/find.test.hpp)
