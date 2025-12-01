<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Cotanivore::KindredRepack`

<p style='text-align: right'><a href="../../../facilities/metafunctions.md#cotanivore-kindred-repack">To Index</a></p>

## Description

`Cotanivore::KindredRepack` accepts a list of packed containers and returns a function.
When invoked by an operation, the function concatenates the packed containers and instantiates the operation with the result.

<pre><code>   Con<sub><i>0</i></sub>&lt;Es<sub><i>0</i></sub>...&gt;, Con<sub><i>1</i></sub>&lt;Es<sub><i>1</i></sub>...&gt;, ..., Con<sub><i>n</i></sub>&lt;Es<sub><i>n</i></sub>...&gt;
-> Op
-> Op&lt;Es<sub><i>0</i></sub>..., Es<sub><i>1</i></sub>..., ..., Es<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
KindredRepack
 :: typename...
 -> template<typename...>
```

## Structure

```C++
template<typename...>
struct KindredRepack
{
    template<template<typename...> class>
    alias Road = RESULT;
};
```

## Examples

Here, we first concatenate `std::tuple<int>`,  `std::tuple<float, float*>` and `std::tuple<double>`. Then we pack the result into `NewVessel`:

```C++
/**** NewVessel ****/
template<typename...Args>
requires (sizeof...(Args) == 4)
struct NewVessel;

/**** SupposedResult ****/
using SupposedResult = NewVessel<int, float, float*, double>;

/**** Result ****/
using Result = KindredRepack
<
    std::tuple<int>, 
    std::tuple<float, float*>,
    std::tuple<double>
>::Road<NewVessel>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Cotanivore::KindredRepack` is implemented similarly to [`Cotanivore::TypicalPaste`](./typical_paste.doc.md). Intermediate results are kept in [`Capsule`](../../utilities/capsule.doc.md). After all elements are collected, the `Operation` will be invoked.

A simplified version will be as follows:

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** KindredRepack ****/
template<typename...>
struct KindredRepack {};

// Base Case:

template<template<typename...> class Container, typename...Elements>
struct KindredRepack<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<Elements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
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
struct KindredRepack<ContainerA<ElementAs...>, ContainerB<ElementBs...>, Others...>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = KindredRepack
        <
            // Put ElementAs... and ElementBs into the `Capsule`
            Capsule<ElementAs..., ElementBs...>,
            Others...
        >::template Road<Operation>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/cotanivore/kindred_repack/implementation.hpp)
- [Source code](../../../../conceptrodon/cotanivore/kindred_repack.hpp)
- [Unit test](../../../../tests/unit/metafunctions/cotanivore/kindred_repack.test.hpp)
