<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roy`

<p style='text-align: right;'><a href="../utilities.md#roy">To Index</a></p>

## Description

`Roy` accepts a `Road` operation and returns the operation via member `Road`.

<pre><code>   Oper
-> struct { using Road = Oper; }</code></pre>

## Type Signature

```Haskell
Roy
 :: template<template<typename...> class...> class...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<template<template<typename...> class...> class>
struct Roy
{
    template<template<typename...> class...>
    alias Road = RESULT;
};
```

## Examples

This function injectively maps a warehouse to a type.
In the following example, We will create an overload set of `fun` using warehouses `Ware_0` and `Ware_1`.

```C++
/**** Operations ****/
template<template<typename...> class...>
struct Ware_0 {};

template<template<typename...> class...>
struct Ware_1 {};

/**** fun ****/
constexpr bool fun(Roy<Ware_0>) { return false; }

constexpr bool fun(Roy<Ware_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Roy<Ware_0>{}));
static_assert(fun(Roy<Ware_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
/**** gun ****/
constexpr auto gun(Roy<Ware_0>) -> std::false_type;

constexpr auto gun(Roy<Ware_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Roy<Ware_0>>()))::value);
static_assert(decltype(gun(std::declval<Roy<Ware_1>>()))::value);
```

## Implementation

```C++
template<template<template<typename...> class...> class Warehouse>
struct Roy
{
    template<template<typename...> class...Containers>
    using Road = Warehouse<Containers...>;
};
```

## Links

- [Example](../../code/facilities/utilities/roy/implementation.hpp)
- [Source code](../../../conceptrodon/utilities/roy.hpp)
- [Unit test](../../../tests/unit/utilities/roy.test.hpp)
