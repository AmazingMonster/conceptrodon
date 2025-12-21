<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Warehivore::KindredRepack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#warehivore-kindred-repack">To Index</a></p>

## Description

`Warehivore::KindredRepack` accepts a list of packed warehouses and returns a function.

When invoked by an operation, the function concatenates the packed warehouses and instantiates the operation with the result.

<pre><code>   Ware<sub><i>0</i></sub>&lt;Cons<sub><i>0</i></sub>...&gt;, Ware<sub><i>1</i></sub>&lt;Cons<sub><i>1</i></sub>...&gt;, ..., Ware<sub><i>n</i></sub>&lt;Cons<sub><i>n</i></sub>...&gt;
-> Oper
-> Oper&lt;Cons<sub><i>0</i></sub>..., Cons<sub><i>1</i></sub>..., ..., Cons<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
KindredRepack
 :: typename... 
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct KindredRepack
{
    template<template<template<typename...> class...> class>
    alias Flow = RESULT;
};
```

## Examples

Here, we first concatenate `Warehouse_0<Con_0>`,  `Warehouse_1<Con_1, Con_2>` and `Warehouse_2<Con_3>`. Then we pack the result into `NewVessel`:

```C++
/**** NewVessel ****/
template<template<typename...> class...>
struct NewVessel;

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
using SupposedResult = NewVessel<Con_0, Con_1, Con_2, Con_3>;

/**** Result ****/
using Result = KindredRepack
<
    Warehouse_0<Con_0>, 
    Warehouse_1<Con_1, Con_2>,
    Warehouse_2<Con_3>
>::Flow<NewVessel>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Warehivore::KindredRepack` is implemented similarly to [`Warehivore::TypicalPaste`](./typical_paste.doc.md). Intermediate results are kept in `Vehicle`. After all containers are collected, the `Operation` will be invoked.

A simplified version will be as follows:

```C++
template<template<typename...> class...>
struct Vehicle;
```

```C++
template<typename...>
struct KindredRepack {};

// Base Case:

template<template<template<typename...> class...> class Warehouse, template<typename...> class...Containers>
struct KindredRepack<Warehouse<Containers...>>
{
    template<template<template<typename...> class...> class Operation>
    struct Detail
    {
        using type = Operation<Containers...>;
    };

    template<template<template<typename...> class...> class...Agreements>
    using Flow = Detail<Agreements...>::type;
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
struct KindredRepack<WarehouseA<ContainerAs...>, WarehouseB<ContainerBs...>, Others...>
{
    template<template<template<typename...> class...> class Operation>
    struct Detail
    {
        using type = KindredRepack
        <
            Vehicle<ContainerAs..., ContainerBs...>,
            Others...
        >::template Flow<Operation>;
    };

    template<template<template<typename...> class...> class...Agreements>
    using Flow = Detail<Agreements...>::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/warehivore/kindred_repack/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/warehivore/kindred_repack.hpp)
- [Unit test](../../../../tests/unit/metafunctions/warehivore/kindred_repack.test.hpp)
