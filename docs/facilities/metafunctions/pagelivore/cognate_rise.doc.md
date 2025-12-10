<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateRise`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-rise">To Index</a></p>

## Description

`Pagelivore::CognateRise` accepts an operation and returns a function.

When invoked, the function sorts the arguments in ascending order and instantiates the operation with the result.

<pre><code>   Oper
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Oper&lt;V<sub>i<sub>0</sub></sub>, V<sub>i<sub>1</sub></sub>, ..., V<sub>i<sub>n</sub></sub>&gt; where V<sub>i<sub>0</sub></sub> &lt; V<sub>i<sub>1</sub></sub> &lt; ... &lt; V<sub>i<sub>n</sub></sub></code></pre>

## Type Signature

```Haskell
CognateRise
 :: template<auto...> class...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct CognateRise
{
    template<auto...>
    alias Rail = RESULT;
};
```

## Examples

We will sort `2, 2, 1, 0` and use the result to instantiate `Operation`.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 1, 2, 2>;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = CognateRise<Operation>
::Page<Args...>;

/**** Result ****/
using Result = Metafunction<0, 1, 2, 2>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`CognateRise` is inspired by the talk [Adapting C++20 Ranges Algorithms for Most Metaprogramming Needs in Fewer Than 1,000 Lines of Code](https://youtu.be/69PuizjrgBM?list=PLPqbaGB3rnNmIaWPvuu4U6LWt1XooNi-L) from Daisy Hollman and Kris Jusiak.

The primary mechanism is implemented within the helper function `arise`.
The talk [Understanding The constexpr 2-Step](https://youtu.be/_AefJX66io8?list=PLPqbaGB3rnNmIaWPvuu4U6LWt1XooNi-L) by Jason Turner provides a relatively detailed explanation of the usage of `std::array`. Here, we will only walk through general ideas.

```C++
template<template<auto...> class Operation, auto...Variables>
static consteval auto arise()
{    
    // `std::index_sequence<I...>` is created
    // for the length of `Variables...`.
    return []<size_t...I>(std::index_sequence<I...>)
    {
        constexpr auto sorted = []()
        {
            std::array original {Variables...};
            // `original` will be reused for the result.
            std::ranges::sort(original);
            return original;
        }();
        // We use `std::type_identity` to avoid construct
        // an object of type `Operation<*>`.
        return std::type_identity<Operation<sorted.at(I)...>> {};
    }(std::make_index_sequence<sizeof...(Variables)>{});
};
```

Finally, we will make an interface to accept arguments:

```C++
template<template<auto...> class Operation>
struct CognateRise
{
    template<auto...Variables>
    using Page = decltype(arise<Operation, Variables...>())
    ::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/cognate_rise/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/cognate_rise.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_rise.test.hpp)
