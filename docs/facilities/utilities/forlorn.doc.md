<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Forlorn`

<p style='text-align: right;'><a href="../utilities.md#forlorn">To Index</a></p>

## Description

`Forlorn` accepts a list of items and returns a function.

When invoked by an operation, the function instantiates the operation with the items.

<pre><code>   Items...
-> Operation
-> Operation&lt;Items...&gt;</code></pre>

It also contains a regular function, `size`, which returns the total number of the items.

<pre><code>size() -> sizeof...(Items)</code></pre>

## Type Signature

```Haskell
Forlorn
 :: template<template<template<typename...> class...> class...> class...
 -> template<template<template<template<template<typename...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<typename...> class...> class...> class...>
struct Forlorn
{
    static constexpr auto size() -> size_t;

    template<template<template<template<template<typename...> class...> class...> class...> class>
    alias Cool = RESULT;
};
```

## Examples

- We will create a `Forlorn` with items `Item_0, Item_1, Item_2, Item_3`.
Then, we will transport the items to `Operation`.

```C++
/**** Items ****/
template<template<template<typename...> class...> class...>
struct Item_0;

template<template<template<typename...> class...> class...>
struct Item_1;

template<template<template<typename...> class...> class...>
struct Item_2;

template<template<template<typename...> class...> class...>
struct Item_3;

/**** Operation ****/
template<template<template<template<typename...> class...> class...> class...>
struct Operation;

/**** Packed Vessel ****/
using PackedForlorn = Forlorn
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
using Result = PackedForlorn::Cool<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We can check the size of a packed `Forlorn`.

```C++
static_assert(PackedForlorn::size() == 4);
```

## Implementation

```C++
template<template<template<template<typename...> class...> class...> class...Items>
struct Forlorn
{
    static constexpr size_t size()
    { return sizeof...(Items); }

    template<template<template<template<template<typename...> class...> class...> class...> class Silence>
    struct Detail { using type = Silence<Items...>; };

    template<template<template<template<template<typename...> class...> class...> class...> class...Silence>
    using Cool = Detail<Silence...>::type;
};
```

## Links

- [Example](../../code/facilities/utilities/forlorn/implementation.hpp)
- [Source code](../../../conceptrodon/forlorn.hpp)
