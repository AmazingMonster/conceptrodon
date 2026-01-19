<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Rotate`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-rotate">To Index</a></p>

## Description

`Typelivore::Rotate` accepts a list of elements.
Its first layer accepts an amount and returns a function.

When invoked by an operation, the function relocates elements of the given amount from the front to the end of the previously provided list and instantiates the operation with the result.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, E<sub>I</sub>, ..., E<sub>n</sub>
-> I
-> Oper
-> Oper
   &lt;
       E<sub>I</sub>, E<sub>I+1</sub>, ..., E<sub>n</sub>,
       E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>
   &gt;</code></pre>

## Type Signature

```Haskell
Rotate
 :: typename...
 -> auto...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
alias Rotate
{
    template<auto>
    alias Page
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};
```

## Examples

We will rotate the first three elements from `int, int*, int**, int**` and instantiate `Operation` with the result.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int**, int, int*, int**>;

/**** Result ****/
using Result = Rotate<int, int*, int**, int**>
::Page<3>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Rotate` using concept expansion.

We will expand the constraint `Prefix<***>` alongside the arguments.

```C++
template<typename, auto>
concept Prefix = true;
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
        template<typename...> class Operation,
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
        typename BackArgs::type...,
        typename decltype(front_args)::type...
    >;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`.

Note that we wrap the elements inside `Tyy`.

```C++
template<typename Element>
struct Tyy
{
    using type = Element;
};
```

This ensures we can create objects to invoke the ordinary function.

```C++
template<typename...Elements>
struct Rotate
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<template<typename...> class...Agreements>
        using Road = decltype
        (
            Swivel<std::make_index_sequence<Amount>>
            ::template idyl<Agreements...>(Tyy<Elements>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/rotate/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/typelivore/rotate.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/rotate.test.hpp)
