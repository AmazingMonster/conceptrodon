<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsMoldful`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-is-moldful">To Index</a></p>

## Description

`Omennivore::IsMoldful` accepts a type.
It returns true if the type is a packed `Mold` and returns false if otherwise.

<pre><code>   Type
-> Type == Mold&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsMoldful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsMoldful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsMoldful_v {RESULT};
```

## Examples

```C++
/**** Vessel ****/
template<typename...>
struct MoldLike;

/**** Tests ****/
static_assert(IsMoldful<MoldLike<int, int*>>::value);
static_assert(! IsMoldful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsMoldful
{ static constexpr bool value {false}; };

template<template<typename...> class Container, typename...Elements>
struct IsMoldful<Container<Elements...>>
{ static constexpr bool value {true}; };
```

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/is_moldful/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/omennivore/is_moldful.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/is_moldful.test.hpp)
