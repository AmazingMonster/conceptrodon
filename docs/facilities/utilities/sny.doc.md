<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Sny`

<p style='text-align: right;'><a href="../utilities.md#sny">To Index</a></p>

## Description

`Sny` accepts a `Snow` operation and returns the operation via member `Snow`.

<pre><code>   Oper
-> struct { using Snow = Oper; }</code></pre>

## Type Signature

```Haskell
Sny
 :: template<template<template<template<typename...> class...> class...> class...> class...
 -> template<template<template<template<typename...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<typename...> class...> class...> class...> class>
struct Sny
{
    template<template<template<template<typename...> class...> class...> class...>
    alias Snow = RESULT;
};
```

## Examples

This function injectively maps a `Snow` to a type.
In the following example, We will create an overload set of `fun` using operations `Op_0` and `Op_1`.

```C++
/**** Operations ****/
template<template<template<template<typename...> class...> class...> class...>
struct Op_0 {};

template<template<template<template<typename...> class...> class...> class...>
struct Op_1 {};

/**** fun ****/
constexpr bool fun(Sny<Op_0>) { return false; }

constexpr bool fun(Sny<Op_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Sny<Op_0>{}));
static_assert(fun(Sny<Op_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
/**** gun ****/
constexpr auto gun(Sny<Op_0>) -> std::false_type;

constexpr auto gun(Sny<Op_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Sny<Op_0>>()))::value);
static_assert(decltype(gun(std::declval<Sny<Op_1>>()))::value);
```

## Implementation

```C++
template<template<template<template<template<typename...> class...> class...> class...> class Operation>
struct Sny
{
    template<template<template<template<typename...> class...> class...> class...Args>
    using Snow = Operation<Args...>;
};
```

## Links

- [Example](../../code/facilities/utilities/sny/implementation.hpp)
- [Source code](../../../conceptrodon/sny.hpp)
