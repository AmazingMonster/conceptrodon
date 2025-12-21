<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Morning`

<p style='text-align: right;'><a href="../utilities.md#morning">To Index</a></p>

## Description

`Morning` is a vessel for `Will`.

It also contains a regular function, `size`, which returns the number of items it holds.

## Type Signature

```Haskell
Morning
 :: template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
struct Morning
{
    static constexpr auto size() -> size_t;
};
```

## Examples

We will create a `Morning` with items `Item_0, Item_1, Item_2, Item_3`.
Then, we query its size.

```C++
/**** Items ****/
template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct Item_0;

template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct Item_1;

template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct Item_2;

template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct Item_3;

/**** Packed Vessel ****/
using PackedMorning = Morning
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

/**** Test ****/
static_assert(PackedMorning::size() == 4);
```

## Implementation

```C++
template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Items>
struct Morning
{
    static constexpr size_t size()
    { return sizeof...(Items); }
};
```

## Links

- [Example](../../code/facilities/utilities/morning/implementation.hpp)
- [Source code](../../../conceptrodon/utilities/morning.hpp)
- [Unit test](../../../tests/unit/utilities/morning.test.hpp)
