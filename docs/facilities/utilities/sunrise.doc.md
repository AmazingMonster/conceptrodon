<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Sunrise`

<p style='text-align: right;'><a href="../utilities.md#sunrise">To Index</a></p>

## Description

`Sunrise` is a vessel for `Grit`.

It also contains a regular function, `size`, which returns the number of items it holds.

## Type Signature

```Haskell
Sunrise
 :: template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct Sunrise
{
    static constexpr auto size() -> size_t;
};
```

## Examples

We will create a `Sunrise` with items `Item_0, Item_1, Item_2, Item_3`.
Then, we query its size.

```C++
/**** Items ****/
template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct Item_0;

template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct Item_1;

template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct Item_2;

template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct Item_3;

/**** Packed Vessel ****/
using PackedSunrise = Sunrise
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

/**** Test ****/
static_assert(PackedSunrise::size() == 4);
```

## Implementation

```C++
template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Items>
struct Sunrise
{
    static constexpr size_t size()
    { return sizeof...(Items); }
};
```

## Links

- [Example](../../code/facilities/utilities/sunrise/implementation.hpp)
- [Source code](../../../conceptrodon/sunrise.hpp)
