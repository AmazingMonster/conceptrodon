<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Duplicate`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-duplicate">To Index</a></p>

## Description

`Typelivore::Duplicate` accepts an element.
Its first layer accepts an amount and returns a function.

When invoked by an operation, the function creates copies of the element of the amount and instantiates the operation with the result.

<pre><code>   E
-> N
-> Oper
-> Oper&lt;E,<sub><sub>1</sub></sub> E,<sub><sub>2</sub></sub> ...,<sub><sub>N-1</sub></sub> E&gt;</code></pre>

## Type Signature

```Haskell
Duplicate
 :: typename...
 -> auto...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename>
struct Duplicate
{
    template<auto>
    alias Page
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
};
```

## Examples

We will instantiate `Operation` with four `int`:

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int, int, int, int>;

/**** Result ****/
using Result = Duplicate<int>
::Page<4>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

One way to implement `Duplicate` is through recursion.
We start with an empty list, adding the element while subtracting the required number of copies until the number reaches zero.

Our method will be different.
The goal is to generate all the copies 'simultaneously' in the sense that there are no intermediate stages.
We will achieve this by pack expansion.

We want to bundle the element and each index from a `std::index_sequence`.
Then, we will pull out the element from each bundle by a pack expansion over indices.

First, we need to create a `Bundle_t`:

```C++
template<typename Element, auto>
using Bundle_t = Element;
```

The entire implementation is presented below:

```C++
template<typename Element>
struct Duplicate
{
    template<typename>
    struct ProtoMold {};

    template<size_t...I>
    struct ProtoMold<std::index_sequence<I...>>
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation
            <Bundle_t<Element, I>...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
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

- [Example](../../../code/facilities/metafunctions/typelivore/duplicate/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/typelivore/duplicate.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/duplicate.test.hpp)
