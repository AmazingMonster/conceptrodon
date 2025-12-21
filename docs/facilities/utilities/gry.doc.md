<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Gry`

<p style='text-align: right;'><a href="../utilities.md#gry">To Index</a></p>

## Description

`Gry` accepts a `Grit` operation and returns the operation via member `Grit`.

<pre><code>   Oper
-> struct { using Flow = Oper; }</code></pre>

## Type Signature

```Haskell
Gry
 :: template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class>
struct Gry
{
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
    alias Grit = RESULT;
};
```

## Examples

This function injectively maps a `Grit` to a type.
In the following example, We will create an overload set of `fun` using operations `Op_0` and `Op_1`.

```C++
/**** Operations ****/
template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct Op_0 {};

template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct Op_1 {};

/**** fun ****/
constexpr bool fun(Gry<Op_0>) { return false; }

constexpr bool fun(Gry<Op_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Gry<Op_0>{}));
static_assert(fun(Gry<Op_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
/**** gun ****/
constexpr auto gun(Gry<Op_0>) -> std::false_type;

constexpr auto gun(Gry<Op_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Gry<Op_0>>()))::value);
static_assert(decltype(gun(std::declval<Gry<Op_1>>()))::value);
```

## Implementation

```C++
template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class Operation>
struct Gry
{
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Args>
    using Grit = Operation<Args...>;
};
```

## Links

- [Example](../../code/facilities/utilities/gry/implementation.hpp)
- [Source code](../../../conceptrodon/utilities/gry.hpp)
