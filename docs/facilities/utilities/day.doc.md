<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Day`

<p style='text-align: right;'><a href="../utilities.md#day">To Index</a></p>

## Description

`Day` accepts a `Dawn` operation and returns the operation via member `Dawn`.

<pre><code>   Oper
-> struct { using Dawn = Oper; }</code></pre>

## Type Signature

```Haskell
Day
 :: template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class...
 -> template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class>
struct Day
{
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
    alias Dawn = RESULT;
};
```

## Examples

This function injectively maps a `Dawn` to a type.
In the following example, We will create an overload set of `fun` using operations `Op_0` and `Op_1`.

```C++
/**** Operations ****/
template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
struct Op_0 {};

template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
struct Op_1 {};

/**** fun ****/
constexpr bool fun(Day<Op_0>) { return false; }

constexpr bool fun(Day<Op_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Day<Op_0>{}));
static_assert(fun(Day<Op_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
/**** gun ****/
constexpr auto gun(Day<Op_0>) -> std::false_type;

constexpr auto gun(Day<Op_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Day<Op_0>>()))::value);
static_assert(decltype(gun(std::declval<Day<Op_1>>()))::value);
```

## Implementation

```C++
template<template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class Operation>
struct Day
{
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Args>
    using Dawn = Operation<Args...>;
};
```

## Links

- [Example](../../code/facilities/utilities/day/implementation.hpp)
- [Source code](../../../conceptrodon/utilities/day.hpp)
