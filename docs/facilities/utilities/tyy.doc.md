<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Tyy`

<p style='text-align: right;'><a href="../utilities.md#tyy">To Index</a></p>

## Description

`Tyy` accepts an element and returns the element via member `type`.

<pre><code>   T
-> struct { type = T; }</code></pre>

## Type Signature

```Haskell
Tyy
 :: typename...
 -> typename
```

## Structure

```C++
template<typename>
struct Tyy
{
    using type = RESULT;
};
```

## Examples

This function injectively maps a type to a type.
In the following example, We will create an overload set of `fun` using types `int` and `int*`.

```C++
/**** fun ****/
constexpr bool fun(Tyy<int>) { return false; }

constexpr bool fun(Tyy<int*>) { return true; }

/**** Tests ****/
static_assert(not fun(Tyy<int>{}));
static_assert(fun(Tyy<int*>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
/**** gun ****/
constexpr auto gun(Tyy<int>) -> std::false_type;

constexpr auto gun(Tyy<int*>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Tyy<int>>()))::value);
static_assert(decltype(gun(std::declval<Tyy<int*>>()))::value);
```

## Implementation

```C++
template<typename Element>
struct Tyy
{
    using type = Element;
};
```

## Links

- [Example](../../code/facilities/utilities/tyy/implementation.hpp)
- [Source code](../../../conceptrodon/utilities/tyy.hpp)
- [Unit test](../../../tests/unit/utilities/tyy.test.hpp)
