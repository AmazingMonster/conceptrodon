<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Say`

<p style='text-align: right;'><a href="../utilities.md#say">To Index</a></p>

## Description

`Say` accepts a `Sail` operation and returns the operation via member `Sail`.

<pre><code>   Oper
-> struct { using Sail = Oper; }</code></pre>

## Type Signature

```Haskell
Say
 :: template<template<template<auto...> class...> class...> class...
 -> template<template<template<auto...> class...> class...>
```

## Structure

```C++
template<template<template<template<auto...> class...> class...> class>
struct Say
{
    template<template<template<auto...> class...> class...>
    alias Sail = RESULT;
};
```

## Examples

This function injectively maps a `Sail` to a type.
In the following example, We will create an overload set of `fun` using operations `Op_0` and `Op_1`.

```C++
/**** Operations ****/
template<template<template<auto...> class...> class...>
struct Op_0 {};

template<template<template<auto...> class...> class...>
struct Op_1 {};

/**** fun ****/
constexpr bool fun(Say<Op_0>) { return false; }

constexpr bool fun(Say<Op_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Say<Op_0>{}));
static_assert(fun(Say<Op_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
/**** gun ****/
constexpr auto gun(Say<Op_0>) -> std::false_type;

constexpr auto gun(Say<Op_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Say<Op_0>>()))::value);
static_assert(decltype(gun(std::declval<Say<Op_1>>()))::value);
```

## Implementation

```C++
template<template<template<template<auto...> class...> class...> class Operation>
struct Say
{
    template<template<template<auto...> class...> class...Args>
    using Sail = Operation<Args...>;
};
```

## Links

- [Example](../../code/facilities/utilities/say/implementation.hpp)
- [Source code](../../../conceptrodon/say.hpp)
