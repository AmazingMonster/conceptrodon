<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Stockivore::TypicalPaste`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#stockivore-typical-paste">To Index</a></p>

## Description

`Stockivore::TypicalPaste` accepts a list of packed stockrooms.
It concatenates them together and uses the first stockroom to hold the result.

<pre><code>   Stoc<sub><i>0</i></sub>&lt;Seqs<sub><i>0</i></sub>...&gt;, Stoc<sub><i>1</i></sub>&lt;Seqs<sub><i>1</i></sub>...&gt;, ..., Stoc<sub><i>n</i></sub>&lt;Seqs<sub><i>n</i></sub>...&gt;
-> Stoc<sub><i>0</i></sub>&lt;Seqs<sub><i>0</i></sub>..., Seqs<sub><i>1</i></sub>..., ..., Seqs<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
TypicalPaste
 :: typename...
 -> typename
```

## Structure

```C++
template<typename...>
struct TypicalPaste
{
    using type = RESULT;
};
```

## Examples

Here, we paste `Stockroom_0<Seq_0>`,  `Stockroom_1<Seq_1, Seq_2>` and `Stockroom_2<Seq_3>` together:

```C++
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
using SupposedResult = Stockroom_0<Seq_0, Seq_1, Seq_2, Seq_3>;

/**** Result ****/
using Result = TypicalPaste
<
    Stockroom_0<Seq_0>, 
    Stockroom_1<Seq_1, Seq_2>,
    Stockroom_2<Seq_3>
>::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `TypicalPaste` using recursion over the total number of packed stockrooms.

- **Base Case:** Handle several amounts directly;
- **Recursive Case:**
  1. Concatenate several packed stockrooms at the front directly and place the result into the first stockroom;
  2. Invoke `TypicalPaste` with the newly packed first stockroom and the unhandled stockrooms.

A simplified version will be as follows:

```C++
template<typename...>
struct TypicalPaste {};

// Base Case:

template<typename PackedStockroom>
struct TypicalPaste<PackedStockroom>
{
    using type = PackedStockroom;
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
struct TypicalPaste<StockroomA<SequenceAs...>, StockroomB<SequenceBs...>, Others...>
{
    using type = typename TypicalPaste
    <
        StockroomA<SequenceAs..., SequenceBs...>,
        Others...
    >::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/stockivore/typical_paste/implementation.hpp)
- [Source code](../../../../conceptrodon/stockivore/paste.hpp)
- [Unit test](../../../../tests/unit/metafunctions/stockivore/typical_paste.test.hpp)
