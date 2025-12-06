<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateInject`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-inject">To Index</a></p>

## Description

`Mouldivore::CognateInject` accepts an operation.
Its first layer accepts an index, which indicates a location in a list.
Its second layer accepts a list of new elements and returns a function.

When invoked, the function injects new elements into the location of its argument list and instantiates the operation with the result.

<pre><code>   Oper
-> I
-> Es...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Es..., Arg<sub>I</sub>, ..., Arg<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateInject
 :: template<typename...> class...
 -> auto...
 -> typename...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
alias CognateInject
{
    template<auto>
    alias Page
    {
        template<typename...>
        alias Mold
        { 
            template<typename...>
            alias Mold = RESULT;
        };
    };
}；
```

## Examples

We will inject `double, double*` into index `1` of `int, int*, int**, int**`. Then, we will instantiate `Operation` with the resulting list.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int, double, double*, int*, int**>;

/**** Result ****/
using Result = CognateInject<Operation>
::Page<1>
::Mold<double, double*>
::Mold<int, int*, int**>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateInject` using concept expansion.

We will expand the constraint `Prefix<***>` alongside the arguments.

```C++
template<typename, auto>
concept Prefix = true;
```

`Enrich` will help us translate `std::index_sequence` into a pack of indices.

```C++
template<typename>
struct Enrich {};

template<size_t...I>
struct Enrich<std::index_sequence<I...>>
{
    template<typename...NewElements>
    struct ProtoMold
    { 
        template
        <
            template<typename...> class Operation,
            typename...BackTargets
        >
        static consteval auto idyl
        (
            // Expand `Prefix<I>` to count the arguments from the front.
            Prefix<I> auto...front_targets,
            // Collect the rest.
            BackTargets...
        )
        -> Operation
        <
            typename decltype(front_targets)::type...,
            NewElements...,
            typename BackTargets::type...
        >;
    };

    template<typename...NewElements>
    using Mold = ProtoMold<NewElements...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`.

Note that we wrap the elements inside `std::type_identity`. This ensures we can create objects to invoke the ordinary function.

```C++
template<template<typename...> class Operation>
struct CognateInject
{
    template<size_t Index>
    struct ProtoPage
    {
        struct Slash
        {
            template<typename...NewElements>
            struct ProtoMold
            {
                template<typename...Elements>
                using Mold = decltype
                (
                    Enrich<std::make_index_sequence<Index>>
                    ::template ProtoMold<NewElements...>
                    ::template idyl<Operation>(std::type_identity<Elements>{}...)
                );
            };
        };

        template<typename...Agreements>
        using Mold = Slash::template ProtoMold<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/cognate_inject/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/cognate_inject.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_inject.test.hpp)
