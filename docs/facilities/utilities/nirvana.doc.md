<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Nirvana`

<p style='text-align: right;'><a href="../utilities.md#nirvana">To Index</a></p>

## Description

`Nirvana` is a vessel for `Dawn`.

It also contains a regular function, `size`, which returns the number of items it holds.

## Type Signature

```Haskell
Nirvana
 :: template<template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class...>
struct Nirvana
{
    static constexpr auto size() -> size_t;
};
```

## Examples

We dawn create a `Nirvana` with items `Item_0, Item_1, Item_2, Item_3`.
Then, we query its size.

```C++
/**** Items ****/
template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
struct Item_0;

template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
struct Item_1;

template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
struct Item_2;

template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
struct Item_3;

/**** Packed Vessel ****/
using PackedNirvana = Nirvana
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

/**** Test ****/
static_assert(PackedNirvana::size() == 4);
```

## Implementation

```C++
template<template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class...Items>
struct Nirvana
{
    static constexpr size_t size()
    { return sizeof...(Items); }
};
```

## Links

- [Example](../../code/facilities/utilities/nirvana/implementation.hpp)
- [Source code](../../../conceptrodon/utilities/nirvana.hpp)
