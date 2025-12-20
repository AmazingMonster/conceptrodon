<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::IsGreater`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-is-greater">To Index</a></p>

## Description

`Varybivore::IsGreater` accepts a target and a list of variables.
It returns true if the target is greater than all the variables;
otherwise, it returns false.

<pre><code>   Target, V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (Target &gt; V<sub>0</sub>) && (Target &gt; V<sub>1</sub>) && ... && (Target &gt; V<sub>n</sub>)</code></pre>

## Type Signature

```Haskell
IsGreater
 :: auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct IsGreater
{
    static constexpr bool value
    {RESULT};
};

template<auto...>
constexpr bool IsGreater_v
{RESULT};
```

## Examples

```C++
static_assert(IsGreater<5, 2, 3, 4>::value);
static_assert(! IsGreater<4, 2, 3, 4>::value);
```

## Implementation

We will implement `IsGreater` using only `<`, meaning <code>Target > Variable</code> is expressed as:

```C++
Variable < Target
```

Here's the entire implementation:

```C++
template<auto Target, auto...Variables>
struct IsGreater
{
    static constexpr bool value
    { (...&&(Variables < Target)) };
};

template<auto Target, auto...Variables>
constexpr bool IsGreater_v
{ (...&&(Variables < Target)) };
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/is_greater/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/is_greater.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/is_greater.test.hpp)
