<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Repack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-repack">To Index</a></p>

## Description

`Mouldivore::Repack` accepts an operation and returns a function.

When invoked by a list of packed containers, the function concatenates the packed containers and instantiates the operation with the result.

<pre><code>   Oper
-> Con<sub><i>0</i></sub>&lt;Es<sub><i>0</i></sub>...&gt;, Con<sub><i>1</i></sub>&lt;Es<sub><i>1</i></sub>...&gt;, ..., Con<sub><i>n</i></sub>&lt;Es<sub><i>n</i></sub>...&gt;
-> Oper&lt;Es<sub><i>0</i></sub>..., Es<sub><i>1</i></sub>..., ..., Es<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
Repack
 :: template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct Repack
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

Here, we first concatenate `std::tuple<int>`,  `std::tuple<int*, int**>` and `std::tuple<int**>`. Then we pack the result into `NewVessel`:

```C++
/**** NewVessel ****/
template<typename...Args>
requires (sizeof...(Args) == 4)
struct NewVessel;

/**** SupposedResult ****/
using SupposedResult = NewVessel<int, int*, int**, int***>;

/**** Result ****/
using Result = Repack<NewVessel>
::Mold
<
    std::tuple<int>,
    std::tuple<int*, int**>,
    std::tuple<int***>
>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Mouldivore::Repack` is implemented similarly to `Typelivore::TypicalPaste`. Intermediate results are kept in `Capsule`.

```C++
template<typename...>
struct Capsule;
```

After all elements are collected, the `Operation` will be invoked.

A simplified version will be as follows:

```C++
template<template<typename...> class Operation>
struct Repack
{
    template<typename...>
    struct Detail {};

// Base Case:

    template<template<typename...> class Container, typename...Elements>
    struct Detail<Container<Elements...>>
    {
        using type = Operation<Elements...>;
    };

// Recursive Case:

    template
    <
        template<typename...> class ContainerA,
        template<typename...> class ContainerB,
        typename...ElementAs, 
        typename...ElementBs,
        typename...Others
    >
    struct Detail<ContainerA<ElementAs...>, ContainerB<ElementBs...>, Others...>
    {
        using type = Detail
        <
            Capsule<ElementAs..., ElementBs...>,
            Others...
        >::type;
    };

    template<typename...PackedContainers>
    using Mold = Detail<PackedContainers...>::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/repack/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/mouldivore/repack.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/repack.test.hpp)
