<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::Agent`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#roadrivore-agent">To Index</a></p>

## Description

`Roadrivore::Agent` accepts an operation and returns a function.

When invoked by a packed warehouse, the function extracts the list of containers from the packed warehouse and instantiates the operation with the list.

<pre><code>   Oper
-> Ware&lt;Cons...&gt;
-> Oper&lt;Cons...&gt;</code></pre>

## Type Signature

```Haskell
Agent
 :: template<template<typename...> class...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<template<typename...> class...> class>
struct Agent
{
    template<typename>
    alias Mold = RESULT;
};
```

## Examples

- We will create an `Agent` of the `Operation` and invoke the returned function with `Vehicle<Con_0, Con_1, Con_2>`.

```C++
/**** Vehicle ****/
template<template<typename...> class...>
struct Vehicle;

/**** Arguments ****/
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

/**** Operation ****/
template<template<typename...> class...>
struct Operation;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Agent<Operation>::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<Con_0, Con_1, Con_2>;

/**** Result ****/
using Result = Metafunction<Vehicle<Con_0, Con_1, Con_2>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Roadrivore::Agent` uses partial template specialization to extract containers from a packed warehouse. Here is the entire implementation:

```C++
template<template<template<typename...> class...> class Operation>
struct Agent
{
    template<typename>
    struct Detail {};

    template<template<template<typename...> class...> class Warehouse, template<typename...> class...Containers>
    struct Detail<Warehouse<Containers...>>
    { using type = Operation<Containers...>; };
    
    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/roadrivore/agent/implementation.hpp)
- [Source code](../../../../conceptrodon/roadrivore/agent.hpp)
- [Unit test](../../../../tests/unit/metafunctions/roadrivore/agent.test.hpp)
