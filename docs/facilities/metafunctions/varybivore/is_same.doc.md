<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::IsSame`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-is-same">To Index</a></p>

## Description

`Varybivore::IsSame` accepts a target and a list of variables.
It returns true if the target is the same as every variable;
otherwise, it returns false.

<pre><code>   Target, V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (Target `same as` V<sub>0</sub>) && (Target `same as` V<sub>1</sub>) && ... && (Target `same as` V<sub>n</sub>)</code></pre>

## Type Signature

```Haskell
IsSame
 :: auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct IsSame
{
    static constexpr bool value
    {RESULT};
};

template<auto...>
constexpr bool IsSame_v
{RESULT};
```

## Examples

```C++
static_assert(IsSame<1, 1, 1, 1>::value);
static_assert(! IsSame<1, 1.0, 1>::value);
```

## Implementation

We will implement `IsSame` using `Varybivore::SolitaryIsSame`.

Here's the entire implementation:

```C++
template<auto Target, auto...Variables>
struct IsSame
{
    static constexpr bool value
    {(...&&SolitaryIsSame<Variables, Target>::value)};
};

template<auto Target, auto...Variables>
constexpr bool IsSame_v
{(...&&SolitaryIsSame<Variables, Target>::value)};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/is_same/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/varybivore/is_same.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/is_same.test.hpp)
