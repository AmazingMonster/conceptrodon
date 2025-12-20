<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Ray`

<p style='text-align: right;'><a href="../utilities.md#ray">To Index</a></p>

## Description

`Ray` accepts a `Rail` operation and returns the operation via member `Rail`.

<pre><code>   Oper
-> struct { using Rail = Oper; }</code></pre>

## Type Signature

```Haskell
Ray
 :: template<template<auto...> class...> class...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<template<template<auto...> class...> class>
struct Ray
{
    template<template<auto...> class...>
    alias Rail = RESULT;
};
```

## Examples

This function injectively maps a stockroom to a type.
In the following example, We will create an overload set of `fun` using stockrooms `Stoc_0` and `Stoc_1`.

```C++
/**** Operations ****/
template<template<auto...> class...>
struct Stoc_0 {};

template<template<auto...> class...>
struct Stoc_1 {};

/**** fun ****/
constexpr bool fun(Ray<Stoc_0>) { return false; }

constexpr bool fun(Ray<Stoc_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Ray<Stoc_0>{}));
static_assert(fun(Ray<Stoc_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
/**** gun ****/
constexpr auto gun(Ray<Stoc_0>) -> std::false_type;

constexpr auto gun(Ray<Stoc_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Ray<Stoc_0>>()))::value);
static_assert(decltype(gun(std::declval<Ray<Stoc_1>>()))::value);
```

## Implementation

```C++
template<template<template<auto...> class...> class Stockroom>
struct Ray
{
    template<template<auto...> class...Sequences>
    using Rail = Stockroom<Sequences...>;
};
```

## Links

- [Example](../../code/facilities/utilities/ray/implementation.hpp)
- [Source code](../../../conceptrodon/ray.hpp)
