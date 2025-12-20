<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Coy`

<p style='text-align: right;'><a href="../utilities.md#coy">To Index</a></p>

## Description

`Coy` accepts a `Cool` operation and returns the operation via member `Cool`.

<pre><code>   Oper
-> struct { using Cool = Oper; }</code></pre>

## Type Signature

```Haskell
Coy
 :: template<template<template<template<template<typename...> class...> class...> class...> class...> class...
 -> template<template<template<template<template<typename...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<typename...> class...> class...> class...> class...> class>
struct Coy
{
    template<template<template<template<template<typename...> class...> class...> class...> class...>
    alias Cool = RESULT;
};
```

## Examples

This function injectively maps a `Cool` to a type.
In the following example, We will create an overload set of `fun` using operations `Op_0` and `Op_1`.

```C++
/**** Operations ****/
template<template<template<template<template<typename...> class...> class...> class...> class...>
struct Op_0 {};

template<template<template<template<template<typename...> class...> class...> class...> class...>
struct Op_1 {};

/**** fun ****/
constexpr bool fun(Coy<Op_0>) { return false; }

constexpr bool fun(Coy<Op_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Coy<Op_0>{}));
static_assert(fun(Coy<Op_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
/**** gun ****/
constexpr auto gun(Coy<Op_0>) -> std::false_type;

constexpr auto gun(Coy<Op_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Coy<Op_0>>()))::value);
static_assert(decltype(gun(std::declval<Coy<Op_1>>()))::value);
```

## Implementation

```C++
template<template<template<template<template<template<typename...> class...> class...> class...> class...> class Operation>
struct Coy
{
    template<template<template<template<template<typename...> class...> class...> class...> class...Args>
    using Cool = Operation<Args...>;
};
```

## Links

- [Example](../../code/facilities/utilities/coy/implementation.hpp)
- [Source code](../../../conceptrodon/coy.hpp)
