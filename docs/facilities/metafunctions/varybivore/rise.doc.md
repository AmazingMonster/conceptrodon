<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Rise`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-rise">To Index</a></p>

## Description

`Varybivore::Rise` accepts a list of variables and returns a function.

When invoked by an operation, the function sorts the variables in ascending order and instantiates the operation with the result.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Oper
-> Oper&lt;V<sub>i<sub>0</sub></sub>, V<sub>i<sub>1</sub></sub>, ..., V<sub>i<sub>n</sub></sub>&gt; where V<sub>i<sub>0</sub></sub> &lt; V<sub>i<sub>1</sub></sub> &lt; ... &lt; V<sub>i<sub>n</sub></sub></code></pre>

## Type Signature

```Haskell
Rise
 :: auto...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<auto...>
struct Rise
{
    template<template<auto...> class>
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

/**** Result ****/
using Result = Rise<0, 1, 2, 2>::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Rise` is inspired by the talk [Adapting C++20 Ranges Algorithms for Most Metaprogramming Needs in Fewer Than 1,000 Lines of Code](https://youtu.be/69PuizjrgBM?list=PLPqbaGB3rnNmIaWPvuu4U6LWt1XooNi-L) from Daisy Hollman and Kris Jusiak.

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
template<auto...Variables>
struct Rise
{
    template<template<auto...> class...Agreements>
    using Rail = decltype
    (arise<Agreements..., Variables...>())::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/rise/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/rise.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/rise.test.hpp)
