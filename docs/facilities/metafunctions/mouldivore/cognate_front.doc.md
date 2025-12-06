<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateFront`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-front">To Index</a></p>

## Description

`Mouldivore::CognateFront` accepts an operation.
Its first layer accepts an amount and returns a function.

When invoked, the function collects arguments of the amount from the front of its argument list and instantiates the operation with the collection.

<pre><code>   Oper
-> I
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateFront
 :: template<typename...> class...
 -> auto...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
alias CognateFront
{
    template<auto>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };
}；
```

## Examples

We will invoke the `Operation` with the first three elements from `int, int*, int**, int**`.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int, int*, int**>;

/**** Result ****/
using Result = CognateFront<Operation>
::Page<3>
::Mold<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateFront` using concept expansion.

We will expand the constraint `Prefix<***>` alongside the arguments.

```C++
template<typename, auto>
concept Prefix = true;
```

`Fore` will help us translate `std::index_sequence` into a pack of indices.

```C++
template<typename>
struct Fore {};

template<size_t...I>
struct Fore<std::index_sequence<I...>>
{
    template<template<typename...> class Operation>
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the arguments from the front.
        Prefix<I> auto...targets,
        ...
    )
    -> Operation<typename decltype(targets)::type...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`.

Note that we wrap the elements inside `std::type_identity`.
This ensures we can create objects to invoke the ordinary function.

```C++
template<template<typename...> class Operation>
struct CognateFront
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<typename...Elements>
        using Mold = decltype
        (
            Fore<std::make_index_sequence<Amount>>
            ::template idyl<Operation>(std::type_identity<Elements>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/cognate_front/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/cognate_front.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_front.test.hpp)
