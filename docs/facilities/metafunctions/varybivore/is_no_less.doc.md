<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::IsNoLess`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-is-no-less">To Index</a></p>

## Description

`Varybivore::IsNoLess` accepts a target and a list of variables.
It returns true if the target is greater or equal to all the variables;
otherwise, it returns false.

<pre><code>   Target, V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (Target &ge; V<sub>0</sub>) && (Target &ge; V<sub>1</sub>) && ... && (Target &ge; V<sub>n</sub>)</code></pre>

## Type Signature

```Haskell
IsNoLess
 :: auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct IsNoLess
{
    static constexpr bool value
    {RESULT};
};
    
template<auto...>
constexpr bool IsNoLess_v
{RESULT};
```

## Examples

```C++
static_assert(IsNoLess<5, 4, 3, 2>::value);
static_assert(! IsNoLess<4, 5, 3, 4>::value);
```

## Implementation

We will implement `IsNoLess` using only `<`, meaning <code>Target &ge; Variable</code> is expressed as:

```C++
not (Target < Variable)
```

Here's the entire implementation:

```C++
template<auto Target, auto...Variables>
struct IsNoLess
{
    static constexpr bool value
    { (...&&(not (Target < Variables))) };
};

template<auto Target, auto...Variables>
constexpr bool IsNoLess_v
{ (...&&(not (Target < Variables))) };
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/is_no_less/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/is_no_less.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/is_no_less.test.hpp)
