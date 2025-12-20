<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::IsUnequal`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-is-unequal">To Index</a></p>

## Description

`Varybivore::IsUnequal` accepts a target and a list of variables.
It returns true if all variables are unequal to the target.
Otherwise, it returns false.

<pre><code>   Target, V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (V<sub>0</sub> != Target) && (V<sub>1</sub> != Target) && ... && (V<sub>n</sub> != Target)</code></pre>

## Type Signature

```Haskell
IsUnequal
 :: auto...
 -> auto
```

## Structure

```C++
template<auto, auto...>
struct IsUnequal
{
    static constexpr bool value
    {RESULT};
};

template<auto, auto...>
static constexpr bool IsUnequal_v
{RESULT};
```

## Examples

```C++
static_assert(! IsUnequal<1, 1.0, 2, 3>::value);
static_assert(IsUnequal<1, 2, 2, 3>::value);
```

## Implementation

We will implement `IsUnequal` using only `<`, meaning <code>Variable != Target</code> is expressed as:

```C++
(Target < Variable) || (Variable < Target)
```

Here's the entire implementation:

```C++
template<auto Target, auto...Variables>
struct IsUnequal
{
    static constexpr auto value
    { (...&&(Target < Variables || Variables < Target)) };
};

template<auto Target, auto...Variables>
constexpr bool IsUnequal_v
{ (...&&(Target < Variables || Variables < Target)) };
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/is_unequal/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/is_unequal.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/is_unequal.test.hpp)
