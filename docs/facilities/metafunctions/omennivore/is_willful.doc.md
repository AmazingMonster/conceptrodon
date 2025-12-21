<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsWillful`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-is-willful">To Index</a></p>

## Description

`Omennivore::IsWillful` accepts a type.
It returns true if the type is a packed `Will` and returns false if otherwise.

<pre><code>   Type
-> Type == Will&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsWillful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsWillful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsWillful_v {RESULT};
```

## Examples

```C++
/**** Vessel ****/
template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct WillLike;

/**** Items ****/
template<template<template<template<template<auto...> class...> class...> class...> class...>
struct CalmLike_0;

template<template<template<template<template<auto...> class...> class...> class...> class...>
struct CalmLike_1;

/**** Tests ****/
static_assert(IsWillful<WillLike<CalmLike_0, CalmLike_1>>::value);
static_assert(! IsWillful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsWillful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<auto...> class...> class...> class...> class...> class...Perseverance
>
struct IsWillful<Sunshine<Perseverance...>>
{ static constexpr bool value {true}; };
```

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/is_willful/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/omennivore/is_willful.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/is_willful.test.hpp)
