<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Fly`

<p style='text-align: right;'><a href="../utilities.md#fly">To Index</a></p>

## Description

`Fly` accepts a `Flow` operation and returns the operation via member `Flow`.

<pre><code>   Oper
-> struct { using Flow = Oper; }</code></pre>

## Type Signature

```Haskell
Fly
 :: template<template<template<typename...> class...> class...> class...
 -> template<template<template<typename...> class...> class...>
```

## Structure

```C++
template<template<template<template<typename...> class...> class...> class>
struct Fly
{
    template<template<template<typename...> class...> class...>
    alias Flow = RESULT;
};
```

## Examples

This function injectively maps a `Flow` to a type.
In the following example, We will create an overload set of `fun` using operations `Op_0` and `Op_1`.

```C++
/**** Operations ****/
template<template<template<typename...> class...> class...>
struct Op_0 {};

template<template<template<typename...> class...> class...>
struct Op_1 {};

/**** fun ****/
constexpr bool fun(Fly<Op_0>) { return false; }

constexpr bool fun(Fly<Op_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Fly<Op_0>{}));
static_assert(fun(Fly<Op_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
/**** gun ****/
constexpr auto gun(Fly<Op_0>) -> std::false_type;

constexpr auto gun(Fly<Op_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Fly<Op_0>>()))::value);
static_assert(decltype(gun(std::declval<Fly<Op_1>>()))::value);
```

## Implementation

```C++
template<template<template<template<typename...> class...> class...> class Operation>
struct Fly
{
    template<template<template<typename...> class...> class...Args>
    using Flow = Operation<Args...>;
};
```

## Links

- [Example](../../code/facilities/utilities/fly/implementation.hpp)
- [Source code](../../../conceptrodon/utilities/fly.hpp)
- [Unit test](../../../tests/unit/utilities/fly.test.hpp)
