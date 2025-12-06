<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsDawnful`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-is-dawnful">To Index</a></p>

## Description

`Omennivore::IsDawnful` accepts a type.
It returns true if the type is a packed `Dawn` and returns false if otherwise.

<pre><code>   Type
-> Type == Dawn&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsDawnful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsDawnful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsDawnful_v {RESULT};
```

## Examples

```C++
/**** Vessel ****/
template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
struct DawnLike;

/**** Items ****/
template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct WillLike_0;

template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct WillLike_1;

/**** Tests ****/
static_assert(IsDawnful<DawnLike<WillLike_0, WillLike_1>>::value);
static_assert(! IsDawnful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsDawnful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class Sunlight,
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Sunshines
>
struct IsDawnful<Sunlight<Sunshines...>>
{ static constexpr bool value {true}; };
```

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/is_dawnful/implementation.hpp)
- [Source code](../../../../conceptrodon/omennivore/is_dawnful.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/is_dawnful.test.hpp)
