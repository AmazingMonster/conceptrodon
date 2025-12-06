<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsFlowful`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-is-flowful">To Index</a></p>

## Description

`Omennivore::IsFlowful` accepts a type.
It returns true if the type is a packed `Flow` and returns false if otherwise.

<pre><code>   Type
-> Type == Flow&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsFlowful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsFlowful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsFlowful_v {RESULT};
```

## Examples

```C++
/**** Vessel ****/
template<template<template<typename...> class...> class...>
struct FlowLike;

/**** Items ****/
template<template<typename...> class...>
struct RoadLike_0;

template<template<typename...> class...>
struct RoadLike_1;

/**** Tests ****/
static_assert(IsFlowful<FlowLike<RoadLike_0, RoadLike_1>>::value);
static_assert(! IsFlowful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsFlowful
{ static constexpr bool value {false}; };

template
<
    template<template<template<typename...> class...> class...> class Sorrow,
    template<template<typename...> class...> class...Warehouses
>
struct IsFlowful<Sorrow<Warehouses...>>
{ static constexpr bool value {true}; };
```

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/is_flowful/implementation.hpp)
- [Source code](../../../../conceptrodon/omennivore/is_flowful.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/is_flowful.test.hpp)
