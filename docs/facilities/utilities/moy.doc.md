<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Moy`

<p style='text-align: right;'><a href="../utilities.md#moy">To Index</a></p>

## Description

`Moy` accepts a `Mold` operation and returns the operation via member `Mold`.

<pre><code>   Oper
-> struct { using Mold = Oper; }</code></pre>

## Type Signature

```Haskell
Moy
 :: template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct Moy
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

This function injectively maps a container to a type.
In the following example, We will create an overload set of `fun` using containers `Con_0` and `Con_1`.

```C++
/**** Operations ****/
template<typename...>
struct Con_0 {};

template<typename...>
struct Con_1 {};

/**** fun ****/
constexpr bool fun(Moy<Con_0>) { return false; }

constexpr bool fun(Moy<Con_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Moy<Con_0>{}));
static_assert(fun(Moy<Con_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
/**** gun ****/
constexpr auto gun(Moy<Con_0>) -> std::false_type;

constexpr auto gun(Moy<Con_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Moy<Con_0>>()))::value);
static_assert(decltype(gun(std::declval<Moy<Con_1>>()))::value);
```

## Implementation

```C++
template<template<typename...> class Container>
struct Moy
{
    template<typename...Elements>
    using Mold = Container<Elements...>;
};
```

## Links

- [Example](../../code/facilities/utilities/moy/implementation.hpp)
- [Source code](../../../conceptrodon/utilities/moy.hpp)
- [Unit test](../../../tests/unit/utilities/moy.test.hpp)
