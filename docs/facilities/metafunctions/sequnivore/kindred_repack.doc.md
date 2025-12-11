<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Sequnivore::KindredRepack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#sequnivore-kindred-repack">To Index</a></p>

## Description

`Sequnivore::KindredRepack` accepts a list of packed sequences and returns a function.
When invoked by an operation, the function concatenates the packed sequences and instantiates the operation with the result.

<pre><code>   Seq<sub><i>0</i></sub>&lt;Vs<sub><i>0</i></sub>...&gt;, Seq<sub><i>1</i></sub>&lt;Vs<sub><i>1</i></sub>...&gt;, ..., Seq<sub><i>n</i></sub>&lt;Vs<sub><i>n</i></sub>...&gt;
-> Oper
-> Oper&lt;Vs<sub><i>0</i></sub>..., Vs<sub><i>1</i></sub>..., ..., Vs<sub><i>n</i></sub>...></code></pre>

`Sequnivore::KindredRepack` can also handle `std::integer_sequence`. The function first `static_cast` integers to `std::make_signed_t<size_t>`. Then, it uses the result to invoke an operation.

<pre><code>   Seq<sub><i>0</i></sub>&lt;Type<sub>0</sub>, Vs<sub><i>0</i></sub>...&gt;, Seq<sub><i>1</i></sub>&lt;Type<sub>1</sub>, Vs<sub><i>1</i></sub>...&gt;, ..., Seq<sub><i>n</i></sub>&lt;Type<sub>n</sub>, Vs<sub><i>n</i></sub>...&gt;
-> Oper
-> Oper&lt;Vs<sub><i>0</i></sub>..., Vs<sub><i>1</i></sub>..., ..., Vs<sub><i>n</i></sub>...></code></pre>

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
    template<template<auto...> class>
    alias Rail = RESULT;
};
```

## Examples

Here, we first concatenate `std::integer_sequence<int, 0>`,  `std::index_sequence<1, 2>` and `std::index_sequence<3>`. Then we pack the result into `NewVessel`:

```C++
/**** NewVessel ****/
template<std::make_signed_t<std::size_t>...Args>
requires (sizeof...(Args) == 4)
struct NewVessel;

/**** SupposedResult ****/
using SupposedResult = NewVessel<0, 1, 2, 3>;

/**** Result ****/
using Result = KindredRepack
<
    std::integer_sequence<int, 0>, 
    std::index_sequence<1, 2>,
    std::index_sequence<3>
>::Road<NewVessel>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Sequnivore::KindredRepack` is implemented similarly to [`Sequnivore::TypicalPaste`](./typical_paste.doc.md). Intermediate results are kept in `Shuttle` or `std::integer_sequence<std::make_signed_t<size_t>, *>`.
After all variables are collected, the `Operation` will be invoked.

A simplified version will be as follows:

```C++
template<auto...>
struct Shuttle;
```

```C++
template<typename...>
struct KindredRepack {};

// Base Case:

template<template<auto...> class Sequence, auto...Variables>
struct KindredRepack<Sequence<Variables...>>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation<Variables...>;
    };

    template<template<auto...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

template<template<typename, auto...> class Sequence, typename Type, auto...Variables>
struct KindredRepack<Sequence<Type, Variables...>>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation
        <static_cast<std::make_signed_t<size_t>>(Variables)...>;
    };

    template<template<auto...> class...Agreements>
    using Road = Detail<Agreements...>::type;
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
struct KindredRepack<SequenceA<VariableAs...>, SequenceB<VariableBs...>, Others...>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = KindredRepack
        <
            Shuttle<VariableAs..., VariableBs...>,
            Others...
        >::template Road<Operation>;
    };

    template<template<auto...> class...Agreements>
    using Road = Detail<Agreements...>::type;
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
struct KindredRepack<SequenceA<TA, VariableAs...>, SequenceB<TB, VariableBs...>, Others...>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = KindredRepack
        <
            std::integer_sequence
            <
                std::make_signed_t<std::size_t>,
                static_cast<std::make_signed_t<std::size_t>>(VariableAs)...,
                static_cast<std::make_signed_t<std::size_t>>(VariableBs)...
            >,
            Others...
        >::template Road<Operation>;
    };

    template<template<auto...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/sequnivore/kindred_repack/implementation.hpp)
- [Source code](../../../../conceptrodon/sequnivore/kindred_repack.hpp)
- [Unit test](../../../../tests/unit/metafunctions/sequnivore/kindred_repack.test.hpp)
