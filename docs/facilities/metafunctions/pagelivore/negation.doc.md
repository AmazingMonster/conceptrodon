<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Negation`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-negation">To Index</a></p>

## Description

`Pagelivore::Negation` accepts a predicate and returns a function.

When invoked, the function returns true if the predicate instantiated by the arguments evaluates to false and returns false if otherwise.

<pre><code>   Pred
-> Args...
-> not Pred&lt;Args...&gt;::value</code></pre>

## Type Signature

```Haskell
Negation
 :: template<auto...> class...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class>
struct Negation
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

We will turn `IsLess`, which checks if the first argument is less than the second, into `IsNoLess`, which checks if the first argument is no less than the second.

```C++
/**** IsLess ****/
template<auto First, auto Second>
struct IsLess
{
    static constexpr bool value
    {First < Second};
};

/**** IsNoLess ****/
template<auto...Args>
using IsNoLess = Negation<IsLess>::Page<Args...>;

/**** Tests ****/
static_assert(IsNoLess<1, 1>::value);
static_assert(IsNoLess<1, 0>::value);
static_assert(! IsNoLess<1, 2>::value);
```

## Implementation

```C++
template<template<auto...>  class Predicate>
struct Negation
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value 
        {not Predicate<Variables...>::value};
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/negation/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/pagelivore/negation.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/negation.test.hpp)
