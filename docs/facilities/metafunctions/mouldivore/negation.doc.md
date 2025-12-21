<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Negation`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-negation">To Index</a></p>

## Description

`Mouldivore::Negation` accepts a predicate and returns a function.

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

We will turn `IsLess`, which checks if the first argument is less than the second, into `IsNoLess`, which checks if the first argument is no less than the second.

```C++
/**** IsLess ****/
template<typename First, typename Second>
struct IsLess
{
    static constexpr bool value
    {First::value < Second::value};
};

/**** IsNoLess ****/
template<typename...Args>
using IsNoLess = Negation<IsLess>::Mold<Args...>;

/**** Tests ****/
static_assert(IsNoLess<std::integral_constant<int, 1>, std::integral_constant<int, 1>>::value);
static_assert(IsNoLess<std::integral_constant<int, 1>, std::integral_constant<int, 0>>::value);
static_assert(! IsNoLess<std::integral_constant<int, 1>, std::integral_constant<int, 2>>::value);
```

## Implementation

```C++
template<template<typename...>  class Predicate>
struct Negation
{
    template<typename...Elements>
    struct ProtoMold
    {
        static constexpr bool value 
        {not Predicate<Elements...>::value};
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/negation/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/mouldivore/negation.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/negation.test.hpp)
