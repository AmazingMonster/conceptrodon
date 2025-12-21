<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsGlowful`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-is-glowful">To Index</a></p>

## Description

`Omennivore::IsGlowful` accepts a type.
It returns true if the type is a packed `Glow` and returns false if otherwise.

<pre><code>   Type
-> Type == Glow&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsGlowful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsGlowful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsGlowful_v {RESULT};
```

## Examples

```C++
/**** Vessel ****/
template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct GlowLike;

/**** Items ****/
template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct GritLike_0;

template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct GritLike_1;

/**** Tests ****/
static_assert(IsGlowful<GlowLike<GritLike_0, GritLike_1>>::value);
static_assert(! IsGlowful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsGlowful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class Sunlight,
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Sunshines
>
struct IsGlowful<Sunlight<Sunshines...>>
{ static constexpr bool value {true}; };
```

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/is_glowful/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/omennivore/is_glowful.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/is_glowful.test.hpp)
