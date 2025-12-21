<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Rotate`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-rotate">To Index</a></p>

## Description

`Varybivore::Rotate` accepts a list of variables.
Its first layer accepts an amount and returns a function.

When invoked by an operation, the function relocates variables of the given amount from the front to the end of the previously provided list and instantiates the operation with the result.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>, V<sub>I</sub>, ..., V<sub>n</sub>
-> I
-> Oper
-> Oper
   &lt;
       V<sub>I</sub>, V<sub>I+1</sub>, ..., V<sub>n</sub>,
       V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>
   &gt;</code></pre>

## Type Signature

```Haskell
Rotate
 :: auto...
 -> auto...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<auto...>
alias Rotate
{
    template<auto>
    alias Page
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
};
```

## Examples

We will rotate the first three variables from `0, 1, 2, 2` and instantiate `Operation` with the result.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<2, 0, 1, 2>;

/**** Result ****/
using Result = Rotate<0, 1, 2, 2>
::Page<3>
::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation is similar to `Varybivore::Amidst`.
We want to count variables one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Rotate` using concept expansion.

We will expand the constraint `Prefix<***>` alongside the arguments.

```C++
template<typename, auto>
concept Prefix = true;
```

We will encode value information into types by `Vay` to avoid defining the body of helper functions.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

`Swivel` will help us translate `std::index_sequence` into a pack of indices.

```C++
template<typename>
struct Swivel {};

template<size_t...I>
struct Swivel<std::index_sequence<I...>>
{
    template
    <
        template<auto...> class Operation,
        typename...BackArgs
    >
    static constexpr auto idyl
    (
        // Expand `Prefix<I>` to count the arguments from the front.
        Prefix<I> auto...front_args,
        // Collect the rest.
        BackArgs...
    )
    -> Operation
    <
        BackArgs::value...,
        decltype(front_args)::value...
    >;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<auto...Variables>
struct Rotate
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<template<auto...> class...Agreements>
        using Rail = decltype
        (
            Swivel<std::make_index_sequence<Amount>>
            ::template idyl<Agreements...>(Vay<Variables>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/rotate/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/varybivore/rotate.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/rotate.test.hpp)
