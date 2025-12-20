<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pay`

<p style='text-align: right;'><a href="../utilities.md#pay">To Index</a></p>

## Description

`Pay` accepts a `Page` operation and returns the operation via member `Page`.

<pre><code>   Oper
-> struct { using Page = Oper; }</code></pre>

## Type Signature

```Haskell
Pay
 :: template<auto...> class...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct Pay
{
    template<auto...>
    alias Page = RESULT;
};
```

## Examples

This function injectively maps a sequence to a type.
In the following example, We will create an overload set of `fun` using sequences `Seq_0` and `Seq_1`.

```C++
/**** Operations ****/
template<auto...>
struct Seq_0 {};

template<auto...>
struct Seq_1 {};

/**** fun ****/
constexpr bool fun(Pay<Seq_0>) { return false; }

constexpr bool fun(Pay<Seq_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Pay<Seq_0>{}));
static_assert(fun(Pay<Seq_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
/**** gun ****/
constexpr auto gun(Pay<Seq_0>) -> std::false_type;

constexpr auto gun(Pay<Seq_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Pay<Seq_0>>()))::value);
static_assert(decltype(gun(std::declval<Pay<Seq_1>>()))::value);
```

## Implementation

```C++
template<template<auto...> class Sequence>
struct Pay
{
    template<auto...Variables>
    using Page = Sequence<Variables...>;
};
```

## Links

- [Example](../../code/facilities/utilities/pay/implementation.hpp)
- [Source code](../../../conceptrodon/pay.hpp)
