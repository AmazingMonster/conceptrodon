<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Inject`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-inject">To Index</a></p>

## Description

`Varybivore::Inject` accepts a list of variables.
Its first layer accepts an index, which indicates a location in the list.
Its second layer accepts a list of new variables and returns a function.

When invoked by an operation, the function injects new variables into the location and instantiates the operation with the result.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>, V<sub>I</sub>, ..., V<sub>n</sub>
-> I
-> Args...
-> Oper
-> Oper&lt;V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>, Args..., V<sub>I</sub>, ..., V<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
Inject
 :: auto...
 -> auto...
 -> auto...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<auto...>
alias Inject
{
    template<auto>
    alias Page
    {
        template<auto...>
        alias Page
        {
            template<template<auto...> class>
            alias Rail = RESULT;
        };
        
    };
}；
```

## Examples

We will inject `10, 11` into index one of `0, 1, 2`. Then, we will instantiate `Operation` with the resulting list.

```C++
template<auto...>
struct Operation;

using SupposedResult = Operation<0, 10, 11, 1, 2>;

using Result = Inject<0, 1, 2>
::Page<1>
::Page<10, 11>
::Rail<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation is similar to `Varybivore::Amidst`.
We want to count variables one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Inject` using concept expansion.

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

`Enrich` will help us translate `std::index_sequence` into a pack of indices.

```C++
template<typename>
struct Enrich {};

template<size_t...I>
struct Enrich<std::index_sequence<I...>>
{
    template<auto...NewVariables>
    struct ProtoPage
    { 
        template
        <
            template<auto...> class Operation,
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
            decltype(front_args)::value...,
            NewVariables...,
            BackArgs::value...
        >;
    };

    template<auto...NewVariables>
    using Page = ProtoPage<NewVariables...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<auto...Variables>
struct Inject
{
    template<size_t Index>
    struct ProtoPage
    {   
        struct Slash
        {
            template<auto...NewVariables>
            struct ProtoPage
            {
                template<template<auto...> class...Agreements>
                using Rail = decltype
                (
                    Enrich<std::make_index_sequence<Index>>
                    ::template ProtoPage<NewVariables...>
                    ::template idyl<Agreements...>(Vay<Variables>{}...)
                );
            };
        };

        template<auto...NewVariables>
        using Page = Slash::template ProtoPage<NewVariables...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/inject/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/inject.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/inject.test.hpp)
