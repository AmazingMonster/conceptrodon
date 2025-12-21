<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsRoadful`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-is-roadful">To Index</a></p>

## Description

`Omennivore::IsRoadful` accepts a type.
It returns true if the type is a packed `Road` and returns false if otherwise.

<pre><code>   Type
-> Type == Road&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsRoadful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsRoadful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsRoadful_v {RESULT};
```

## Examples

```C++
/**** Vessel ****/
template<template<typename...> class...>
struct RoadLike;

/**** Items ****/
template<typename...>
struct MoldLike_0;

template<typename...>
struct MoldLike_1;

/**** Tests ****/
static_assert(IsRoadful<RoadLike<MoldLike_0, MoldLike_1>>::value);
static_assert(! IsRoadful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsRoadful
{ static constexpr bool value {false}; };

template
<
    template<template<typename...> class...> class Warehouse,
    template<typename...> class...Containers
>
struct IsRoadful<Warehouse<Containers...>>
{ static constexpr bool value {true}; };
```

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/is_roadful/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/omennivore/is_roadful.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/is_roadful.test.hpp)
