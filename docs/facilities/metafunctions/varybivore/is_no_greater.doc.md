<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::IsNoGreater`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-is-no-greater">To Index</a></p>

## Description

`Varybivore::IsNoGreater` accepts a target and a list of variables.
It returns true if the target is less or equal to all the variables;
otherwise, it returns false.

<pre><code>   Target, V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (Target &le; V<sub>0</sub>) && (Target &le; V<sub>1</sub>) && ... && (Target &le; V<sub>n</sub>)</code></pre>

## Type Signature

```Haskell
IsNoGreater
 :: auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct IsNoGreater
{
    static constexpr bool value
    {RESULT};
};

template<auto...>
constexpr bool IsNoGreater_v
{RESULT};
```

## Examples

```C++
static_assert(IsNoGreater<5, 5, 6, 7>::value);
static_assert(! IsNoGreater<4, 2, 3, 4>::value);
```

## Implementation

We will implement `IsNoGreater` using only `<`, meaning <code>Target &le; Variable</code> is expressed as:

```C++
not (Variable < Target)
```

Here's the entire implementation:

```C++
template<auto Target, auto...Variables>
struct IsNoGreater
{
    static constexpr bool value
    { (...&&(not (Variables < Target))) };
};

template<auto Target, auto...Variables>
constexpr bool IsNoGreater_v
{ (...&&(not (Variables < Target))) };
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/is_no_greater/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/is_no_greater.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/is_no_greater.test.hpp)
