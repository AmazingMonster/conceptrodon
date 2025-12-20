<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::IsEqual`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-is-equal-to">To Index</a></p>

## Description

`Varybivore::IsEqual` accepts a target and a list of variables.
It returns true if all variables are equal to the target.
Otherwise, it returns false.

<pre><code>   Target, V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (V<sub>0</sub> == Target) && (V<sub>1</sub> == Target) && ... && (V<sub>n</sub> == Target)</code></pre>

## Type Signature

```Haskell
IsEqual
 :: auto...
 -> auto
```

## Structure

```C++
template<auto, auto...>
struct IsEqual
{
    static constexpr bool value
    {RESULT};
};

template<auto, auto...>
static constexpr bool IsEqual_v
{RESULT};
```

## Examples

```C++
static_assert(IsEqual<1, 1.0, 1>::value);
static_assert(! IsEqual<1, 2, 2>::value);
```

## Implementation

We will implement `IsEqual` using only `<`, meaning <code>Variable == Target</code> is expressed as:

```C++
(not (Target < Variable)) && (not (Variable < Target))
```

Here's the entire implementation:

```C++
template<auto Target, auto...Variables>
struct IsEqual
{
    static constexpr bool value
    { (...&&(not (Target < Variables) && not (Variables < Target))) };
};

template<auto Target, auto...Variables>
constexpr bool IsEqual_v
{ (...&&(not (Target < Variables) && not (Variables < Target))) };
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/is_equal/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/is_equal.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/is_equal.test.hpp)
