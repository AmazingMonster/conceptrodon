<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateHarvest`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-harvest">To Index</a></p>

## Description

`Mouldivore::CognateHarvest` accepts an operation and returns a function.

When invoked, the function collects the type result from its arguments and instantiates the operation with the collection.

<pre><code>   Oper
-> Es...
-> Oper&lt;Es::type...&gt;</code></pre>

## Type Signature

```Haskell
CognateHarvest
 :: template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct CognateHarvest
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

We will instantiate `Operation` with the type results from `AddOne<0>, AddOne<1>, AddOne<2>, AddOne<2>`.

```C++
/**** AddOne ****/
template<auto I>
struct AddOne
{
    using type = std::integral_constant<int, I + 1>;
};

/**** Operation ****/
template<typename...>
struct Operation;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = CognateHarvest<Operation>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation
<
    std::integral_constant<int, 0 + 1>,
    std::integral_constant<int, 1 + 1>, 
    std::integral_constant<int, 2 + 1>, 
    std::integral_constant<int, 2 + 1>
>;

/**** Result ****/
using Result = Metafunction<
    AddOne<0>, AddOne<1>, AddOne<2>, AddOne<2>
>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

```C++
template<template<typename...> class Operation>
struct CognateHarvest
{ 
    template<typename...Crops>
    using Mold = Operation<typename Crops::type...>; 
};
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/cognate_harvest/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/mouldivore/cognate_harvest.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_harvest.test.hpp)
