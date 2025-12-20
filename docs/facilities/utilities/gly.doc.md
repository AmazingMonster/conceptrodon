<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Gly`

<p style='text-align: right;'><a href="../utilities.md#gly">To Index</a></p>

## Description

`Gly` accepts a `Glow` operation and returns the operation via member `Glow`.

<pre><code>   Oper
-> struct { using Glow = Oper; }</code></pre>

## Type Signature

```Haskell
Gly
 :: template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class...
 -> template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class>
struct Gly
{
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
    alias Glow = RESULT;
};
```

## Examples

This function injectively maps a `Glow` to a type.
In the following example, We will create an overload set of `fun` using operations `Op_0` and `Op_1`.

```C++
/**** Operations ****/
template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct Op_0 {};

template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct Op_1 {};

/**** fun ****/
constexpr bool fun(Gly<Op_0>) { return false; }

constexpr bool fun(Gly<Op_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Gly<Op_0>{}));
static_assert(fun(Gly<Op_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
/**** gun ****/
constexpr auto gun(Gly<Op_0>) -> std::false_type;

constexpr auto gun(Gly<Op_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Gly<Op_0>>()))::value);
static_assert(decltype(gun(std::declval<Gly<Op_1>>()))::value);
```

## Implementation

```C++
template<template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class Operation>
struct Gly
{
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Args>
    using Glow = Operation<Args...>;
};
```

## Links

- [Example](../../code/facilities/utilities/gly/implementation.hpp)
- [Source code](../../../conceptrodon/gly.hpp)
