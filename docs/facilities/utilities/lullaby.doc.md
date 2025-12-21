<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Lullaby`

<p style='text-align: right;'><a href="../utilities.md#lullaby">To Index</a></p>

## Description

`Lullaby` accepts a list of items and returns a function.

When invoked by an operation, the function instantiates the operation with the items.

<pre><code>   Items...
-> Operation
-> Operation&lt;Items...&gt;</code></pre>

It also contains a regular function, `size`, which returns the total number of the items.

<pre><code>size() -> sizeof...(Items)</code></pre>

## Type Signature

```Haskell
Lullaby
 :: template<template<template<template<typename...> class...> class...> class...> class...
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<typename...> class...> class...> class...> class...>
struct Lullaby
{
    static constexpr auto size() -> size_t;

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class>
    alias Grit = RESULT;
};
```

## Examples

- We will create a `Lullaby` with items `Item_0, Item_1, Item_2, Item_3`.
Then, we will transport the items to `Operation`.

```C++
/**** Items ****/
template<template<template<template<typename...> class...> class...> class...>
struct Item_0;

template<template<template<template<typename...> class...> class...> class...>
struct Item_1;

template<template<template<template<typename...> class...> class...> class...>
struct Item_2;

template<template<template<template<typename...> class...> class...> class...>
struct Item_3;

/**** Operation ****/
template<template<template<template<template<typename...> class...> class...> class...> class...>
struct Operation;

/**** Packed Vessel ****/
using PackedLullaby = Lullaby
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

/**** SuppsedResult ****/
using SupposedResult = Operation
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

/**** Result ****/
using Result = PackedLullaby::Grit<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We can check the size of a packed `Lullaby`.

```C++
static_assert(PackedLullaby::size() == 4);
```

## Implementation

```C++
template<template<template<template<template<typename...> class...> class...> class...> class...Items>
struct Lullaby
{
    static constexpr size_t size()
    { return sizeof...(Items); }

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class Tranquil>
    struct Detail { using type = Tranquil<Items...>; };

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Tranquil>
    using Grit = Detail<Tranquil...>::type;
};
```

## Links

- [Example](../../code/facilities/utilities/lullaby/implementation.hpp)
- [Source code](../../../conceptrodon/utilities/lullaby.hpp)
- [Unit test](../../../tests/unit/utilities/lullaby.test.hpp)
