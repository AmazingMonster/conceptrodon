<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsCoolful`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-is-coolful">To Index</a></p>

## Description

`Omennivore::IsCoolful` accepts a type.
It returns true if the type is a packed `Cool` and returns false if otherwise.

<pre><code>   Type
-> Type == Cool&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsCoolful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsCoolful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsCoolful_v {RESULT};
```

## Examples

```C++
/**** Vessel ****/
template<template<template<template<template<typename...> class...> class...> class...> class...>
struct CoolLike;

/**** Items ****/
template<template<template<template<typename...> class...> class...> class...>
struct SnowLike_0;

template<template<template<template<typename...> class...> class...> class...>
struct SnowLike_1;

/**** Tests ****/
static_assert(IsCoolful<CoolLike<SnowLike_0, SnowLike_1>>::value);
static_assert(! IsCoolful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsCoolful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<template<typename...> class...> class...> class...> class...> class Consistency,
    template<template<template<template<typename...> class...> class...> class...> class...Silence
>
struct IsCoolful<Consistency<Silence...>>
{ static constexpr bool value {true}; };
```

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/is_coolful/implementation.hpp)
- [Source code](../../../../conceptrodon/omennivore/is_coolful.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/is_coolful.test.hpp)
