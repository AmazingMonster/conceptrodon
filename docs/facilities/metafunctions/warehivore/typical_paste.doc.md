<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Warehivore::TypicalPaste`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#warehivore-typical-paste">To Index</a></p>

## Description

`Warehivore::TypicalPaste` accepts a list of packed warehouses.
It concatenates them together and uses the first warehouse to hold the result.

<pre><code>   Ware<sub><i>0</i></sub>&lt;Cons<sub><i>0</i></sub>...&gt;, Ware<sub><i>1</i></sub>&lt;Cons<sub><i>1</i></sub>...&gt;, ..., Ware<sub><i>n</i></sub>&lt;Cons<sub><i>n</i></sub>...&gt;
-> Ware<sub><i>0</i></sub>&lt;Cons<sub><i>0</i></sub>..., Cons<sub><i>1</i></sub>..., ..., Cons<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
TypicalPaste
 :: typename...
 -> typename
```

## Structure

```C++
template<typename...>
struct TypicalPaste
{
    using type = RESULT;
};
```

## Examples

Here, we paste `Warehouse_0<Con_0>`,  `Warehouse_1<Con_1, Con_2>` and `Warehouse_2<Con_3>` together:

```C++
/**** Vessels ****/
template<template<typename...> class...>
struct Warehouse_0;

template<template<typename...> class...>
struct Warehouse_1;

template<template<typename...> class...>
struct Warehouse_2;

/**** Items ****/
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

/**** SupposedResult ****/
using SupposedResult = Warehouse_0<Con_0, Con_1, Con_2, Con_3>;

/**** Result ****/
using Result = TypicalPaste
<
    Warehouse_0<Con_0>, 
    Warehouse_1<Con_1, Con_2>,
    Warehouse_2<Con_3>
>::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `TypicalPaste` using recursion over the total number of packed warehouses.

- **Base Case:** Handle several amounts directly;
- **Recursive Case:**
  1. Concatenate several packed warehouses at the front directly and place the result into the first warehouse;
  2. Invoke `TypicalPaste` with the newly packed first warehouse and the unhandled warehouses.

```C++
template<typename...>
struct TypicalPaste {};

// Base Case:

template<typename PackedWarehouse>
struct TypicalPaste<PackedWarehouse>
{
    using type = PackedWarehouse;
};

// Recursive Case:

template
<
    template<template<typename...> class...> class WarehouseA,
    template<template<typename...> class...> class WarehouseB,
    template<typename...> class...ContainerAs, 
    template<typename...> class...ContainerBs,
    typename...Others
>
struct TypicalPaste<WarehouseA<ContainerAs...>, WarehouseB<ContainerBs...>, Others...>
{
    using type = typename TypicalPaste
    <
        WarehouseA<ContainerAs..., ContainerBs...>,
        Others...
    >::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/warehivore/typical_paste/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/warehivore/typical_paste.hpp)
- [Unit test](../../../../tests/unit/metafunctions/warehivore/typical_paste.test.hpp)
