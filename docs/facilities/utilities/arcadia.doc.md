<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Arcadia`

<p style='text-align: right;'><a href="../utilities.md#arcadia">To Index</a></p>

## Description

`Arcadia` is a vessel for `Glow`.

It also contains a regular function, `size`, which returns the number of items it holds.

## Type Signature

```Haskell
Arcadia
 :: template<template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class...>
struct Arcadia
{
    static constexpr auto size() -> size_t;
};
```

## Examples

We glow create a `Arcadia` with items `Item_0, Item_1, Item_2, Item_3`.
Then, we query its size.

```C++
/**** Items ****/
template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct Item_0;

template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct Item_1;

template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct Item_2;

template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct Item_3;

/**** Packed Vessel ****/
using PackedArcadia = Arcadia
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

/**** Test ****/
static_assert(PackedArcadia::size() == 4);
```

## Implementation

```C++
template<template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class...Items>
struct Arcadia
{
    static constexpr size_t size()
    { return sizeof...(Items); }
};
```

## Links

- [Example](../../code/facilities/utilities/arcadia/implementation.hpp)
- [Source code](../../../conceptrodon/utilities/arcadia.hpp)
- [Unit test](../../../tests/unit/utilities/arcadia.test.hpp)
