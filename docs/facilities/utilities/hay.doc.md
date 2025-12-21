<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Hay`

<p style='text-align: right;'><a href="../utilities.md#hay">To Index</a></p>

## Description

`Hay` accepts a `Hail` operation and returns the operation via member `Hail`.

<pre><code>   Oper
-> struct { using Flow = Oper; }</code></pre>

## Type Signature

```Haskell
Hay
 :: template<template<template<template<auto...> class...> class...> class...> class...
 -> template<template<template<template<auto...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<auto...> class...> class...> class...> class>
struct Hay
{
    template<template<template<template<auto...> class...> class...> class...>
    alias Hail = RESULT;
};
```

## Examples

This function injectively maps a `Hail` to a type.
In the following example, We will create an overload set of `fun` using operations `Op_0` and `Op_1`.

```C++
/**** Operations ****/
template<template<template<template<auto...> class...> class...> class...>
struct Op_0 {};

template<template<template<template<auto...> class...> class...> class...>
struct Op_1 {};

/**** fun ****/
constexpr bool fun(Hay<Op_0>) { return false; }

constexpr bool fun(Hay<Op_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Hay<Op_0>{}));
static_assert(fun(Hay<Op_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
/**** gun ****/
constexpr auto gun(Hay<Op_0>) -> std::false_type;

constexpr auto gun(Hay<Op_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Hay<Op_0>>()))::value);
static_assert(decltype(gun(std::declval<Hay<Op_1>>()))::value);
```

## Implementation

```C++
template<template<template<template<template<auto...> class...> class...> class...> class Operation>
struct Hay
{
    template<template<template<template<auto...> class...> class...> class...Args>
    using Hail = Operation<Args...>;
};
```

## Links

- [Example](../../code/facilities/utilities/hay/implementation.hpp)
- [Source code](../../../conceptrodon/utilities/hay.hpp)
