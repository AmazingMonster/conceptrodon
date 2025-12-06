<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsRailful`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-is-railful">To Index</a></p>

## Description

`Omennivore::IsRailful` accepts a type.
It returns true if the type is a packed `Rail` and returns false if otherwise.

<pre><code>   Type
-> Type == Rail&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsRailful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsRailful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsRailful_v {RESULT};
```

## Examples

```C++
/**** Vessel ****/
template<template<auto...> class...>
struct RailLike;

/**** Items ****/
template<auto...>
struct PageLike_0;

template<auto...>
struct PageLike_1;

/**** Tests ****/
static_assert(IsRailful<RailLike<PageLike_0, PageLike_1>>::value);
static_assert(! IsRailful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsRailful
{ static constexpr bool value {false}; };

template
<
    template<template<auto...> class...> class Stockroom,
    template<auto...> class...Sequences
>
struct IsRailful<Stockroom<Sequences...>>
{ static constexpr bool value {true}; };
```

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/is_railful/implementation.hpp)
- [Source code](../../../../conceptrodon/omennivore/is_railful.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/is_railful.test.hpp)
