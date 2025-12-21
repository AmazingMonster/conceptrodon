<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Reverie`

<p style='text-align: right;'><a href="../utilities.md#reverie">To Index</a></p>

## Description

`Reverie` accepts a list of warehouses and returns a function.

When invoked by an operation, the function instantiates the operation with the warehouses.

<pre><code>   Warehouses...
-> Operation
-> Operation&lt;Warehouses...&gt;</code></pre>

It also contains a regular function, `size`, which returns the total number of the warehouses.

<pre><code>size() -> sizeof...(Warehouses)</code></pre>

## Type Signature

```Haskell
Reverie
 :: template<template<typename...> class...> class...
 -> template<template<template<template<typename...> class...> class...> class...>
```

## Structure

```C++
template<template<template<typename...> class...> class...>
struct Reverie
{
    static constexpr auto size() -> size_t;

    template<template<template<template<typename...> class...> class...> class>
    alias Snow = RESULT;
};
```

## Examples

- We will create a `Reverie` with warehouses `Warehouse_0, Warehouse_1, Warehouse_2, Warehouse_3`.
Then, we will transport the warehouses to `Operation`.

```C++
/**** Items ****/
template<template<typename...> class...>
struct Warehouse_0;

template<template<typename...> class...>
struct Warehouse_1;

template<template<typename...> class...>
struct Warehouse_2;

template<template<typename...> class...>
struct Warehouse_3;

/**** Operation ****/
template<template<template<typename...> class...> class...>
struct Operation;

/**** Packed Vessel ****/
using PackedReverie = Reverie
<
    Warehouse_0, 
    Warehouse_1, 
    Warehouse_2, 
    Warehouse_3
>;

/**** SupposedResult ****/
using SupposedResult = Operation
<
    Warehouse_0, 
    Warehouse_1, 
    Warehouse_2, 
    Warehouse_3
>;

/**** Result ****/
using Result = PackedReverie::Snow<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We can check the size of a packed `Reverie`.

```C++
static_assert(PackedReverie::size() == 4);
```

## Implementation

```C++
template<template<template<typename...> class...> class...Warehouses>
struct Reverie
{
    static constexpr size_t size()
    { return sizeof...(Warehouses); }

    template<template<template<template<typename...> class...> class...> class Sorrow>
    struct Detail { using type = Sorrow<Warehouses...>; };

    template<template<template<template<typename...> class...> class...> class...Sorrow>
    using Snow = Detail<Sorrow...>::type;
};
```

## Links

- [Example](../../code/facilities/utilities/reverie/implementation.hpp)
- [Source code](../../../conceptrodon/utilities/reverie.hpp)
- [Unit test](../../../tests/unit/utilities/reverie.test.hpp)
