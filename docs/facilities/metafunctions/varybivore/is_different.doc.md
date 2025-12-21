<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::IsDifferent`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-is-different">To Index</a></p>

## Description

`Varybivore::IsDifferent` accepts a target and a list of variables.
It returns true if the target is different from every variable;
otherwise, it returns false.

<pre><code>   Target, V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (Target `different from` V<sub>0</sub>) && (Target `different from` V<sub>1</sub>) && ... && (Target `different from` V<sub>n</sub>)</code></pre>

## Type Signature

```Haskell
IsDifferent
 :: auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct IsDifferent
{
    static constexpr bool value
    {RESULT};
};

template<auto...>
constexpr bool IsDifferent_v
{RESULT};
```

## Examples

```C++
static_assert(IsDifferent<1, 2, 3, 4>::value);
static_assert(! IsDifferent<1, 1.0, 1>::value);
static_assert(IsDifferent<1, 1.0>::value);
```

## Implementation

We will implement `IsDifferent` using `Varybivore::SolitaryIsDifferent`.

Here's the entire implementation:

```C++
template<auto Target, auto...Variables>
struct IsDifferent
{
    static constexpr bool value
    {(...&&SolitaryIsDifferent<Variables, Target>::value)};
};

template<auto Target, auto...Variables>
constexpr bool IsDifferent_v
{(...&&SolitaryIsDifferent<Variables, Target>::value)};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/is_different/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/varybivore/is_different.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/is_different.test.hpp)
