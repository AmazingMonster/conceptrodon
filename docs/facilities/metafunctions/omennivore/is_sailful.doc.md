<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsSailful`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-is-sailful">To Index</a></p>

## Description

`Omennivore::IsSailful` accepts a type.
It returns true if the type is a packed `Sail` and returns false if otherwise.

<pre><code>   Type
-> Type == Sail&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsSailful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsSailful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsSailful_v {RESULT};
```

## Examples

```C++
/**** Vessel ****/
template<template<template<auto...> class...> class...>
struct SailLike;

/**** Items ****/
template<template<auto...> class...>
struct RailLike_0;

template<template<auto...> class...>
struct RailLike_1;

/**** Tests ****/
static_assert(IsSailful<SailLike<RailLike_0, RailLike_1>>::value);
static_assert(! IsSailful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsSailful
{ static constexpr bool value {false}; };

template
<
    template<template<template<auto...> class...> class...> class Melancholy,
    template<template<auto...> class...> class...Stockrooms
>
struct IsSailful<Melancholy<Stockrooms...>>
{ static constexpr bool value {true}; };
```

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/is_sailful/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/omennivore/is_sailful.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/is_sailful.test.hpp)
