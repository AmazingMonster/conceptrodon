<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateHarvest`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-harvest">To Index</a></p>

## Description

`Pagelivore::CognateHarvest` accepts an operation and returns a function.

When invoked, the function collects the value result from its arguments and instantiates the operation with the collection.

<pre><code>   Oper
-> Es
-> Oper&lt;Es::value...&gt;</code></pre>

## Type Signature

```Haskell
CognateHarvest
 :: template<auto...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<auto...> class>
struct CognateHarvest
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

We will instantiate `Operation` with the value results from `std::integral_constant<int, 0>, std::integral_constant<int, 1>, std::integral_constant<int, 2>, std::integral_constant<int, 2>`.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = CognateHarvest<Operation>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 1, 2, 2>;

/**** Result ****/
using Result = Metafunction<
    std::integral_constant<int, 0>, std::integral_constant<int, 1>, std::integral_constant<int, 2>, std::integral_constant<int, 2>
>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

```C++
template<template<auto...> class Operation>
struct CognateHarvest
{ 
    template<typename...Crops>
    using Mold = Operation<Crops::value...>; 
};
```

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/cognate_harvest/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/cognate_harvest.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_harvest.test.hpp)
