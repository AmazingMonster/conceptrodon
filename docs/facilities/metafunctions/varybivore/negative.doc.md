<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Negative`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-negative">To Index</a></p>

## Description

`Varybivore::Negative` accepts a variable and applies unary `-` to it.

<pre><code>V -> -V</code></pre>

## Type Signature

```Haskell
Negative
 :: auto...
 -> auto
```

## Structure

```C++
template<auto>
struct Negative
{
    static constexpr bool value
    {RESULT};
};

template<auto>
static constexpr auto Negative_v
{RESULT};
```

## Examples

```C++
static_assert(Negative<1>::value == -1);
static_assert(Negative<-1.0>::value == 1.0);
```

## Implementation

```C++
template<auto I>
struct Negative
{ 
    static constexpr auto value 
    {-I}; 
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/negative/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/negative.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/negative.test.hpp)
