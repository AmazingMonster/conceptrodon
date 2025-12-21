<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Wiy`

<p style='text-align: right;'><a href="../utilities.md#wiy">To Index</a></p>

## Description

`Wiy` accepts a `Will` operation and returns the operation via member `Will`.

<pre><code>   Oper
-> struct { using Will = Oper; }</code></pre>

## Type Signature

```Haskell
Wiy
 :: template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class>
struct Wiy
{
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
    alias Will = RESULT;
};
```

## Examples

This function injectively maps a `Will` to a type.
In the following example, We will create an overload set of `fun` using operations `Op_0` and `Op_1`.

```C++
/**** Operations ****/
template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct Op_0 {};

template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct Op_1 {};

/**** fun ****/
constexpr bool fun(Wiy<Op_0>) { return false; }

constexpr bool fun(Wiy<Op_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Wiy<Op_0>{}));
static_assert(fun(Wiy<Op_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
/**** gun ****/
constexpr auto gun(Wiy<Op_0>) -> std::false_type;

constexpr auto gun(Wiy<Op_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Wiy<Op_0>>()))::value);
static_assert(decltype(gun(std::declval<Wiy<Op_1>>()))::value);
```

## Implementation

```C++
template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class Operation>
struct Wiy
{
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Args>
    using Will = Operation<Args...>;
};
```

## Links

- [Example](../../code/facilities/utilities/wiy/implementation.hpp)
- [Source code](../../../conceptrodon/utilities/wiy.hpp)
