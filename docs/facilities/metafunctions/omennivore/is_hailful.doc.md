<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsHailful`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-is-hailful">To Index</a></p>

## Description

`Omennivore::IsHailful` accepts a type.
It returns true if the type is a packed `Hail` and returns false if otherwise.

<pre><code>   Type
-> Type == Hail&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsHailful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsHailful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsHailful_v {RESULT};
```

## Examples

```C++
/**** Vessel ****/
template<template<template<template<auto...> class...> class...> class...>
struct HailLike;

/**** Items ****/
template<template<template<auto...> class...> class...>
struct SailLike_0;

template<template<template<auto...> class...> class...>
struct SailLike_1;

/**** Tests ****/
static_assert(IsHailful<HailLike<SailLike_0, SailLike_1>>::value);
static_assert(! IsHailful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsHailful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<auto...> class...> class...> class...> class Tranquil,
    template<template<template<auto...> class...> class...> class...Melancholy
>
struct IsHailful<Tranquil<Melancholy...>>
{ static constexpr bool value {true}; };
```

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/is_hailful/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/omennivore/is_hailful.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/is_hailful.test.hpp)
