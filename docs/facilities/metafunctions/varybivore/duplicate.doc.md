<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Duplicate`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-duplicate">To Index</a></p>

## Description

`Varybivore::Duplicate` accepts an variable.
Its first layer accepts an amount and returns a function.

When invoked by an operation, the function creates copies of the variable of the amount and instantiates the operation with the result.

<pre><code>   E
-> N
-> Oper
-> Oper&lt;E<sub>1</sub>, E<sub>2</sub>, ..., E<sub>N</sub>&gt;</code></pre>

## Type Signature

```Haskell
Duplicate
 :: auto...
 -> auto...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<auto>
struct Duplicate
{
    template<auto>
    alias Page
    {
        template<template<auto...> class>
        alias Rail = RESULT;
    };
};
```

## Examples

We will instantiate `Operation` with four `0`:

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 0, 0, 0>;

/**** Result ****/
using Result = Duplicate<0>
::Page<4>
::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

One way to implement `Duplicate` is through recursion.
We start with an empty list, adding the variable while subtracting the required number of copies until the number reaches zero.

Our method will be different.
The goal is to generate all the copies 'simultaneously' in the sense that there are no intermediate stages.
We will achieve this by pack expansion.

We want to bundle the variable and each index from a `std::index_sequence`.
Then, we will pull out the variable from each bundle by a pack expansion over indices.

First, we need to create a `Bundle_v`:

```C++
template<auto Variable, auto>
static constexpr auto Bundle_v
{Variable};
```

The entire implementation is presented below:

```C++
template<auto Variable>
struct Duplicate
{
    template<typename>
    struct ProtoMold {};

    template<size_t...I>
    struct ProtoMold<std::index_sequence<I...>>
    {
        template<template<auto...> class Operation>
        struct Detail
        {
            using type = Operation
            <Bundle_v<Variable, I>...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<size_t I>
    struct ProtoPage
    : public ProtoMold<std::make_index_sequence<I>>
    {};

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/duplicate/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/duplicate.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/duplicate.test.hpp)
