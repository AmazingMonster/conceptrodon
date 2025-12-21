<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsCalmful`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-is-calmful">To Index</a></p>

## Description

`Omennivore::IsCalmful` accepts a type.
It returns true if the type is a packed `Calm` and returns false if otherwise.

<pre><code>   Type
-> Type == Calm&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsCalmful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsCalmful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsCalmful_v {RESULT};
```

## Examples

```C++
/**** Vessel ****/
template<template<template<template<template<auto...> class...> class...> class...> class...>
struct CalmLike;

/**** Items ****/
template<template<template<template<auto...> class...> class...> class...>
struct HailLike_0;

template<template<template<template<auto...> class...> class...> class...>
struct HailLike_1;

/**** Tests ****/
static_assert(IsCalmful<CalmLike<HailLike_0, HailLike_1>>::value);
static_assert(! IsCalmful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsCalmful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<template<auto...> class...> class...> class...> class...> class Perseverance,
    template<template<template<template<auto...> class...> class...> class...> class...Tranquil
>
struct IsCalmful<Perseverance<Tranquil...>>
{ static constexpr bool value {true}; };
```

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/is_calmful/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/omennivore/is_calmful.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/is_calmful.test.hpp)
