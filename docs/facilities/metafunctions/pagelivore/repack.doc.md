<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Repack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-repack">To Index</a></p>

## Description

`Pagelivore::Repack` accepts an operation and returns a function.
When invoked by a list of packed sequences, the function concatenates the packed sequences and instantiates the operation with the result.

<pre><code>   Oper
-> Seq<sub><i>0</i></sub>&lt;Vs<sub><i>0</i></sub>...&gt;, Seq<sub><i>1</i></sub>&lt;Vs<sub><i>1</i></sub>...&gt;, ..., Seq<sub><i>n</i></sub>&lt;Vs<sub><i>n</i></sub>...&gt;
-> Oper&lt;Vs<sub><i>0</i></sub>..., Vs<sub><i>1</i></sub>..., ..., Vs<sub><i>n</i></sub>...></code></pre>

`Pagelivore::Repack` can also handle `std::integer_sequence`. The function first `static_cast` integers to `std::make_signed_t<size_t>`. Then, it uses the result to invoke an operation.

<pre><code>   Oper
-> Seq<sub><i>0</i></sub>&lt;Type<sub>0</sub>, Vs<sub><i>0</i></sub>...&gt;, Seq<sub><i>1</i></sub>&lt;Type<sub>1</sub>, Vs<sub><i>1</i></sub>...&gt;, ..., Seq<sub><i>n</i></sub>&lt;Type<sub>n</sub>, Vs<sub><i>n</i></sub>...&gt;
-> Oper&lt;Vs<sub><i>0</i></sub>..., Vs<sub><i>1</i></sub>..., ..., Vs<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
Repack
 :: template<auto...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<auto...> class>
struct Repack
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

Here, we first concatenate `std::integer_sequence<int, 0>`,  `std::index_sequence<1, 2>` and `std::index_sequence<3>`. Then we pack the result into `Sequence`:

```C++
template<std::make_signed_t<std::size_t>...Args>
requires (sizeof...(Args) == 4)
struct Sequence;

using SupposedResult = Sequence<0, 1, 2, 3>;

using Result = Repack<Sequence>
::Mold
<
    std::integer_sequence<int, 0>, 
    std::index_sequence<1, 2>,
    std::index_sequence<3>
>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Pagelivore::Repack` is implemented similarly to `Sequnivore::TypicalPaste`. Intermediate results are kept in `Shuttle` or `std::integer_sequence<std::make_signed_t<size_t>, *>`.
After all variables are collected, the `Operation` will be invoked.

A simplified version will be as follows:

```C++
template<auto...>
struct Shuttle;

template<template<auto...> class Operation>
struct Repack
{

    template<typename...>
    struct Detail {};

// Base Case:

    template<template<auto...> class Sequence, auto...Variables>
    struct Detail<Sequence<Variables...>>
    {
        using type = Operation<Variables...>;
    };

    template<template<typename, auto...> class Sequence, typename Type, auto...Variables>
    struct Detail<Sequence<Type, Variables...>>
    {
        using type = Operation<Variables...>;
    };

// Recursive Case:

    template
    <
        template<auto...> class SequenceA,
        template<auto...> class SequenceB,
        auto...VariableAs, 
        auto...VariableBs,
        typename...Others
    >
    struct Detail<SequenceA<VariableAs...>, SequenceB<VariableBs...>, Others...>
    {
        using type = Detail
        <
            Shuttle<VariableAs..., VariableBs...>,
            Others...
        >::type;
    };

    template
    <
        template<typename, auto...> class SequenceA,
        template<typename, auto...> class SequenceB,
        typename TA,
        typename TB,
        auto...VariableAs, 
        auto...VariableBs,
        typename...Others
    >
    struct Detail<SequenceA<TA, VariableAs...>, SequenceB<TB, VariableBs...>, Others...>
    {
        using type = Detail
        <
            std::integer_sequence
            <
                std::make_signed_t<std::size_t>,
                static_cast<std::make_signed_t<std::size_t>>(VariableAs)...,
                static_cast<std::make_signed_t<std::size_t>>(VariableBs)...
            >,
            Others...
        >::type;
    };

    template<typename...PackedSequences>
    using Mold = Detail<PackedSequences...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCAA7GakAA6oCoRODB7evnppGY4CoeFRLLHxgXaYDllCBEzEBDk%2BflWY9kUM9Y0EJZExcYnJCg1NLXlctmN9YQPlQ/4AlLaoXsTI7Bzm/mHI3lgA1Cb%2Bbl6OtIQAnifYJhoAgvcPBJgsKQavJ25M56gAdIDbs9RsQvA5DkIEOcCPQTlZHs9Xu9PphvsiPkwvqdfkRAf9bod9kwFApDgB5FJxLFZYGPUHggiHABKmBSTGQAGtniYEgino9DkLDhjUeirlTmGx8XSHsLDgyIQARTANOjHPm8pXwnmPAD0esOFhJmEOPyUIF1cuFoqxaNOtuxPz%2BMv82CJBlJkMwAEcvIxNqRDriAYCAGqNPBMaL0BSy%2BWKpkqtW0b5CX3%2Bhibb4R4hRmOYBSuu5u57y3n8%2BXyrwZIwiiWmk5KilU4g0gQ5yPR2PFnWC4VavsC61Cx32txj8WS1iYIMh4seklk9N%2BgOz%2BvTtiHAAqDbnLvDXYLcdL/aFicOyaYdDTGbX313VKDufzPaBpdPI41larQprYWADdG38ZtKWpLpOzzbtC17fwfyFQc4KtA0WRqdYMgAN1Nc12CteVJzPY5TjLX8RTeTEnXnd93WJL0V0zTYHlIEjf0nHEDwJN1Fzou8s0wGwWKrKj/hfaCHgUINBPlYTRILCwJKkm0GylTB8XJAgEDiONCPjYULyvG9TnotcnlOWT6HE4sg2MvirDMo96HkqyKQ0rTex0zVCOrWtAIIBsiObAzUy8gdiJC38oRhOF7KggtLMBZ8HP4otqOY8Kq3UzTiBSgl0tuEAQD8qkh3LBJtSQxFCIIr9vkU0dyLFB1lJnfc8Wo7jl14xi0q/fCGrtKdGBa4MOMJWjOtXWyetIoCVJ3Ji6tmmcdwE9KZKS8TJLWjjzOS6bSKKobpUBTKtME3TzwIMFlVVa9UyMrrMFMtxtyYw5dvizjsGsx67Jemx3qSpzUpcrKcou79Fv/OtDoCy9bpvPKwt60jRnQAqwleYA4gAfSUSbs3S8tkZmma0YKlgmE5TA8bwYBwnQHGCG%2BcmQAyAAvGnmbdfbSarUYaWQHHRFGFmCHRkBKep2n6cwRnubcVmOa54E3QgD6FCWfFeb5vSGkcIWRYV1mpZpjJZflsWJeVpnVewdWgc1mUidC77FvlU7sudlGELdArDpKgcyqHQS2InZrjv%2BZQOWp9AbM2E87kI6HAIAWU8dA4aC75o65OX45g6j/YbEPg4q4c9QAKmrmva7rvVnirmud0LAgyVrhv9Tr7uO6tMOTaps26YZ23TiVvBOdH7B8QeYhgET55iAzPAl7JCBldQKh8QgWf56WAKm0OSQlhBK7GW9An7X5Z4U8hLwUgKOXWQULxaCZQ%2BC%2B%2BDQgymQ5kkOfwqtr6PFvs/V%2B78QKoXZFyW8l9ZQFXTrQdAPISZ6wlpjTA2NiB40et8TGQYNC3C2l%2BVmYQsCqBwXA04v8zBEMEqQhg5DKEMXHIAz8QCrQCwNjjJccQCDr3FgVBQM4eEnjcGAt%2B1l76P3QBI7m2AT5wQ4CsWgnAACsvA/AcC0KQVAnA3DWGsAqNYGxGxmH8DwUgBBNDKJWJyEAai1H/H8GorgZgAAcGh/AADYEjeIAJxqP8JINR%2BhOCSF4CwCQGhv5aJ0XojgvAFAgG/tY7RyjSBwFgDARAIA1gEBSOccglA0DvDoHECIM5OCqHcd4gAtN4yQhxgDIGQIcKQ/wzC8DloQEgeB0ZTH4IIEQYh2BSBkIIRQKh1DpNILoKYAB3NsKROA8BUeozRNjdGcHJOcQpTJN6HBqfUxpzTWntMkJ0w4EAPBlPoMQY45iuBLF4GkrQKwIBIFKSkcpZAKAQG%2Bb8kAwApDJBoG/LSlBohbOiGERoVxVm8FhcwYgVxyTRG0DUNJljSlsEEOSBgtAEWzKwNELwwAfi0FoMk7gvAsCUyMOIElK8sV4CwjSnRmBVBoVeIi8gggOhbMuNENsqKPBYC2VdPAUTaWkCwsQaI6RMAqgZcAS4RgbErCoAYeeYY8CYAWWBLRlihnCFEOIcZpqplqC2fM/QhhjCGMsPoPA0RkmQBWKgFIXQaV1LRk2UwlhrBmHifKvMWB3UQBWNUWozgICuAmH4KYIQ5hlAqPkdImQBCJozYULI/Q01DCmDGroPRxieFaHoEtdQZgFsGPEYtMwc2Nt6HWhYDbo0mM2BIdZHANGkDibwBJRzakNKaS0tpHSzDXNwL0h5OxnmvM1SsTSTAsDxCjaQexkh/D/H8f4BIkgNCSDMJIbxMS1EBLCRwCJpAokWP%2BN4rg3j3H%2BPcc%2BtRkguBqP3d4gdWyElJJSVYzVmScmfLyXsop/zAX3MqWwTgjQWAYQSHUpgi46xcH8f8Lg/xOX4CIOGvQpqRkWukFapQNrZm6GSEspgKzaW9v7YO7ZHBdkFPOIcQ5SGUNoYw4BLDOG8PXNuT8%2B5jz/BmBeSB9JHyvmoDuXEYpAKFNiaGDx1DxIjBYa4N/cFrxspQphXC1FfLkXwvRZihwfLcWMAIASolWzSXkspdSvl9KHVMp0fgJetR2VbK5TyrYliMGqNmcK0VVxxVbB0VKmVlj5WKqUCqzzAFQPaqYLq/VhrJR8pI%2BasZ5HZDWpmTomj9qNWBqsM64VkbPXeqyL6/1IEqvBtDXEcNhZ4DRo6KyuNCaK2TCCIwtt6apgFCzdkQbSbUiZq6KNottheuxu6E26bVblultram%2BtVa1u5BmwLJoC2O2rHWN25517mMAc4MGYgyHUPoa0wJ7DuGNAzoIyQCTi6ZPvJXZgNdQxN1hdvfe7Dx6Eg/oSAkYJp7GlTBY4B2wwG3kZKybk/J%2BzlOwYqVUjgSHTksAUBhNpGFBOolGN0z7RHBmyFI4ViZ8hKOlZ0AEUgdGGNrKu5s2ZCT2P7K41QO7LBCfE9J%2BTu0owROqd%2BRJ5YS7ZOZPk4pv5JSZf3JACTh%2BOMyf%2BJxhTggPD7uNL4HQAzySIDQtmeZ0zsqbdooxVimzCm8X2cJcS7zmAyUUrEG52VHnGUxbpSyvzXXZmBeQOcYLvBQtCtdZF6Lkq8zxd4IlpVKXGVpcVxlrLBqjV5bpwViQRXJnM9tWzgwlWnU2Fq913RDWBA0r1OTVrlgQ1DrDf0rrHqludCyC4RhzbhvoBO7mybQ%2BJvzZ2%2B2jbfeBBluaOt4tm2a2tun2N6YvQh9HdmKUXbl2FBdrGUxnn8TbsE6aUTknhxdf/ANx9ud33pOo6WP9wHG7e2g5AGYbD/gXFqOPV0y8QPRfX/V504CA1SWXS3RAEkEuUaXcQSCw28Uk38GPW8UcWvX8FPyHQgN%2B1sWvS6TALP0SXwNfzlS0n70kCAA)

## Links

- [source code](../../../../conceptrodon/descend/pagelivore/repack.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/repack.test.hpp)
