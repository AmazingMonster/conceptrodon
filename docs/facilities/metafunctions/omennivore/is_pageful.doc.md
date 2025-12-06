<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsPageful`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-is-pageful">To Index</a></p>

## Description

`Omennivore::IsPageful` accepts a type.
It returns true if the type is a packed `Page` and returns false if otherwise.

<pre><code>   Type
-> Type == Page&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsPageful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsPageful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsPageful_v {RESULT};
```

## Examples

```C++
/**** Vessel ****/
template<auto...>
struct PageLike;

/**** Tests ****/
static_assert(IsPageful<PageLike<0, 1>>::value);
static_assert(! IsPageful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsPageful
{ static constexpr bool value {false}; };

template<template<auto...> class Sequence, auto...Variables>
struct IsPageful<Sequence<Variables...>>
{ static constexpr bool value {true}; };
```

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/is_pageful/implementation.hpp)
- [Source code](../../../../conceptrodon/omennivore/is_pageful.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/is_pageful.test.hpp)
