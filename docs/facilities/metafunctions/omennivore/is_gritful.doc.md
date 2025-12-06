<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsGritful`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-is-gritful">To Index</a></p>

## Description

`Omennivore::IsGritful` accepts a type.
It returns true if the type is a packed `Grit` and returns false if otherwise.

<pre><code>   Type
-> Type == Grit&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsGritful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsGritful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsGritful_v {RESULT};
```

## Examples

```C++
/**** Vessel ****/
template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct GritLike;

/**** Items ****/
template<template<template<template<template<typename...> class...> class...> class...> class...>
struct CoolLike_0;

template<template<template<template<template<typename...> class...> class...> class...> class...>
struct CoolLike_1;

/**** Tests ****/
static_assert(IsGritful<GritLike<CoolLike_0, CoolLike_1>>::value);
static_assert(! IsGritful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsGritful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<typename...> class...> class...> class...> class...> class...Consistency
>
struct IsGritful<Sunshine<Consistency...>>
{ static constexpr bool value {true}; };
```

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/is_gritful/implementation.hpp)
- [Source code](../../../../conceptrodon/omennivore/is_gritful.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/is_gritful.test.hpp)
