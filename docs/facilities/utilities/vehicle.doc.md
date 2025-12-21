<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Vehicle`

<p style='text-align: right;'><a href="../utilities.md#vehicle">To Index</a></p>

## Description

`Vehicle` accepts a list of containers and returns a function.

When invoked by an operation, the function instantiates the operation with the containers.

<pre><code>   Containers...
-> Operation
-> Operation&lt;Containers...&gt;</code></pre>

It also contains a regular function, `size`, which returns the total number of the containers.

<pre><code>size() -> sizeof...(Containers)</code></pre>

## Type Signature

```Haskell
Vehicle
 :: template<typename...> class...
 -> template<template<template<typename...> class...> class...>
```

## Structure

```C++
template<template<typename...> class...>
struct Vehicle
{
    static constexpr auto size() -> size_t;

    template<template<template<typename...> class...> class>
    alias Flow = RESULT;
};
```

## Examples

- We will create a `Vehicle` with containers `Container_0, Container_1, Container_2, Container_3`.
Then, we will transport the containers to `Operation`.

```C++
/**** Items ****/
template<typename...>
struct Container_0;

template<typename...>
struct Container_1;

template<typename...>
struct Container_2;

template<typename...>
struct Container_3;

/**** Operation ****/
template<template<typename...> class...>
struct Operation;

/**** Packed Vessel ****/
using PackedVehicle = Vehicle
<
    Container_0, 
    Container_1, 
    Container_2, 
    Container_3
>;

/**** SuppsedResult ****/
using SupposedResult = Operation
<
    Container_0, 
    Container_1, 
    Container_2, 
    Container_3
>;

/**** Result ****/
using Result = PackedVehicle::Flow<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We can check the size of a packed `Vehicle`.

```C++
static_assert(PackedVehicle::size() == 4);
```

## Implementation

```C++
template<template<typename...> class...Containers>
struct Vehicle
{
    static constexpr size_t size()
    { return sizeof...(Containers); }

    template<template<template<typename...> class...> class Warehouse>
    struct Detail { using type = Warehouse<Containers...>; };

    template<template<template<typename...> class...> class...Warehouses>
    using Flow = Detail<Warehouses...>::type;
};
```

## Links

- [Example](../../code/facilities/utilities/vehicle/implementation.hpp)
- [Source code](../../../conceptrodon/utilities/vehicle.hpp)
- [Unit test](../../../tests/unit/utilities/vehicle.test.hpp)
