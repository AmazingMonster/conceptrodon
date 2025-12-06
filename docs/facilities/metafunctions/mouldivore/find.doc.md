<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Find`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-find">To Index</a></p>

## Description

`Mouldivore::Find` accepts a list of predicates and returns a function.

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
 :: template<typename...> class...
 -> typename...
 -> auto
```

## Structure

```C++
template<template<typename...> class...>
struct Find
{
    template<typename...>
    alias Mold
    {
        static constexpr std::make_signed_t<size_t> value
        {RESULT};
    };

    template<typename...>
    static constexpr std::make_signed_t<size_t> Mold_v
    {RESULT};
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
using Metafunction = Find<IsIntDoubleStar>
::Mold<Args...>;

/**** Tests ****/
static_assert(Metafunction<int, int*, int**, int***>::value == 2);
static_assert(Metafunction<int, int*, int***>::value == -1);
```

## Implementation

`Mouldivore::Find` is implemented based on `Typelivore::KindredFind`. It changes the invocation order of the latter.

```C++
template<template<typename...> class Predicate>
struct Find
{
    template<typename...Elements>
    using Mold = Typelivore::KindredFind<Elements...>
    ::template Road<Predicate>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/find/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/find.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/find.test.hpp)
