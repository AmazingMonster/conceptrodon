<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsSnowful`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-is-snowful">To Index</a></p>

## Description

`Omennivore::IsSnowful` accepts a type.
It returns true if the type is a packed `Snow` and returns false if otherwise.

<pre><code>   Type
-> Type == Snow&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsSnowful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsSnowful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsSnowful_v {RESULT};
```

## Examples

```C++
/**** Vessel ****/
template<template<template<template<typename...> class...> class...> class...>
struct SnowLike;

/**** Items ****/
template<template<template<typename...> class...> class...>
struct FlowLike_0;

template<template<template<typename...> class...> class...>
struct FlowLike_1;

/**** Tests ****/
static_assert(IsSnowful<SnowLike<FlowLike_0, FlowLike_1>>::value);
static_assert(! IsSnowful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsSnowful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<typename...> class...> class...> class...> class Silence,
    template<template<template<typename...> class...> class...> class...Sorrow
>
struct IsSnowful<Silence<Sorrow...>>
{ static constexpr bool value {true}; };
```

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/is_snowful/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/omennivore/is_snowful.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/is_snowful.test.hpp)
