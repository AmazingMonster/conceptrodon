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
/**** New Vessel ****/
template<template<auto...> class...>
struct Stockroom;

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
using SupposedResult = Stockroom<Seq_0, Seq_1, Seq_2, Seq_3>;

/**** Result ****/
using Result = KindredRepack
<
    Stockroom_0<Seq_0>, 
    Stockroom_1<Seq_1, Seq_2>,
    Stockroom_2<Seq_3>
>::Sail<Stockroom>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Stockivore::KindredRepack` is implemented similarly to [`Stockivore::TypicalPaste`](./typical_paste.doc.md). Intermediate results are kept in `Carrier`. After all sequences are collected, the `Operation` will be invoked.

A simplified version will be as follows:

```C++
template<template<auto...> class...>
struct Carrier;

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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBIaAKykAA6oCoRODB7evnrJqY4CQSHhLFExXPG2mPb5DEIETMQEmT5%2BXJXV6XUNBIVhkdGxCQr1jc3ZbcPdvcWlgwCUtqhexMjsHAD0AFTbO7t7%2B5vrJhoAgls7ANQAIpiJrozIeJgKF7tHp%2BcHX3vvJ8dnuwubgaxCexFeO1%2BBEwLESBmhJgAzG5obD4ZgkcCvEQAHR4pHYC7IAwKBR4nEE/7DYheBxAkFgpFWU7/T7fdnbX5si4ASTRMMY9RqEM5rI54sO/zFlwA0sF0MRMOgAEq3JjIADWIslp1RcKYCORBAAnndmGxyZTTtTaQQLnKGAqlarEuqtSYAOxWD1XJlSj7rC4WJhKelKED%2Bk569GY6MGjFGmH6w1Y3H4xGE4khsnpzMkl51VCa4ioVAsUgXOMppjY1CWjNE/PkoSYACOXgezytJxtdIdTpVas1mMLxdLLBHbY7DFWOYpGe7nuZJwuq8rSZjibR8djG53yJrafneez9ZPpIuAHk7sQDelu2uLr27Td6nR/o%2Blx/H2uvKkjJWpqYBcSJXFeN53gIk7tp2c6Uoiy6fj6fosqcj5VgmKJ7imGGYoeda5o2p6EVmpLkicwCKgKggKA%2Bv7/sAFxCEwdAgYiYGvixtCYhRVFsDRZ4gCAJp3ChfzIQhkbrIGqrIMsqQAG7AcC4aRrhLLIt%2Bq64VuyaYfhZ5EWRJH5kxRBjmWJykFp67bjh2H6bWhmkXBDYuWZRYaiWZY2DZOmpgRx5GXOLYwTOmA9hWfkOXhTkmcROKhdOqwWAo1loWuImMKwmDkpeBAINEtEadgVIEDSfbyoqg6usOyKjl545/PVU6dj2Z4Vg13ksFYLVhSlrnYBW%2BWFcQg1Sl60V2Zh/n%2BQZ8XGUF7nXtEkEMHRq7PtcmBvtxGWrl%2B%2B0/n%2BwSMVlbFgf21Uum6NmfppR0/muwLEKC0TQclEVzp1rXhalHV3U9V4FUVlqPWuBJCRhTFcZiK23jU8GIRDEnLlNem7tNmMYwecVLU2C1zrxmDUQQtELkdJ0AcxrGgdtu08ZRJP8WTgnCUBYmer6kmoQCEqQtK2wXNgqisHCwFvIL/O/FKZiIsExJeFgbFuGg4WJGTi4fICoSYAA7hcABqzx2NqUIxbpm4Bc5BPHmVFV2l146c9rlzG6SVQvJLuoW1hWO40eBLBWe9u2h5FksAA%2BhoLtRr7c140HLkh9a5Vh07ZaR1wsezb7834wl3ZbRnUdmLH3I8qiXsCz7/vW7mod0qF0c53nicUz2adN22Wet3X%2BdF13js92XPN/LXOP13bqcO0xPeIuXgJCF4iS5M6zxeLQdreycVOMcvq8pOvCib3adMl9B0c/a2WfX5HZh3wvC5j1LFyqifW9m/8e9vxvn901ddetUNRSgeiuNcJcW59SgUNECR1IHZ2gW0OeN9R5DRspA0ebhm5P1KiVISNNuL1XMo1MsSMpKAgACrPG3jXTud5kCR2zNEAgEBhjoCEgoHKTDyZuHfqfTqK816Dg/gQAkcxY4cAWLQTgcReB%2BA4FoUgqBOBuGsNYJ8SwVjAXMIiHgpACCaCkQsDUIA4iSBxBoAAHGYMwABOOxXA4jWKsVwD0HppAyI4JIXgLBYgaFIAopRKiOC8AUCAAJhjFFSNIHAWAMBEAgCWAQRI2JyCUDQLCOg0RQg5U4KoKxAA2AAtIUyQFxgDIGQBcKQOIzC8CVIQEgeAOFtH4IIEQYh2BSBkIIRQKh1DRNILoNoetbyJE4DwaRsj5FGOUZwS82JUl2lQFQC4BSSllIqVUmpFizAXAgB4LJ9BwS6K4HMXgUStALAgEgTJiRslkAoBAe5jyQDACkA/GgW8iqUAiHMiIwQGjGkmbwQFzBiDGkvBEbQmAHCgtIJklml4GC0BBUMrAEQvDAGBLQWg4TuC8CwCwQwwBxAYrwIqBweAlIEqUZgVQcLsRrH0cEaEXilG0DwBEW8kKPBYDmeVPAfjCWkCUsQCIR8bgkqMFyowRiFhUAMMABQhsnh6xWgo/R7ThCiHED0nV/S1BzJGfoUlKB1GWH0Ny8JkAFioA1ukAlxT2GgVMJYawZhgnitBFgW1EAFh2DhTUFwjoxitFIIEYIfQSgDDaLkNIAhw05BSImhg0x%2BhlHaMGzoIwmieBaHoIN1KBBdEaBm2NWbJijALeMWweaK2zHOYsZYqwJDTI4HIwJcyQnrKKaU8plTqm1P2RAXATTTly3OZchVCxCpMCwDEANpBTGSERDiOxiIPEaEkGYSQhSNDxEKXY/QnAfGkD8XonEhSuCFKsXY1xhTzFOM3YU7tQyQlhIiQYhVsSEm3KSUstJzzXknNyWwTgDQWAKQ9MUpgREAJcDsTiLgliGn4CIL6vQOrOn6ukIapQxqhm6AfmMpgEzCUdq7UE3gITFkpOxBcVZfbNnlKzIh5DqGNAHKOQ8k5IE5ZmAuT%2B6JNy7llj49EdJLyJNvPYx8xxATvnQjGn8gFQLIUIvBcC6FsL4WiqRYKFFaK5mYuxbi/FCLiWkvJUo/AVLHC0rmQypl0IEVsqqHMrlPLgX8rWEooVIr9HislUoaVNnTq/qVUwFVar9aaoRThvV3T8OyCNYMpRJGzXyvdVYK13n/X2sdQIZ1rr2K5c9d66IvrnjwEDVUHNzgICuGTW0KNRRM0pryOkVrSRU01EbXG7NJbah5t68WmoZaejRpmEN6t%2BasgRvm4NsogatFtubV46jPbOAsYHQhxiSGUOWIOeOzDAm9HCaucY0g87F2UA7eey9yGd0ejiHY9xiJd37skG0Gj8zQm2G/ddm5/6kDJOWdJ0DOS8kcCg1slgCgFLVIUkd9Ewx0MTpadh2QuGUu9PkIRjLOgQCIlIGRijUzT2dtmR%2BhZQGVlrNUAjpHKO0fxmGDx2T/HdGIiu7%2BgD0OnkZO5wMZHq9I6o7sZHdHBBI7M/w3QFT4SID/KGdpzToqNdQphcGhFhnBDGfRXZzAWKcViEs6K6zsr/NEspTmpzQyXNyTc6KjzHLeDed5caPzgrQRBd4CFqVMIIvytE3wZVqr1UJdFUlrpEhUt9KJya0n2XjCWpsAVuryjisMAJesdhFqPWWC9bRn1LTat2uGyG5rYba0RvazGptfXutJvr11tNK2i0NZG1N8bPfJsNpm51iYY32%2Bj6mMPyt7aW3aJn1t2nwTdsK4uIj5HFwpc4ll6djDJALvTpE9cudmAF0DGXV4p7IB7E4kRIiOIzjfuHtvx6O976l%2BA/CZE2dK6QCSDiButxD0Q9KxSQRxLgGxMwN9LxRERfWjTgGdUTDtepN/OAwHEHBYcVVIZwSQIAA%3D)$Done$

## Links

- [source code](../../../../conceptrodon/descend/stockivore/kindred_repack.hpp)
- [unit test](../../../../tests/unit/metafunctions/stockivore/kindred_repack.test.hpp)
