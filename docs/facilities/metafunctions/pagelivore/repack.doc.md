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
/**** NewVessel ****/
template<std::make_signed_t<std::size_t>...Args>
requires (sizeof...(Args) == 4)
struct NewVessel;

/**** SupposedResult ****/
using SupposedResult = NewVessel<0, 1, 2, 3>;

/**** Result ****/
using Result = Repack<NewVessel>
::Mold
<
    std::integer_sequence<int, 0>, 
    std::index_sequence<1, 2>,
    std::index_sequence<3>
>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Pagelivore::Repack` is implemented similarly to `Sequnivore::TypicalPaste`. Intermediate results are kept in `Shuttle` or `std::integer_sequence<std::make_signed_t<size_t>, *>`.
After all variables are collected, the `Operation` will be invoked.

A simplified version will be as follows:

```C++
template<auto...>
struct Shuttle;
```

```C++
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

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/repack/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/repack.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/repack.test.hpp)
