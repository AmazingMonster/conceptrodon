<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::IsLess`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-is-less">To Index</a></p>

## Description

`Varybivore::IsLess` accepts a target and a list of variables.
It returns true if the target is less than all the variables;
otherwise, it returns false.

<pre><code>   Target, V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (Target &lt; V<sub>0</sub>) && (Target &lt; V<sub>1</sub>) && ... && (Target &lt; V<sub>n</sub>)</code></pre>

## Type Signature

```Haskell
IsLess
 :: auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct IsLess
{
    static constexpr bool value
    {RESULT};
};

template<auto...>
constexpr bool IsLess_v
{RESULT};
```

## Examples

```C++
static_assert(IsLess<0, 2, 3, 4>::value);
static_assert(! IsLess<0, -1, 2, 3>::value);
```

## Implementation

Here's the entire implementation:

```C++
template<auto Target, auto...Variables>
struct IsLess
{
    static constexpr bool value
    { (...&&(Target < Variables)) };
};

template<auto Target, auto...Variables>
constexpr bool IsLess_v
{ (...&&(Target < Variables)) };
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/is_less/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/varybivore/is_less.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/is_less.test.hpp)
