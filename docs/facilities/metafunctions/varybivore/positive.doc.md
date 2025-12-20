<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Positive`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-positive">To Index</a></p>

## Description

`Varybivore::Positive` accepts a variable and applies unary `+` to it.

<pre><code>V -> +V</code></pre>

## Type Signature

```Haskell
Positive
 :: auto...
 -> auto
```

## Structure

```C++
template<auto>
struct Positive
{
    static constexpr bool value
    {RESULT};
};

template<auto>
static constexpr auto Positive_v
{RESULT};
```

## Examples

```C++
static_assert(Positive<1>::value == 1);
static_assert(Positive<-1.0>::value == -1.0);
```

## Implementation

```C++
template<auto I>
struct Positive
{ 
    static constexpr auto value 
    {+I}; 
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/positive/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/positive.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/positive.test.hpp)
