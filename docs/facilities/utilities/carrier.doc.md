<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Carrier`

<p style='text-align: right;'><a href="../utilities.md#carrier">To Index</a></p>

## Description

`Carrier` accepts a list of sequences and returns a function.

When invoked by an operation, the function instantiates the operation with the sequences.

<pre><code>   Seqs...
-> Oper
-> Oper&lt;Seqs...&gt;</code></pre>

It also contains a regular function, `size`, which returns the total number of the sequences.

<pre><code>size() -> sizeof...(Sequences)</code></pre>

## Type Signature

```Haskell
Carrier
 :: template<auto...> class...
 -> template<template<template<auto...> class...> class...>
```

## Structure

```C++
template<template<auto...> class...>
struct Carrier
{
    static constexpr auto size() -> size_t;

    template<template<template<auto...> class...> class>
    alias Sail = RESULT;
};
```

## Examples

- We will create a `Carrier` with sequences `Sequence_0, Sequence_1, Sequence_2, Sequence_3`.
Then, we will transport the sequences to `Operation`.

```C++
/**** Items ****/
template<auto...>
struct Sequence_0;

template<auto...>
struct Sequence_1;

template<auto...>
struct Sequence_2;

template<auto...>
struct Sequence_3;

/**** Operation ****/
template<template<auto...> class...>
struct Operation;

/**** Packed Vessel ****/
using PackedCarrier = Carrier
<
    Sequence_0, 
    Sequence_1, 
    Sequence_2, 
    Sequence_3
>;

/**** SuppsedResult ****/
using SupposedResult = Operation
<
    Sequence_0, 
    Sequence_1, 
    Sequence_2, 
    Sequence_3
>;

/**** Result ****/
using Result = PackedCarrier::Sail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We can check the size of a packed `Carrier`.

```C++
static_assert(PackedCarrier::size() == 4);
```

## Implementation

```C++
template<template<auto...> class...Sequences>
struct Carrier
{
    static constexpr size_t size()
    { return sizeof...(Sequences); }

    template<template<template<auto...> class...> class Stockroom>
    struct Detail { using type = Stockroom<Sequences...>; };

    template<template<template<auto...> class...> class...Stockrooms>
    using Sail = Detail<Stockrooms...>::type;
};
```

## Links

- [Example](../../code/facilities/utilities/carrier/implementation.hpp)
- [Source code](../../../conceptrodon/utilities/carrier.hpp)
