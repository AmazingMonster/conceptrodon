<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Vay`

<p style='text-align: right;'><a href="../utilities.md#vay">To Index</a></p>

## Description

`Vay` accepts a variable and returns the variable via member `value`.

<pre><code>   V
-> struct { value = V; }</code></pre>

## Type Signature

```Haskell
Vay
 :: auto...
 -> auto
```

## Structure

```C++
template<auto>
struct Vay
{
    static constexpr auto value
    {RESULT};
};
```

## Examples

This function injectively maps a variable to a type.
In the following example, We will create an overload set of `fun` using values `0` and `1`.

```C++
/**** fun ****/
constexpr bool fun(Vay<0>) { return false; }

constexpr bool fun(Vay<1>) { return true; }

/**** Tests ****/
static_assert(not fun(Vay<0>{}));
static_assert(fun(Vay<1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
/**** gun ****/
constexpr auto gun(Vay<0>) -> std::false_type;

constexpr auto gun(Vay<1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Vay<0>>()))::value);
static_assert(decltype(gun(std::declval<Vay<1>>()))::value);
```

## Implementation

```C++
template<auto Variable>
struct Vay
{
    static constexpr auto value
    {Variable};
};
```

## Links

- [Example](../../code/facilities/utilities/vay/implementation.hpp)
- [Source code](../../../conceptrodon/utilities/vay.hpp)
- [Unit test](../../../tests/unit/utilities/vay.test.hpp)
