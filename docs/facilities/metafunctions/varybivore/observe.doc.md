<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Observe`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-observe">To Index</a></p>

## Description

`Varybivore::Observe` accepts a list of variables and returns a function.

When invoked by an operation, the function collects the indices of the variables that can be evaluated to `true` and instantiates the operation with the collection.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Preds...
-> Oper
-> Oper
   <
       V<sub>0</sub> ? (nothing) : 0,
       V<sub>1</sub> ? (nothing) : 1,
                  &vellip;
       V<sub>n</sub> ? (nothing) : n
   ></code></pre>

## Type Signature

```Haskell
Observe
 :: auto...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<auto...>
struct Observe
{
    template<template<auto...> class...>
    alias Rail = RESULT;
};
```

## Examples

We will observe `0, 1, nullptr, 3.0` and use the result to instantiate `Operation`.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation
<
    static_cast<size_t>(1),
    static_cast<size_t>(3)
>;

/**** Result ****/
using Result = Observe<0, 1, nullptr, 3.0>::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Observe` is inspired by the talk [Adapting C++20 Ranges Algorithms for Most Metaprogramming Needs in Fewer Than 1,000 Lines of Code](https://youtu.be/69PuizjrgBM?list=PLPqbaGB3rnNmIaWPvuu4U6LWt1XooNi-L) from Daisy Hollman and Kris Jusiak.

The primary mechanism is implemented within the helper function `stare`.
The talk [Understanding The constexpr 2-Step](https://youtu.be/_AefJX66io8?list=PLPqbaGB3rnNmIaWPvuu4U6LWt1XooNi-L) by Jason Turner provides a relatively detailed explanation of the usage of `std::array`. Here, we will only walk through general ideas.

We will deliver the types using objects of `Tyy`.

```C++
template<typename Element>
struct Tyy
{
    using type = Element;
};
```

Here is the entire implementation.

```C++
template<template<auto...> class Operation, bool...Phenomena>
static consteval auto stare()
{
    // `std::index_sequence<I...>` is created
    // for the length of `Phenomena...`.
    return []<size_t...I>(std::index_sequence<I...>)
    {
        
        // `std::index_sequence<I...>` is created
        // for the count of `true` in `Phenomena...`.
        return []<size_t...J>(std::index_sequence<J...>)
        {
            constexpr auto result = []()
            {
                // We make `std::array phenomena` so that
                // we can access items of `Phenomena...` using [index].
                std::array phenomena {Phenomena...};

                // We will sort `std::array indices`.
                std::array indices {I...};
                
                // We will use this comparison function to sort.
                auto comp = [&phenomena](size_t i, size_t j)
                {
                    return
                    // If `phenomena[i]` is `true` and
                    // `phenomena[j]` is false, then `i` is less than `j`.
                    // Therefore, an index of `true` is always less
                    // than an index of `false`.
                    // As a result, indices of `true` will
                    // assemble in the front of the array.
                        (phenomena[i] && ! phenomena[j])
                    // If `phenomena[i]` and `phenomena[j]` are both `true`,
                    // then we return `i < j` to preserve relative positions.
                    ||  (phenomena[i] && phenomena[j] && i < j);
                };
                
                // `indices` will be reused for the result.
                std::ranges::sort(indices, comp);
                
                // return the result.
                return indices;
            }();

            // `result` is a `std::array`.
            // We collect its front part,
            // which contains all the indices of `true`.
            // Then, we instantiate `Operation`.
            // We return `Tyy` to avoid constructing
            // an object of type `Operation<*>`.
            return Tyy<Operation<result.at(J)...>> {};
        }(std::make_index_sequence<(...+Phenomena)>{});
    }(std::make_index_sequence<sizeof...(Phenomena)>{});
};
```

Finally, we will make an interface to accept arguments:

```C++
template<auto...Phenomena>
struct Observe
{
    template<template<auto...> class...Agreements>
    using Rail = decltype
    (stare<Agreements..., static_cast<bool>(Phenomena)...>())
    ::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/observe/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/varybivore/observe.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/observe.test.hpp)
