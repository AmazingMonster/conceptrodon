<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Cay`

<p style='text-align: right;'><a href="../utilities.md#cay">To Index</a></p>

## Description

`Cay` accepts a `Calm` operation and returns the operation via member `Calm`.

<pre><code>   Oper
-> struct { using Calm = Oper; }</code></pre>

## Type Signature

```Haskell
Cay
 :: template<template<template<template<template<auto...> class...> class...> class...> class...> class...
 -> template<template<template<template<template<auto...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<auto...> class...> class...> class...> class...> class>
struct Cay
{
    template<template<template<template<template<auto...> class...> class...> class...> class...>
    alias Calm = RESULT;
};
```

## Examples

This function injectively maps a `Calm` to a type.
In the following example, We will create an overload set of `fun` using operations `Op_0` and `Op_1`.

```C++
/**** Operations ****/
template<template<template<template<template<auto...> class...> class...> class...> class...>
struct Op_0 {};

template<template<template<template<template<auto...> class...> class...> class...> class...>
struct Op_1 {};

/**** fun ****/
constexpr bool fun(Cay<Op_0>) { return false; }

constexpr bool fun(Cay<Op_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Cay<Op_0>{}));
static_assert(fun(Cay<Op_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
/**** gun ****/
constexpr auto gun(Cay<Op_0>) -> std::false_type;

constexpr auto gun(Cay<Op_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Cay<Op_0>>()))::value);
static_assert(decltype(gun(std::declval<Cay<Op_1>>()))::value);
```

## Implementation

```C++
template<template<template<template<template<template<auto...> class...> class...> class...> class...> class Operation>
struct Cay
{
    template<template<template<template<template<auto...> class...> class...> class...> class...Args>
    using Calm = Operation<Args...>;
};
```

## Links

- [Example](../../code/facilities/utilities/cay/implementation.hpp)
- [Source code](../../../conceptrodon/cay.hpp)
