<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Inject`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-inject">To Index</a></p>

## Description

`Typelivore::Inject` accepts a list of elements.
Its first layer accepts an index, which indicates a location in the list.
Its second layer accepts a list of new elements and returns a function.

When invoked by an operation, the function injects new elements into the location and instantiates the operation with the result.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, E<sub>I</sub>, ..., E<sub>n</sub>
-> I
-> Args...
-> Oper
-> Oper&lt;E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, Args..., E<sub>I</sub>, ..., E<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
Inject
 :: typename...
 -> auto...
 -> typename...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
alias Inject
{
    template<auto>
    alias Page
    {
        template<typename...>
        alias Mold
        {
            template<template<typename...> class>
            alias Road = RESULT;
        };
        
    };
}；
```

## Examples

We will inject `double, double*` into one of `int, int*, int**, int**`. Then, we will instantiate `Operation` with the resulting list.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int, double, double*, int*, int**>;

/**** Result ****/
using Result = Inject<int, int*, int**>
::Page<1>
::Mold<double, double*>
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
Therefore, we will only implement `Inject` using concept expansion.

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
            typename...BackArgs
        >
        static consteval auto idyl
        (
            // Expand `Prefix<I>` to count the arguments from the front.
            Prefix<I> auto...front_args,
            // Collect the rest.
            BackArgs...
        )
        -> Operation
        <
            typename decltype(front_args)::type...,
            NewElements...,
            typename BackArgs::type...
        >;
    };

    template<typename...NewElements>
    using Mold = ProtoMold<NewElements...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`.

Note that we wrap the elements inside `std::type_identity`. This ensures we can create objects to invoke the ordinary function.

```C++
template<typename...Elements>
struct Inject
{
    template<size_t Index>
    struct ProtoPage
    {   
        template<typename...NewElements>
        struct ProtoMold
        {
            template<template<typename...> class...Agreements>
            using Road = decltype
            (
                Enrich<std::make_index_sequence<Index>>
                ::template ProtoMold<NewElements...>
                ::template idyl<Agreements...>(std::type_identity<Elements>{}...)
            );
        };

        template<typename...NewElements>
        using Mold = ProtoMold<NewElements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/inject/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/typelivore/inject.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/inject.test.hpp)
