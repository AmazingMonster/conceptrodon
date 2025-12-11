<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Stockivore::KindredRepack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#stockivore-kindred-repack">To Index</a></p>

## Description

`Stockivore::KindredRepack` accepts a list of packed stockrooms and returns a function.
When invoked by an operation, the function concatenates the packed stockrooms and instantiates the operation with the result.

<pre><code>  Stoc<sub><i>0</i></sub>&lt;Seqs<sub><i>0</i></sub>...&gt;,Stoc<sub><i>1</i></sub>&lt;Seqs<sub><i>1</i></sub>...&gt;, ...,Stoc<sub><i>n</i></sub>&lt;Seqs<sub><i>n</i></sub>...&gt;
-> Oper
-> Oper&lt;Seqs<sub><i>0</i></sub>..., Seqs<sub><i>1</i></sub>..., ..., Seqs<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
KindredRepack
 :: typename... 
 -> template<template<auto...> class...>
```

## Structure

```C++
template<typename...>
struct KindredRepack
{
    template<template<template<auto...> class...> class>
    alias Sail = RESULT;
};
```

## Examples

Here, we first concatenate `Stockroom_0<Seq_0>`,  `Stockroom_1<Seq_1, Seq_2>` and `Stockroom_2<Seq_3>`. Then we pack the result into `Stockroom`:

```C++
/**** NewVessel ****/
template<template<auto...> class...>
struct NewVessel;

/**** Vessels ****/
template<template<auto...> class...>
struct Stockroom_0;

template<template<auto...> class...>
struct Stockroom_1;

template<template<auto...> class...>
struct Stockroom_2;

/**** Items ****/
template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<auto...>
struct Seq_3;

/**** SupposedResult ****/
using SupposedResult = NewVessel<Seq_0, Seq_1, Seq_2, Seq_3>;

/**** Result ****/
using Result = KindredRepack
<
    Stockroom_0<Seq_0>, 
    Stockroom_1<Seq_1, Seq_2>,
    Stockroom_2<Seq_3>
>::Sail<NewVessel>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Stockivore::KindredRepack` is implemented similarly to [`Stockivore::TypicalPaste`](./typical_paste.doc.md). Intermediate results are kept in `Carrier`. After all sequences are collected, the `Operation` will be invoked.

A simplified version will be as follows:

```C++
template<template<auto...> class...>
struct Carrier;
```

```C++
template<typename...>
struct KindredRepack {};

// Base Case:

template<template<template<auto...> class...> class Stockroom, template<auto...> class...Sequences>
struct KindredRepack<Stockroom<Sequences...>>
{
    template<template<template<auto...> class...> class Operation>
    struct Detail
    {
        using type = Operation<Sequences...>;
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = Detail<Agreements...>::type;
};

// Recursive Case:

template
<
    template<template<auto...> class...> class StockroomA,
    template<template<auto...> class...> class StockroomB,
    template<auto...> class...SequenceAs, 
    template<auto...> class...SequenceBs,
    typename...Others
>
struct KindredRepack<StockroomA<SequenceAs...>, StockroomB<SequenceBs...>, Others...>
{
    template<template<template<auto...> class...> class Operation>
    struct Detail
    {
        using type = KindredRepack
        <
            Carrier<SequenceAs..., SequenceBs...>,
            Others...
        >::template Sail<Operation>;
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = Detail<Agreements...>::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/stockivore/kindred_repack/implementation.hpp)
- [Source code](../../../../conceptrodon/stockivore/kindred_repack.hpp)
- [Unit test](../../../../tests/unit/metafunctions/stockivore/kindred_repack.test.hpp)
